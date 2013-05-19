#include "rotor.h"

Rotor::Rotor(QObject *parent) :
    QObject(parent)
{

    edb = EnigmaDatabase::getInstance();

    recRotor = edb->getRotor("NOMAP");

    recAlphabet = edb->getAlphabet(recRotor.value("alphabetid").toInt());

    qDebug("rotor [%s] alphabet [%s]",
           recRotor.value("name").toString().toAscii().data(),
           recAlphabet.value("name").toString().toAscii().data());

    sanityCheck();

}


Rotor::~Rotor()
{

}


bool Rotor::sanityCheck()
{
    bool result = true;

    QString alphabet = recAlphabet.value("alphabet").toString();
    QString rotor = recRotor.value("pinright").toString();

// Disable deprecated conversion from string constant to char *
// when instantiating EnigmaException object
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

    if (alphabet.size() != rotor.size())
    {
        QString tmp = QString("Rotor: alphabet lengths do not match alphabet [%1] rotor [%2]").
                                arg(recAlphabet.value("name").toString()).
                                arg(recRotor.value("name").toString());
        result = false;
        throw EnigmaException(tmp.toAscii().data(), __FILE__ , __LINE__);
    }

    for (int i = 0; i < alphabet.count(); i++)
    {
        if (! rotor.contains(alphabet.at(i), Qt::CaseSensitive))
        {

            QString tmp = QString("Alphabet character [%1] not found in rotor definition [%2]").
                                    arg(alphabet.at(i)).
                                    arg(recRotor.value("name").toString());
            result = false;
            throw EnigmaException(tmp.toAscii().data(), __FILE__ , __LINE__);
        }
    }

    for (int i = 0; i < rotor.count(); i++)
    {
        if (! alphabet.contains(rotor.at(i), Qt::CaseSensitive))
        {

            QString tmp = QString("Rotor character [%1] not found in Alphabet definition [%2]").
                                    arg(rotor.at(i)).
                                    arg(recAlphabet.value("name").toString());
            result = false;
            throw EnigmaException(tmp.toAscii().data(), __FILE__ , __LINE__);
        }
    }

#pragma GCC diagnostic pop

    return result;
}
