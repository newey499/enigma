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

#ifndef KEYBOARD_H
#define KEYBOARD_H

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
#include "alphabetdata.h"

class Keyboard : public ComponentBase
{
    Q_OBJECT

public:

    explicit Keyboard(QString name, QObject *parent = 0);
    explicit Keyboard(int alphabetId, QObject *parent = 0);
    ~Keyboard();

    virtual bool isValidKey(QString keyIn);
    virtual QString keyIn(QString keyIn);

    virtual QPointer<Alphabet> getAlphabetObj();

    virtual bool getForceToUpper();
    virtual void setForceToUpper(bool toUpper);

signals:

public slots:


protected:

    QPointer<Alphabet> oAlphabet;

    QPointer<EnigmaDatabase> edb;

    QSqlRecord recAlphabet;

    int alphabetSize;
    bool forceToUpper;

    QString alphabetMap;
    QString alphabetName;

    virtual void commonConstructor();

private:



};

#endif // KEYBOARD_H
