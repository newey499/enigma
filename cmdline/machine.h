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

#ifndef MACHINE_H
#define MACHINE_H

#include <QList>
#include <QMap>
#include <QMapIterator>
#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "componentbase.h"
#include "globals.h"
#include "genlib.h"
#include "enigmaexception.h"
#include "enigmadatabase.h"

#include "alphabet.h"
#include "keyboard.h"
#include "steckerboard.h"
#include "entry.h"
#include "rotor.h"
#include "reflector.h"
#include "lampboard.h"
#include "machinedata.h"

class Machine : public ComponentBase
{
    Q_OBJECT
public:

    explicit Machine(QString machineName, QObject *parent = 0);
    explicit Machine(int machineId, QObject *parent = 0);

    ~Machine();

    virtual QPointer<Rotor> rotorFactory(QString name, int ringSetting,  QString windowChar);
    virtual bool addRotor(int rotorPosition, Rotor *oRotor);
    virtual bool addRotors(QMap<int, QPointer<Rotor> > rotorArray);
    virtual bool delRotor(QString Name);

    virtual bool addEntry(Entry *oEntry);
    virtual bool addReflector(Reflector *oReflector);

    virtual int getRotorCount();
    virtual QString getWindowChars();

    virtual QString keyPress(QString keyIn);

    virtual QMap<int, QPointer<Rotor> > getRotorArray();

    // performTurnover() relies upon the service methods in
    // the protected section to correctly perform turnovers
    // including the dreaded "double step".
    virtual void performTurnover();

    virtual bool hasSteckerboard();

    virtual QSqlRecord getRecMachine();

    virtual Alphabet *getAlphabet();

signals:

public slots:


protected:

    QPointer<EnigmaDatabase> edb;

    QSqlRecord recMachine;

    int     id;
    QString name;
    QString steckerboard;
    int     rotorCount;
    QString entryList;
    QString rotorList;
    QString reflectorList;
    int     alphabetId;


    QPointer<Keyboard>     oKeyboard;
    QPointer<Steckerboard> oSteckerboard;
    QPointer<Entry>        oEntry;
    // Rotors
    QMap<int, QPointer<Rotor> > rotorArray;

    QPointer<Reflector>    oReflector;
    QPointer<Lampboard>    oLampboard;

    QMap<int, int> turnoverCounters;

    virtual void commonConstructor();

    // performTurnover() service methods
    virtual void clearCounters();
    virtual void incCounter(int rotorId);
    virtual void displayCounters(); // debug info - displays result of turnover algorithm
    virtual void executeTurnovers();


private:




};

#endif // MACHINE_H
