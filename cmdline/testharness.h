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

#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <QCoreApplication>

#include <QHash>
#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "globals.h"
#include "enigmadatabase.h"
#include "alphabet.h"
#include "alphabetdata.h"
#include "entry.h"
#include "entrydata.h"
#include "rotor.h"
#include "reflector.h"
#include "keyboard.h"
#include "steckerboard.h"
#include "enigmaexception.h"
#include "machine.h"
#include "machinedata.h"
#include "mysql.h"

#include "testdatabasevalidation.h"

/****************
 Helper Class to store Component Test Status
 and prompt for test on GUI
***************************/
class TestHash : public QObject
{
    Q_OBJECT

public:

    struct testStatus_t
    {
        bool enabled;
        QString *prompt;
    };

    typedef enum
    {
       TEST_KEYBOARD,
       TEST_STECKERBOARD,
       TEST_ENTRY,
       TEST_ROTOR,
       TEST_RINGSETTING,
       TEST_REFLECTOR,
       TEST_LAMPBOARD,
       TEST_TURNOVER,
       TEST_MACHINE,
       TEST_VALIDATE_MACHINE_CONFIG,
       TEST_DOUBLE_STEP,
       TEST_ADD_AMEND_DEL,
       TEST_VALIDATION
    } TESTS;

    TestHash(QObject *parent = 0) : QObject(parent)
    {
        insertNewItem(TEST_KEYBOARD, "Keyboard");
        insertNewItem(TEST_STECKERBOARD, "Steckerboard");
        insertNewItem(TEST_ENTRY, "Entry Wheel");
        insertNewItem(TEST_ROTOR, "Rotor");
        insertNewItem(TEST_RINGSETTING, "Ring Setting");
        insertNewItem(TEST_REFLECTOR, "Reflector");
        insertNewItem(TEST_LAMPBOARD, "Lampboard");
        insertNewItem(TEST_TURNOVER, "Turnover");
        insertNewItem(TEST_MACHINE, "Machine");
        insertNewItem(TEST_VALIDATE_MACHINE_CONFIG, "Validate Machine Config");
        insertNewItem(TEST_DOUBLE_STEP, "Double Step");
        insertNewItem(TEST_ADD_AMEND_DEL, "Add/Amend/Del");
        insertNewItem(TEST_VALIDATION, "Validation");
    }


    ~TestHash()
    {
        QHashIterator<TESTS, testStatus_t *> i(perform);
        while (i.hasNext()) {
            i.next();
            testStatus_t *tmp = i.value();
            delete tmp->prompt;
            delete tmp;
        }
    }

    QString getPrompt(TESTS key)

    {
        QString result;

        testStatus_t *tmp = perform.value(key, 0);

        if (tmp)
        {
            result =  QString(tmp->prompt->toStdString().data());
        }
        return result;
    }


    void setPrompt(TESTS key, QString prompt)
    {
        testStatus_t *tmp = perform.value(key, 0);

        if (tmp)
        {
            *(tmp->prompt) = prompt;
        }
    }

    bool getEnabled(TESTS key)
    {
        bool result = false;

        testStatus_t *tmp = perform.value(key, 0);

        if (tmp)
        {
            result =  tmp->enabled;

        }
        return result;
    }


    void setEnabled(TESTS key, bool enabled)
    {
        testStatus_t *tmp = perform.value(key, 0);

        if (tmp)
        {
            tmp->enabled = enabled;
        }
    }

    QHash<TESTS, testStatus_t *> getPerform()
    {
        return perform;
    }


signals:


public slots:


protected:

    QHash<TESTS, testStatus_t *> perform;

    void insertNewItem(TESTS key, QString prompt)
    {
        testStatus_t *tmp = new testStatus_t;
        tmp->enabled = false;
        tmp->prompt = new QString(prompt);
        perform.insert(key, tmp);
    }

private:


};


class TestHarness : public QObject
{
    Q_OBJECT

public:

    const static char *MSG_FAIL;
    const static char *MSG_FAIL_NO_EXCEPTION;
    const static char *MSG_OK;
    const static char *MSG_OK_FAIL;

    explicit TestHarness(QObject *parent = 0);

    virtual int exec();
    virtual int execValidationTest();
    virtual int execAddAmendDelTest();

    virtual void testKeyboard();
    virtual void testSteckerboard();
    virtual void testEntry();
    virtual void testRotor();
    virtual void testReflector();
    virtual void testMachine();
    virtual void testMachineConfigurationValidation();
    virtual void testTurnover();
    virtual void testDoubleStep();
    virtual void testLampboard();


    TestHash * getPerform();

signals:

public slots:


protected:

    TestHash *perform;

    QPointer<EnigmaDatabase> edb;
    QPointer<TestDatabaseValidation> tdv;

    QString debugHeader(QString component);
    QString debugFooter(QString component);

    virtual void testRepeatRotate(Rotor &rotor, int repeat, int pinIn, QString letter);
    virtual int testRepeatMapLeftToRight(Rotor &rotor, int repeat, int pinIn, QString letter);
    virtual int testRepeatMapRightToLeft(Rotor &rotor, int repeat, int pinIn, QString letter);
    virtual void testReverseMapping(Rotor &rotor, int keyIn, QString windowChar);
    virtual void testInvalidRingSetting(Rotor &rotor, int ringSetting);

    virtual void performMachineTest(MachineData *md, Globals::EDIT_MODE mode);

private:


};

#endif // ENTRYPOINT_H
