#include "machine.h"

Machine::Machine(QString machineName, QObject *parent) :
    QObject(parent)
{

    edb = EnigmaDatabase::getInstance();

    recMachine = edb->getMachine(machineName);

    id            = recMachine.value("id").toInt();
    name          = recMachine.value("name").toString();
    steckerboard  = recMachine.value("steckerboard").toString();
    rotorCount    = recMachine.value("rotorcount").toInt();
    entryList     = recMachine.value("entrylist").toString();
    rotorList     = recMachine.value("rotorlist").toString();
    reflectorList = recMachine.value("reflectorlist").toString();
    alphabetId    = recMachine.value("alphabetid").toInt();

    oKeyboard = new Keyboard(alphabetId, this);
    oSteckerboard = new Steckerboard(oKeyboard->getAlphabetName(), this);
    oEntry = new Entry("ENTRY", this);
    // Rotors
    oReflector = new Reflector("B", this);
    oLampboard = new Lampboard(oKeyboard->getAlphabetName(), this);
}


QString Machine::keyPress(QString keyIn)
{
    QString keyOut = keyIn;
    int pinIn;
    int pinOut;

    keyOut = oSteckerboard->mapStecker(keyIn);
    qDebug("\tStecker keyIn [%s] keyOut [%s]",
           keyIn.toAscii().data(),
           keyOut.toAscii().data());

    keyIn = keyOut;
    pinOut = oEntry->mapCharToPin(keyIn);
    qDebug("\tEntry keyIn [%s] pinOut [%d]",
           keyIn.toAscii().data(),
           pinOut
           );

    // Go through rotors from right to left
    int i = rotorArray.count();
    while (i > 0)
    {
        pinIn = pinOut;
        Rotor * rotor = rotorArray.value(i);
        pinOut = rotor->mapRightToLeft(pinIn);

        qDebug("\t <<< Rotor [%s] pinIn [%d] pinOut = [%d]",
               rotor->getRotorName().toAscii().data(),
               pinIn,
               pinOut);
        i--;
    }

    pinIn = pinOut;

    pinOut = oReflector->map(pinIn);
    qDebug("\tReflector pinIn [%d] pinOut [%d]",
           pinIn,
           pinOut);


    // Go through rotors from left to right
    int j = 1;
    while (j <= rotorArray.count())
    {
        pinIn = pinOut;
        Rotor *rotor = rotorArray.value(j);
        pinOut = rotor->mapLeftToRight(pinIn);

        qDebug("\t >>> Rotor [%s] pinIn [%d] pinOut = [%d]",
               rotor->getRotorName().toAscii().data(),
               pinIn,
               pinOut);
        j++;
    }

    pinIn = pinOut;
    keyOut = oEntry->mapPinToChar(pinIn);

    qDebug("Entry pinIn [%d] keyOut [%s]",
           pinIn,
           keyOut.toAscii().data());

    return keyOut;
}

Machine::~Machine()
{
    if (oKeyboard)     delete oKeyboard;
    if (oSteckerboard) delete oSteckerboard;
    if (oEntry)        delete oEntry;
    // Rotors
    if (oReflector)    delete oReflector;
    if (oLampboard)    delete oLampboard;
}


Rotor * Machine::rotorFactory(QString name, int ringSetting, QString windowChar)
{
    Rotor * oRotor = new Rotor(name, this);
    oRotor->setRingSetting(ringSetting);
    oRotor->setLetterSetting(windowChar);

    return oRotor;
}

void Machine::addRotors(QMap<int, Rotor *> rotorArray)
{
    this->rotorArray.clear();

    this->rotorArray = rotorArray;
    QMapIterator<int, Rotor *> i(rotorArray);
    while (i.hasNext())
    {
        i.next();
        i.value()->setParent(this);
    }
}


bool Machine::delRotor(QString name)
{
    // TODO define delRotor
    return true;
}


int Machine::getRotorCount()
{
    return rotorCount;
}
