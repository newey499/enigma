#ifndef MACHINE_H
#define MACHINE_H

#include <QMap>
#include <QMapIterator>
#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "genlib.h"
#include "enigmaexception.h"
#include "enigmadatabase.h"


#include "keyboard.h"
#include "steckerboard.h"
#include "entry.h"
#include "rotor.h"
#include "reflector.h"
#include "lampboard.h"

class Machine : public QObject
{
    Q_OBJECT
public:

    explicit Machine(QString machineName, QObject *parent = 0);

    ~Machine();


    virtual Rotor *rotorFactory(QString name, int ringSetting,  QString windowChar);
    virtual void addRotors(QMap<int, Rotor *> rotorArray);
    virtual bool delRotor(QString Name);

    virtual int getRotorCount();

    virtual QString keyPress(QString keyIn);

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
    QMap<int, Rotor *> rotorArray;

    QPointer<Reflector>    oReflector;
    QPointer<Lampboard>    oLampboard;



private:




};

#endif // MACHINE_H
