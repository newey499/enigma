#include "keyboard.h"


Keyboard::Keyboard(QString name, QObject *parent) :
    QObject(parent)
{
    edb = EnigmaDatabase::getInstance();

    try
    {
        recAlphabet = Alphabet().getAlphabet(name);

        alphabetMap = recAlphabet.value("alphabet").toString();
        // This has to be set before a space is prepended
        alphabetSize = alphabetMap.size();

        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        alphabetMap.prepend(" ");
        alphabetName = recAlphabet.value("name").toString();

        qDebug("keyboard alphabet [%s]",
               alphabetName.toAscii().data());

        sanityCheck();
    }
    catch (EnigmaException &e)
    {
        throw e;
    }

}


Keyboard::Keyboard(int alphabetId, QObject *parent) :
    QObject(parent)
{
    edb = EnigmaDatabase::getInstance();

    try
    {
        recAlphabet = Alphabet().getAlphabet(alphabetId);

        alphabetMap = recAlphabet.value("alphabet").toString();
        // This has to be set before a space is prepended
        alphabetSize = alphabetMap.size();

        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        alphabetMap.prepend(" ");
        alphabetName = recAlphabet.value("name").toString();

        qDebug("keyboard alphabet [%s]",
               alphabetName.toAscii().data());

        sanityCheck();
    }
    catch (EnigmaException &e)
    {
        throw e;
    }
}


bool Keyboard::sanityCheck()
{
    qDebug("Keyboard::sanityCheck()");

    bool result = true;

    result = GenLib::alphabetDuplicateCheck(alphabetName, alphabetMap);
    //result = GenLib::alphabetSanityCheck(alphabetName, alphabetMap, rotorName, rotorMap);

    return result;
}


bool Keyboard::isValidKey(QString keyIn)
{
    bool result = true;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

    if (keyIn.size() != 1)
    {
        result = false;
        QString msg = QString("Keyboard - input key must be one character key passed [%1]").
                      arg(keyIn);
        throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
    }

    if (! alphabetMap.contains(keyIn, Qt::CaseSensitive ))
    {
        result = false;
        QString msg = QString("Keyboard - input key [%1] is not in alphabet [%2]").
                      arg(keyIn).
                      arg(alphabetMap.trimmed());
        throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
    }


#pragma GCC diagnostic pop

    return result;
}


QString Keyboard::keyIn(QString keyIn)
{
    try
    {
        // If validation fails an exception is thrown
        isValidKey(keyIn);

        //qDebug("Key input [%s] - validated Ok", keyIn.toAscii().data());
    }
    catch (EnigmaException &e)
    {
        //qDebug("Caught %s", e.what().toAscii().data());

        keyIn = "";
    }

    return keyIn;
}


QString Keyboard::getAlphabetName()
{
    return alphabetName;
}


QString Keyboard::getAlphabetMap()
{
    return alphabetMap;
}
