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

#include "machine.h"

Machine::Machine(QString machineName, QObject *parent) :
    ComponentBase(parent)
{

    edb = EnigmaDatabase::getInstance();

    recMachine = MachineData().getMachine(machineName);

    commonConstructor();

}


Machine::Machine(int machineId, QObject *parent) :
    ComponentBase(parent)
{
    edb = EnigmaDatabase::getInstance();

    recMachine = MachineData().getMachine(machineId);

    commonConstructor();
}


void Machine::commonConstructor()
{
    id            = recMachine.value("id").toInt();
    name          = recMachine.value("name").toString();
    steckerboard  = recMachine.value("steckerboard").toString();
    rotorCount    = recMachine.value("rotorcount").toInt();
    entryList     = recMachine.value("entrylist").toString();
    rotorList     = recMachine.value("rotorlist").toString();
    reflectorList = recMachine.value("reflectorlist").toString();
    alphabetId    = recMachine.value("alphabetid").toInt();

    oKeyboard = new Keyboard(alphabetId, this);

    // Always instantiate a Steckerboard object even if the machine
    // definition says the machine does not have a steckerboard
    oSteckerboard = new Steckerboard(oKeyboard->getAlphabetObj()->getAlphabetName(), this);

    // Default to the first entry wheel in the list
    QStringList sl = recMachine.value("entrylist").toString().split(",");
    Entry *oEnt = new Entry(sl.at(0).toInt(), this);
    //Entry *oEnt = new Entry("ENTRY", this);
    addEntry(oEnt);

    // Rotors
    sl = recMachine.value("reflectorList").toString().split(",");

    // Default to the first reflector wheel in the list
    //Reflector *oRef = new Reflector("B", this);
    Reflector *oRef = new Reflector(sl.at(0).toInt(), this);
    addReflector(oRef);

    oLampboard = new Lampboard(oKeyboard->getAlphabetObj()->getAlphabetName(), this);

}


bool Machine::hasSteckerboard()
{
    return (steckerboard.compare("YES") == 0);
}


QSqlRecord Machine::getRecMachine()
{
    return recMachine;
}

QString Machine::keyPress(QString keyIn)
{
    QString keyOut = keyIn;
    int pinIn;
    int pinOut;

    // The enigma machine performs the rotor turnover before
    // processing the key press
    performTurnover();

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


bool Machine::addEntry(Entry *oEntry)
{
    bool result = false;

    QStringList rl = entryList.split(",");
    QString id = oEntry->getId();

    if (rl.contains(id))
    {
        oEntry->setParent(this);
        delete this->oEntry;
        this->oEntry = oEntry;
        result = true;
    }

    return result;
}

bool Machine::addReflector(Reflector *oReflector)
{
    bool result = false;

    QStringList rl = reflectorList.split(",");
    QString id = oReflector->getId();

    if (rl.contains(id))
    {
        oReflector->setParent(this);
        delete this->oReflector;
        this->oReflector = oReflector;
        result = true;
    }

    return result;
}

bool Machine::addRotor(int rotorPosition, Rotor *oRotor)
{
    bool result = false;

    QStringList rl = rotorList.split(",");
    QString id = oRotor->getId();

    if (rl.contains(id))
    {
        oRotor->setParent(this);
        rotorArray.insert(rotorPosition, oRotor);
        result = true;
    }
    return result;
}

bool Machine::addRotors(QMap<int, QPointer<Rotor> > rotorArray)
{
    bool result = true;
    this->rotorArray.clear();

    this->rotorArray = rotorArray;

    rotorArray.count();
    QMapIterator<int, QPointer<Rotor> > i(rotorArray);
    while (i.hasNext())
    {
        i.next();
        if (! addRotor(i.key(), i.value()))
        {
            this->rotorArray.clear();
            result = false;
            return result;
        }
    }

    return result;
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



