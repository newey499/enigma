#include "machine.h"

Machine::Machine(QString machineName, QObject *parent) :
    QObject(parent)
{

    edb = EnigmaDatabase::getInstance();

    recMachine = MachineData().getMachine(machineName);

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


QPointer<Rotor> Machine::rotorFactory(QString name, int ringSetting, QString windowChar)
{
    QPointer<Rotor> oRotor = new Rotor(name, this);
    oRotor->setRingSetting(ringSetting);
    oRotor->setLetterSetting(windowChar);

    return oRotor;
}

void Machine::addRotors(QMap<int, QPointer<Rotor> > rotorArray)
{
    this->rotorArray.clear();

    this->rotorArray = rotorArray;
    QMapIterator<int, QPointer<Rotor> > i(rotorArray);
    while (i.hasNext())
    {
        i.next();
        i.value()->setParent(this);
    }
}


QString Machine::getWindowChars()
{
    QString result("");
    QMapIterator<int, QPointer<Rotor> > i(rotorArray);
    while (i.hasNext())
    {
        i.next();
        result = result.append(i.value()->getLetterSetting());
    }
    return result;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
bool Machine::delRotor(QString name)
{
    // TODO define delRotor
    return true;
}
#pragma GCC diagnostic pop

int Machine::getRotorCount()
{
    return rotorCount;
}


QMap<int, QPointer<Rotor> > Machine::getRotorArray()
{
    return rotorArray;
}



void Machine::clearCounters()
{
    turnoverCounters.clear();
    for (int i = 1; i <= getRotorCount(); i++)
    {
        turnoverCounters.insert(i, 0);
    }
}


void Machine::incCounter(int rotorId)
{
    int c = turnoverCounters.value(rotorId);
    c++;
    turnoverCounters.insert(rotorId, c);
}


void Machine::displayCounters()
{
    qDebug("\t\t ==========================");
    qDebug("\t\t Turnover::displayCounters()");
    for (int i = 1; i <= turnoverCounters.count(); i++)
    {
        qDebug("\t\t rotor [%d] name [%s] turnover count [%d]",
               i,
               rotorArray.value(i)->getRotorName().toAscii().data(),
               turnoverCounters.value(i));
    }
    qDebug("\t\t ==========================");
}

void Machine::performTurnover()
{
    clearCounters();

    // find situations where the rotor on the right causes the rotor
    // on the left to turnover
    for (int i = rotorArray.count() - 1; i > 0; i--)
    {
        if (rotorArray.value(i+1)->checkForTurnover())
        {
            qDebug("1 - rotorname [%s] number [%d] turnover YES",
                   rotorArray.value(i)->getRotorName().toAscii().data(),
                   i);
            incCounter(i);
        }
    }

    // rotor double steps if its on its turnover position and
    // its not the first or last rotor.
    for (int i = 2; i < rotorArray.count(); i++)
    {
        qDebug("\t\t Double Step rotor [%d] name [%s]",
               i,
               rotorArray.value(i)->getRotorName().toAscii().data());
        if (rotorArray.value(i)->checkForTurnover() )
        {
            incCounter(i);
        }
    }

    // The right hand rotor ALWAYS turns one position
    qDebug("3 - rotor name [%s] number [%d] turnover YES",
           rotorArray.value(rotorArray.count())->getRotorName().toAscii().data(),
           rotorArray.count());
    incCounter(rotorArray.count()); // force a turnover on the right most rotor

    displayCounters(); // display debug information

    executeTurnovers(); // use the accumulated information to turnover the rotor(s)
}


void Machine::executeTurnovers()
{
    // perform rotor turnovers as calculated
    for (int i = 1; i <= turnoverCounters.count(); i++)
    {
        for (int j = 1; j <= turnoverCounters.value(i); i++)
        {
            rotorArray.value(i)->rotate();
            qDebug("\t\t\t Incrementing rotor [%d] name [%s]",
                   i,
                   rotorArray.value(i)->getRotorName().toAscii().data());
        }
    }
    clearCounters();
}



