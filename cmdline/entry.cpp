#include "entry.h"


Entry::Entry(QString entryName, QObject *parent) :
    QObject(parent)
{

    edb = EnigmaDatabase::getInstance();

    try
    {
        recEntry = edb->getEntry(entryName);
        recAlphabet = edb->getAlphabet(recEntry.value("alphabetid").toInt());

        alphabetMap = recAlphabet.value("alphabet").toString();
        // This has to be set before a space is prepended
        alphabetSize = alphabetMap.size();

        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        alphabetMap.prepend(" ");
        alphabetName = recAlphabet.value("name").toString();

        entryMap = recEntry.value("pinright").toString();
        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        entryMap.prepend(" ");
        this->entryName = recEntry.value("name").toString();


        qDebug("entry [%s] alphabet [%s]",
               recEntry.value("name").toString().toAscii().data(),
               recAlphabet.value("name").toString().toAscii().data());

        sanityCheck();
    }
    catch (EnigmaException &e)
    {
        throw e;
    }

}


Entry::~Entry()
{

}


bool Entry::sanityCheck()
{
    bool result = true;

    result = GenLib::alphabetSanityCheck(alphabetName, alphabetMap, entryName, entryMap);

    return result;
}


bool Entry::isValidPinNo(int pinNo)
{
    bool result = true;

    if ((pinNo < 1) || (pinNo > getAlphabetSize()))
    {
        result = false;
    }

    return result;
}


bool Entry::isValidKey(QString keyIn)
{
    return alphabetMap.contains(keyIn, Qt::CaseSensitive);
}


int Entry::getAlphabetSize()
{
    return alphabetSize;
}


/*******************
Assume the right side of the entry wheel is in alphabet order
and the left side of the entry wheel to be in mapping order.
********************/
int Entry::map(int pinIn)
{
    int result = -1;
    int origPinIn = pinIn;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

    if (! isValidPinNo(pinIn))
    {
         QString msg = QString("requested pin [%1] not in valid range [%2...%3]").
                            arg(pinIn).
                            arg(1).
                            arg(getAlphabetSize());
         throw EnigmaException(msg.toAscii().data(),__FILE__, __LINE__);
    }

    QString x = alphabetMap.at(pinIn);
    result = entryMap.indexOf(x, 0, Qt::CaseSensitive );


    if (result == -1)
    {
       QString msg = QString("entry map right to left pin number [%1] not found").
                        arg(pinIn);
       throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
    }

#pragma GCC diagnostic pop

    qDebug("mapLeftToRight origPinIn [%d] calcPinIn [%d] pinOut [%d]",
           origPinIn, pinIn, result);

    return result;
}



int Entry::mapCharToPin(QString keyIn)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

    if (! isValidKey(keyIn))
    {
        QString msg = QString("requested key [%1] not in alphabet [%2] [%3]").
                           arg(keyIn).
                           arg(alphabetName).
                           arg(alphabetMap);
        throw EnigmaException(msg.toAscii().data(),__FILE__, __LINE__);
    }

    int result = entryMap.indexOf(keyIn, 0, Qt::CaseSensitive);
    qDebug("charIn [%s] pinOut [%d] [%s] [%s]",
           keyIn.toAscii().data(),
           result,
           entryName.toAscii().data(),
           entryMap.toAscii().data() );

    if (result == -1)
    {
        QString msg = QString("requested key [%1] not in entry mapping [%2] [%3]").
                           arg(keyIn).
                           arg(entryName).
                           arg(entryMap);
        throw EnigmaException(msg.toAscii().data(),__FILE__, __LINE__);
    }

    return result;

#pragma GCC diagnostic pop
}

QString Entry::mapPinToChar(int pinIn)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

    if (! isValidPinNo(pinIn))
    {
         QString msg = QString("requested pin [%1] not in valid range [%2...%3]").
                            arg(pinIn).
                            arg(1).
                            arg(getAlphabetSize());
         throw EnigmaException(msg.toAscii().data(),__FILE__, __LINE__);
    }

    return entryMap.at(pinIn);

#pragma GCC diagnostic pop
}
