/************************************************************************
Copyright Chris Newey 2013

enigmasim@hotmail.com

This file is part of enigma.

Enigma is distributed under the terms of the GNU General Public License

Enigma is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Qiptables is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Qiptables.  If not, see <http://www.gnu.org/licenses/>.

***************************************************************************/

#ifndef ROTOR_H
#define ROTOR_H

#include <QMap>
#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "genlib.h"
#include "enigmaexception.h"
#include "enigmadatabase.h"

class Rotor : public QObject
{
    Q_OBJECT

public:

    explicit Rotor(QString rotorName, QObject *parent = 0);
    ~Rotor();

    virtual void setRingSetting(int setting);
    virtual int  getRingSetting();

    virtual void setLetterSetting(QString setting);
    virtual QString  getLetterSetting();
    virtual int getLetterOffset();

    virtual int mapRightToLeft(int pinIn);
    virtual int mapLeftToRight(int pinIn);

    virtual int getAlphabetSize();

    virtual int calculateOffset(int pinIn);

signals:

public slots:

protected:

    QPointer<EnigmaDatabase> edb;

    QSqlRecord recRotor;
    QSqlRecord recAlphabet;
    QMap<QString, QString> map;
    QMap<int, int> pinMap;

    int alphabetSize;

    QString alphabetMap;
    QString alphabetName;
    QString rotorMap;
    QString rotorName;

    int getMaxRingSetting();
    int ringSetting;
    QString letterSetting;
    int letterOffset;

    virtual bool sanityCheck();
    virtual bool isValidPinNo(int pinNo);


private:

};

#endif // ROTOR_H
