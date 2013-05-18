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

}


Rotor::~Rotor()
{

}
