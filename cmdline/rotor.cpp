/************************************************************************
Copyright Chris Newey 2013

enigmasim@outlook.com

This file is part of enigma.

Enigma is distributed under the terms of the GNU General Public License

Enigma is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Enigma is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Enigma.  If not, see <http://www.gnu.org/licenses/>.

***************************************************************************/

#include "rotor.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

Rotor::Rotor(QString name, QObject *parent) :
    QObject(parent)
{
    commonConstructor(name);
}


Rotor::Rotor(QString name, int ringSetting,  QString windowChar, QObject *parent) :
    QObject(parent)
{
    commonConstructor(name);
    setRingSetting(ringSetting);
    setLetterSetting(windowChar);
}


void Rotor::commonConstructor(QString name)
{
    edb = EnigmaDatabase::getInstance();

    try
    {
        recRotor = RotorData().getRotor(name);
        recAlphabet = AlphabetData().getAlphabet(recRotor.value("alphabetid").toInt());

        alphabetMap = recAlphabet.value("alphabet").toString();
        // This has to be set before a space is prepended
        alphabetSize = alphabetMap.size();

        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        alphabetMap.prepend(" ");
        alphabetName = recAlphabet.value("name").toString();

        rotorMap = recRotor.value("pinright").toString();
        rotorSize = rotorMap.size();

        notches = recRotor.value("notches").toString();

        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        rotorMap.prepend(" ");
        rotorName = recRotor.value("name").toString();
        setObjectName(rotorName);

        setRingSetting(1);
        setLetterSetting(alphabetMap.at(1));

        qDebug("rotor [%s] alphabet [%s]",
               recRotor.value("name").toString().toAscii().data(),
               recAlphabet.value("name").toString().toAscii().data());

        sanityCheck();

        connect(this, SIGNAL(rotorTurnover(Rotor *, QString)),
                this, SLOT(slotTurnover(Rotor *, QString)));
    }
    catch (EnigmaException &e)
    {
        throw e;
    }
}


Rotor::~Rotor()
{

}


QString Rotor::getRotorName()
{
    return objectName();
}


bool Rotor::sanityCheck()
{
    bool result = true;

    result = GenLib::alphabetSanityCheck(alphabetName, alphabetMap, rotorName, rotorMap);

    return result;
}


int Rotor::getAlphabetSize()
{
    return alphabetSize;
}


int Rotor::getMaxRingSetting()
{
  return getAlphabetSize();
}


bool Rotor::isValidPinNo(int pinNo)
{
    bool result = true;

    if ((pinNo < 1) || (pinNo > getAlphabetSize()))
    {
        result = false;
    }

    return result;
}


bool Rotor::isValidChar(QString charIn)
{
    return (! (alphabetMap.indexOf(charIn, Qt::CaseSensitive) == -1));
}

void Rotor::setRingSetting(int setting)
{
    if (! isValidPinNo(setting))
    {
        QString msg = QString("Ring setting requested [%1] is outside permitted range [%2...%3]").
                            arg(setting).
                            arg(1).
                            arg(getMaxRingSetting());
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
        throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
#pragma GCC diagnostic pop

    }
    else
    {
        ringSetting = setting;
        ringSettingChar = alphabetMap.at(ringSetting);
    }

}

QString Rotor::getRingSettingChar()
{
    return ringSettingChar;
}

void Rotor::setRingSetting(QString setting)
{
    if (! isValidChar(setting))
    {
        QString msg = QString("Ring setting requested [%1] is not in alphabet [%2] [%3]").
                            arg(setting).
                            arg(alphabetName).
                            arg(alphabetMap);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
        throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
#pragma GCC diagnostic pop

    }
    else
    {
        ringSettingChar = setting;
        ringSetting = alphabetMap.indexOf(ringSettingChar, Qt::CaseSensitive);
    }
}


int  Rotor::getRingSetting()
{
    return ringSetting;
}


void Rotor::setLetterSetting(QString setting)
{
    if ( (setting.count() != 1) || (! alphabetMap.contains(setting, Qt::CaseSensitive)) )
    {
        QString msg = QString("Letter setting requested [%1] is not in alphabet [%2]").
                            arg(setting.toAscii().data()).
                            arg(alphabetMap.toAscii().data());

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
        throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
#pragma GCC diagnostic pop

    }
    else
    {
        letterSetting = setting;
        letterOffset  = alphabetMap.indexOf(letterSetting, 0, Qt::CaseSensitive);
    }
}

QString Rotor::getLetterSetting()
{
    return letterSetting;
}


int Rotor::getLetterOffset()
{
    return letterOffset;
}


