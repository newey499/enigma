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

#ifndef ROTOR_H
#define ROTOR_H

#include <QMap>
#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "componentbase.h"
#include "globals.h"
#include "genlib.h"
#include "enigmaexception.h"
#include "enigmadatabase.h"
#include "alphabet.h"
#include "rotordata.h"


class Rotor : public ComponentBase
{
    Q_OBJECT

public:

    explicit Rotor(QString name, QObject *parent = 0);
    explicit Rotor(QString name, int ringSetting,  QString windowChar, QObject *parent = 0);

    ~Rotor();

    virtual void setRingSetting(int setting);
    virtual void setRingSetting(QString setting);
    virtual int  getRingSetting();
    virtual QString getRingSettingChar();

    virtual void setLetterSetting(QString setting);
    virtual QString  getLetterSetting();
    virtual int getLetterOffset();

    virtual QString getRotorName();

    virtual QString getId();

    virtual int mapRightToLeft(int pinIn);
    virtual int mapLeftToRight(int pinIn);

    virtual int getAlphabetSize();
    virtual QString getAlphabetMap();

    virtual int calculateOffset(int pinIn);

    virtual bool checkForTurnover();
    virtual QString getNotches();
    virtual bool isNotch(QString charIn);


signals:


public slots:

    virtual int rotate();

protected:

    void commonConstructor(QString name);

    QPointer<Alphabet> oAlphabet;

    QSqlRecord recRotor;
    QSqlRecord recAlphabet;

    QString alphabetMap;
    QString alphabetName;
    int alphabetSize;

    QString rotorMap;
    QString rotorName;
    int rotorSize;

    QString notches;

    int getMaxRingSetting();
    int ringSetting;
    QString ringSettingChar;

    QString letterSetting;
    int letterOffset;

    virtual bool sanityCheck();
    virtual bool isValidPinNo(int pinNo);
    virtual bool isValidChar(QString charIn);

private:

};

#endif // ROTOR_H
