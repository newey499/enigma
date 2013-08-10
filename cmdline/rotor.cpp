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
    ComponentBase(parent)
{
    commonConstructor(name);
    // Ring and Window Letter settings are set by in commonconstructor()
}


Rotor::Rotor(QString name, int ringSetting,  QString windowChar, QObject *parent) :
    ComponentBase(parent)
{
    commonConstructor(name);
    setRingSetting(ringSetting);
    setLetterSetting(windowChar);
}


void Rotor::commonConstructor(QString name)
{

    recRotor = RotorData().getRotor(name);
    oAlphabet = new Alphabet(recRotor.value("alphabetid").toInt(), this);
    recAlphabet = oAlphabet->getAlphabetRec();

    alphabetMap = oAlphabet->getAlphabetMap();
    // This has to be set before a space is prepended
    alphabetSize = alphabetMap.size();

    // Place a space at the start of the string so that pin
    // numbers need not be zero based.
    alphabetMap.prepend(" ");
    alphabetName = oAlphabet->getAlphabetName();

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

}


Rotor::~Rotor()
{

}


QString Rotor::getRotorName()
{
    return objectName();
}

QString Rotor::getId()
{
    return recRotor.value("id").toString();
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
        qDebug("1) Ring setting requested [%d] is outside permitted range [%d...%d]",
                setting,
                1,
                getMaxRingSetting());
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
        qDebug("2) Ring setting requested [%s] is not in alphabet [%s] [%s]",
                setting.toAscii().data(),
                alphabetName.toAscii().data(),
                alphabetMap.toAscii().data());
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
        qDebug("Letter setting requested [%s] is not in alphabet [%s]",
                setting.toAscii().data(),
                alphabetMap.toAscii().data());
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


    pinIn = calculateOffset(pinIn);

    if (! isValidPinNo(pinIn))
    {
         qDebug("requested pin [%d] not in valid range [%d...%d]",
                pinIn,
                1,
                getAlphabetSize());
    }

    QString x = rotorMap.at(pinIn);
    result = alphabetMap.indexOf(x, 0, Qt::CaseSensitive );

    if (result == -1)
    {
       qDebug("rotor map right to left pin number [%d] not found",
              pinIn);
    }

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

    pinIn = calculateOffset(pinIn);

    if (! isValidPinNo(pinIn))
    {
         qDebug("requested pin [%d] not in valid range [%d...%d]",
                pinIn,
                1,
                getAlphabetSize());
    }

    QString x = alphabetMap.at(pinIn);
    result = rotorMap.indexOf(x, 0, Qt::CaseSensitive );

    if (result == -1)
    {
       qDebug("rotor map right to left pin number [%d] not found",
                pinIn);
    }

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

    if (newLetterOffset == 0)
    {
        newLetterOffset = getAlphabetSize();
    }

    letterOffset = newLetterOffset;
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
        result = true;
    }

    return result;
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