/*******************
Assume the right side of the rotor is in alphabet order
and the left side of the rotor to be in mapping order.
********************/
int Rotor::mapRightToLeft(int pinIn)
{
    int result = -1;
    int origPinIn = pinIn;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

    pinIn = calculateOffset(pinIn);

    if (! isValidPinNo(pinIn))
    {
         QString msg = QString("requested pin [%1] not in valid range [%2...%3]").
                            arg(pinIn).
                            arg(1).
                            arg(getAlphabetSize());
         throw EnigmaException(msg.toAscii().data(),__FILE__, __LINE__);
    }

    QString x = rotorMap.at(pinIn);
    result = alphabetMap.indexOf(x, 0, Qt::CaseSensitive );

    if (result == -1)
    {
       QString msg = QString("rotor map right to left pin number [%1] not found").
                        arg(pinIn);
       throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
    }

#pragma GCC diagnostic pop

    //qDebug("mapRightToLeft origPinIn [%d] calcPinIn [%d] pinOut [%d]",
    //       origPinIn, pinIn, result);

    return result;
}


/*******************
Assume the right side of the rotor is in alphabet order
and the left side of the rotor to be in mapping order.
********************/
int Rotor::mapLeftToRight(int pinIn)
{
    int result = -1;
    int origPinIn = pinIn;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

    pinIn = calculateOffset(pinIn);

    if (! isValidPinNo(pinIn))
    {
         QString msg = QString("requested pin [%1] not in valid range [%2...%3]").
                            arg(pinIn).
                            arg(1).
                            arg(getAlphabetSize());
         throw EnigmaException(msg.toAscii().data(),__FILE__, __LINE__);
    }

    QString x = alphabetMap.at(pinIn);
    result = rotorMap.indexOf(x, 0, Qt::CaseSensitive );


    if (result == -1)
    {
       QString msg = QString("rotor map right to left pin number [%1] not found").
                        arg(pinIn);
       throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
    }

#pragma GCC diagnostic pop

    //qDebug("mapLeftToRight origPinIn [%d] calcPinIn [%d] pinOut [%d]",
    //       origPinIn, pinIn, result);

    return result;
}


int Rotor::calculateOffset(int pinIn)
{
    int result = -1;

    result = ( pinIn + (getRingSetting() -1) + (getLetterOffset() - 1) ) % getAlphabetSize();
    if (result == 0)
    {
        result = getAlphabetSize();
    }

    /**********
    qDebug("calc "
           "pinIn [%d] "
           "ringsetting [%d] "
           "letterOffset [%d] "
           "alphabet length [%d] "
           "result [%d]",
           pinIn, getRingSetting(),
           getLetterOffset(), getAlphabetSize(),
           result);
    ***************/

    return result;
}


int Rotor::rotate()
{
    int oldLetterOffset = getLetterOffset();
    int newLetterOffset = (getLetterOffset() + 1) %  getAlphabetSize();

    //checkForTurnover();

    if (newLetterOffset == 0)
    {
        newLetterOffset = getAlphabetSize();
    }

    letterOffset = newLetterOffset;
    //setLetterSetting(rotorMap.at(letterOffset));
    setLetterSetting(alphabetMap.at(letterOffset));

    qDebug("Rotor::rotate() Rotating rotor name [%s] oldLetterOffset [%d] newLetterOffset [%d]",
           getRotorName().toAscii().data(),
           oldLetterOffset, newLetterOffset);

    return letterOffset;
}


bool Rotor::checkForTurnover()
{
    bool result = false;

    qDebug("Rotor::checkForTurnover() Letter [%s]", getLetterSetting().toAscii().data());
    if (isNotch(getLetterSetting()))
    {
        //qDebug("\t EMIT SIGNAL Letter [%s]", getLetterSetting().toAscii().data());
        //emit rotorTurnover(this, getLetterSetting());
        result = true;
    }

    return result;
}


void Rotor::slotTurnover(Rotor *rotor, QString windowChar)
{
    qDebug("slotTurnover(rotor *) %s Window Char [%s]",
           rotor->getRotorName().toAscii().data(),
           windowChar.toAscii().data());
}


QString Rotor::getNotches()
{
    return notches;
}

bool Rotor::isNotch(QString charIn)
{
    bool result = true;

    result = getNotches().contains(charIn, Qt::CaseSensitive);

    qDebug("Rotor::isNotch charIn [%s] Notches [%s] Result [%s]",
           charIn.toAscii().data(),
           getNotches().toAscii().data(),
           result ? "true" : "false");

    return result;
}


#pragma GCC diagnostic pop
