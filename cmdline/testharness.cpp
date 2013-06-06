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

#include "testharness.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

const char *TestHarness::MSG_FAIL = "FAIL:: Should throw exception :: ";
const char *TestHarness::MSG_FAIL_NO_EXCEPTION = "FAIL:: ";
const char *TestHarness::MSG_OK   = "SUCCESS:: ";
const char *TestHarness::MSG_OK_FAIL = "SUCCESS:: Should throw exception :: ";

TestHarness::TestHarness(QObject *parent) :
    QObject(parent)
{
    createTestHash();
}


int TestHarness::exec()
{
    int result = 0;
    QString component;
    qDebug("TestHarness::exec()");
    edb = EnigmaDatabase::getInstance();
    tdv = new TestDatabaseValidation(this);

    qDebug("=======================================");
    qDebug("grep this output for the string \"FAIL\"");
    qDebug("to find any test that failed.");
    qDebug("=======================================");

    try
    {
        component = "Keyboard";
        debugHeader(component);
        testKeyboard();
        debugFooter(component);
    }
    catch (EnigmaException &e)
    {
        qDebug("Error Testing %s\n%s",
               component.toAscii().data(),
               e.what().toAscii().data());
        debugFooter(component);
    }

    try
    {
        component = "Steckerboard";
        debugHeader(component);
        testSteckerboard();
        debugFooter(component);
    }
    catch (EnigmaException &e)
    {
        qDebug("Error Testing %s\n%s",
               component.toAscii().data(),
               e.what().toAscii().data());
        debugFooter(component);
    }

    try
    {
        component = "Entry Wheel";
        debugHeader(component);
        testEntry();
        debugFooter(component);
    }
    catch (EnigmaException &e)
    {
        qDebug("Error Testing %s\n%s",
               component.toAscii().data(),
               e.what().toAscii().data());
        debugFooter(component);
    }

    try
    {
        component = "Rotor";
        debugHeader(component);
        testRotor();
        debugFooter(component);
    }
    catch (EnigmaException &e)
    {
        qDebug("Error Testing %s\n%s",
               component.toAscii().data(),
               e.what().toAscii().data());
        debugFooter(component);
    }

    try
    {
        component = "Reflector";
        debugHeader(component);
        testReflector();
        debugFooter(component);
    }
    catch (EnigmaException &e)
    {
        qDebug("Error Testing %s\n%s",
               component.toAscii().data(),
               e.what().toAscii().data());
        debugFooter(component);
    }


    try
    {
        component = "Lampboard";
        debugHeader(component);
        testLampboard();
        debugFooter(component);
    }
    catch (EnigmaException &e)
    {
        qDebug("Error Testing %s\n%s",
               component.toAscii().data(),
               e.what().toAscii().data());
        debugFooter(component);
    }


    component = "Test Turnover";
    debugHeader(component);
    testTurnover();
    debugFooter(component);


    component = "MACHINE with rotors I, II, III and reflector B\n"
            "all rotors are set to ring setting 1 and window char \"A\"";
    debugHeader(component);
    testMachine();
    debugFooter(component);


    component = "Double Step rotor turnover";
    debugHeader(component);
    testDoubleStep();
    debugFooter(component);


    qDebug("\n");

    return result;
}


QString TestHarness::debugHeader(QString component)
{
    QString result("\n");

    result = result.append("======================================================\n");
    result = result.append("START TEST %1 \n").arg(component.toUpper());
    result = result.append("======================================================");

    qDebug("%s", result.toAscii().data());

    return result;
}

QString TestHarness::debugFooter(QString component)
{
    QString result("\n");

    result = result.append("======================================================\n");
    result = result.append("END TEST %1 \n").arg(component.toUpper());
    result = result.append("======================================================");

    qDebug("%s", result.toAscii().data());

    return result;
}


void TestHarness::testKeyboard()
{
    qDebug("TestHarness::testKeyboard()");
    if (! perform.value(TEST_KEYBOARD))
    {
        qDebug("Test Disabled");
        qDebug("=============\n");
        return;
    }

    Keyboard keyboard("default", this);

    QString keyPress;

    keyPress = "A";
    keyboard.keyIn(keyPress);
    qDebug("%s key in [%s] valid [%s]",
           MSG_OK,
           keyPress.toAscii().data(),
           keyboard.isValidKey(keyPress) ? "Yes" : "No");

    keyPress = "Z";
    keyboard.keyIn(keyPress);
    qDebug("%s key in [%s] valid [%s]",
           MSG_OK,
           keyPress.toAscii().data(),
           keyboard.isValidKey(keyPress) ? "Yes" : "No");

    try
    {
        keyPress = "a";
        keyboard.keyIn(keyPress);
        qDebug("%s key in [%s] valid [%s]",
               MSG_FAIL,
               keyPress.toAscii().data(),
               keyboard.isValidKey(keyPress) ? "Yes" : "No");
    }
    catch (EnigmaException &e)
    {
        qDebug("%s Keyboard::keyIn keyPress [%s] charOut [%s]",
               MSG_OK_FAIL,
               keyPress.toAscii().data(),
               "*");

    }

}


void TestHarness::testSteckerboard()
{
    qDebug("TestHarness::testSteckerboard()");
    if (! perform.value(TEST_STECKERBOARD))
    {
        qDebug("Test Disabled");
        qDebug("=============\n");
        return;
    }

    Steckerboard stecker("default", this);

    QString from;
    QString to;

    from = "A";
    to = "B";
    qDebug("%s addStecker [%s, %s] %s",
           MSG_OK,
           from.toAscii().data(),
           to.toAscii().data(),
           stecker.addStecker(from, to) ? "added" : "not added");

    from = "C";
    to = "D";
    qDebug("%s addStecker [%s, %s] %s",
           MSG_OK,
           from.toAscii().data(),
           to.toAscii().data(),
           stecker.addStecker(from, to) ? "added" : "not added");

    from = "E";
    to = "F";
    qDebug("%s addStecker [%s, %s] %s",
           MSG_OK,
           from.toAscii().data(),
           to.toAscii().data(),
           stecker.addStecker(from, to) ? "added" : "not added");

    from = "A";
    to = stecker.mapStecker(from);
    qDebug("%s [%s] mapped to [%s]",
           MSG_OK,
           from.toAscii().data(),
           to.toAscii().data());


    from = "B";
    to = stecker.mapStecker(from);
    qDebug("%s [%s] mapped to [%s]",
           MSG_OK,
           from.toAscii().data(),
           to.toAscii().data());

    from = "W";
    to = stecker.mapStecker(from);
    qDebug("%s [%s] mapped to [%s]",
           MSG_OK,
           from.toAscii().data(),
           to.toAscii().data());

    from = "D";
    qDebug("%s [%s] deleted [%s]",
           MSG_OK,
           from.toAscii().data(),
           stecker.delStecker(from) ? "Yes" : "No");


    // stecker has already been removed this should fail
    from = "D";
    qDebug("%s [%s] deleted [%s] Failed as [%s] is not steckered",
           MSG_OK,
           from.toAscii().data(),
           stecker.delStecker(from) ? "Yes" : "No",
           from.toAscii().data());

    from = "L";
    qDebug("%s [%s] deleted [%s] Failed as [%s] is not steckered",
           MSG_OK,
           from.toAscii().data(),
           stecker.delStecker(from) ? "Yes" : "No",
           from.toAscii().data());

}



void TestHarness::testEntry()
{
    qDebug("TestHarness::testEntry()");
    if (! perform.value(TEST_ENTRY))
    {
        qDebug("Test Disabled");
        qDebug("=============\n");
        return;
    }


    Entry entry("ENTRYNOMAP", this);
    //Entry entry("ENTRYREVERSE", this);

    int pinIn;
    int pinOut;
    QString charIn;
    QString charOut;


    pinIn = 1;
    charOut = entry.mapPinToChar(pinIn);
    qDebug("%s Entry::mapPinToChar  pinIn [%d] charOut [%s]",
           MSG_OK, pinIn, charOut.toAscii().data());


    pinIn = 26;
    charOut = entry.mapPinToChar(pinIn);
    qDebug("%s Entry::mapPinToChar  pinIn [%d] charOut [%s]",
           MSG_OK, pinIn, charOut.toAscii().data());


    // invalid pinNo - produces exception
    try
    {
        pinIn = 27;
        charOut = entry.mapPinToChar(pinIn);
        qDebug("%s Should throw exception :: Entry::mapPinToChar pinIn [%d] charOut [%s]",
               MSG_FAIL, pinIn, charOut.toAscii().data());
    }
    catch (EnigmaException &e)
    {
        qDebug("%s Expected exception: Entry::mapPinToChar pinIn [%d] charOut [%s]",
               MSG_OK_FAIL, pinIn,
               "*");
    }


    charIn = "A";
    pinOut = entry.mapCharToPin(charIn);
    qDebug("%s Entry::mapCharToPin  charIn [%s] pinOut [%d]",
           MSG_OK, charIn.toAscii().data(),
           pinOut);

    charIn = "Z";
    pinOut = entry.mapCharToPin(charIn);
    qDebug("%s Entry::mapCharToPin charIn [%s] pinOut [%d]",
           MSG_OK, charIn.toAscii().data(),
           pinOut);


    // invalid charIn - produces exception
    try
    {
        charIn = "a";
        pinOut = entry.mapCharToPin(charIn);
        qDebug("%s Should throw exception Entry::mapCharToPin  charIn [%s] pinOut [%d]",
               MSG_FAIL, charIn.toAscii().data(),
               pinOut);
    }
    catch (EnigmaException &e)
    {
        qDebug("%s Expected exception: Entry::mapCharToPin charIn [%s] pinOut [%s]",
               MSG_OK_FAIL, charIn.toAscii().data(),
               "*");
    }

}


void TestHarness::testRotor()
{
    qDebug("TestHarness::testRotor()");
    if (! perform.value(TEST_ROTOR))
    {
        qDebug("Test Disabled");
        qDebug("=============\n");
        return;
    }

    QString rotorName;
    rotorName = "NOMAP";
    rotorName = "REVERSE";
    Rotor rotor(rotorName, this);

    int pinIn;
    int pinOut;
    int ringSetting;
    int oldLetterOffset;

    testRepeatRotate(rotor, 3, 1, "A");
    testRepeatRotate(rotor, 6, 1, "X");

    qDebug("=======================================");

    testRepeatMapLeftToRight(rotor, 6, 1, "A");

    qDebug("=======================================");

    testRepeatMapRightToLeft(rotor, 6, 1, "A");

    qDebug("=======================================");

    testRepeatMapLeftToRight(rotor, 6, 1, "X");


    qDebug("=======================================");

    testRepeatMapRightToLeft(rotor, 6, 1, "X");

    qDebug("=======================================");

    testReverseMapping(rotor, 1, "A");
    testReverseMapping(rotor, 26, "A");

    qDebug("=======================================");

    testInvalidRingSetting(rotor, 0);
    testInvalidRingSetting(rotor, 1);
    testInvalidRingSetting(rotor, 27);
    testInvalidRingSetting(rotor, 26);

    qDebug("=======================================");
}


void TestHarness::testInvalidRingSetting(Rotor &rotor, int ringSetting)
{
    qDebug("TestHarness::testInvalidRingSetting(Rotor &rotor, int ringSetting)");
    if (! perform.value(TEST_RINGSETTING))
    {
        qDebug("Test Disabled");
        qDebug("=============\n");
        return;
    }

    try
    {
        rotor.setRingSetting(ringSetting);
        qDebug("%s Valid ring setting of [%d] applied",
               MSG_OK,
               ringSetting);
    }
    catch (EnigmaException &e)
    {
        qDebug("%s Invalid ring setting of [%d] : [%s]",
               MSG_OK_FAIL,
               ringSetting,
               e.what().toAscii().data());

    }

}


void TestHarness::testReverseMapping(Rotor &rotor, int keyIn, QString windowChar)
{
    int tmp = testRepeatMapLeftToRight(rotor, 1, keyIn, windowChar);
    testRepeatMapRightToLeft(rotor, 1, tmp, windowChar);
}


void TestHarness::testRepeatRotate(Rotor &rotor, int repeat, int pinIn, QString letter)
{
    int oldLetterOffset;
    QString oldWindowChar;
    rotor.setRingSetting(pinIn);
    rotor.setLetterSetting(letter);

    qDebug("========================================");
    for (int i = 0; i < repeat; i++)
    {
        oldLetterOffset = rotor.getLetterOffset();
        oldWindowChar = rotor.getLetterSetting();
        qDebug("%s rotor.rotate ringstellung [%2d] old win [%s] old offset [%2d] new win [%s] new offset [%2d]",
               MSG_OK,
               rotor.getRingSetting(),
               oldWindowChar.toAscii().data(),
               oldLetterOffset,
               rotor.getLetterSetting().toAscii().data(),
               rotor.rotate()
               );
    }

}


int TestHarness::testRepeatMapLeftToRight(Rotor &rotor, int repeat, int pinIn, QString letter)
{
    int pinOut;
    rotor.setRingSetting(1);
    rotor.setLetterSetting(letter);

    for (int i = 0; i < repeat; i++)
    {
        pinOut = rotor.mapLeftToRight(pinIn);
        qDebug("%s rotor.mapLeftToRight windowChar [%s] ring [%2d] [%s] pinIn [%2d] mapped to pinOut [%2d]",
               MSG_OK,
               rotor.getLetterSetting().toAscii().data(),
               rotor.getRingSetting(),
               rotor.getRotorName().toAscii().data(),
               pinIn,
               pinOut);
        //rotor.rotate();
        //qDebug("rotate called");
        pinIn++;
        //qDebug("pinIn incremented");
    }

    return pinOut;
}


int TestHarness::testRepeatMapRightToLeft(Rotor &rotor, int repeat, int pinIn, QString letter)
{
    int pinOut;
    rotor.setRingSetting(1);
    rotor.setLetterSetting(letter);

    for (int i = 0; i < repeat; i++)
    {
        pinOut = rotor.mapRightToLeft(pinIn);
        qDebug("%s rotor.mapRightToLeft windowChar [%s] ring [%2d] [%s] pinIn [%2d] mapped to pinOut [%2d]",
               MSG_OK,
               rotor.getLetterSetting().toAscii().data(),
               rotor.getRingSetting(),
               rotor.getRotorName().toAscii().data(),
               pinIn,
               pinOut);
        //rotor.rotate();
        // qDebug("rotate called");
        pinIn++;
        //qDebug("pinIn incremented");

    }

    return pinOut;
}

void TestHarness::testReflector()
{
    qDebug("TestHarness::testReflector()");
    if (! perform.value(TEST_REFLECTOR))
    {
        qDebug("Test Disabled");
        qDebug("=============\n");
        return;
    }

    Reflector reflector("REFLECTORNOMAP", this);
    //Reflector reflector("REFLECTORREVERSE", this);

    int pinIn;
    int pinOut;


    pinIn = 1;
    pinOut = reflector.map(pinIn);
    qDebug("%s Reflector::map  pinIn [%d] pinOut [%d]",
           MSG_OK, pinIn, pinOut);

    pinIn = 2;
    pinOut = reflector.map(pinIn);
    qDebug("%s Reflector::map  pinIn [%d] pinOut [%d]",
           MSG_OK, pinIn, pinOut);

    pinIn = 25;
    pinOut = reflector.map(pinIn);
    qDebug("%s Reflector::map  pinIn [%d] pinOut [%d]",
           MSG_OK, pinIn, pinOut);

    pinIn = 26;
    pinOut = reflector.map(pinIn);
    qDebug("%s Reflector::map  pinIn [%d] pinOut [%d]",
           MSG_OK,pinIn, pinOut);

    try
    {
        pinIn = 0;
        pinOut = reflector.map(pinIn);
        qDebug("%s Reflector::map  pinIn [%d] pinOut [%d]",
               MSG_OK, pinIn, pinOut);
    }
    catch (EnigmaException &e)
    {
        qDebug("%s Keyboard::keyIn pinIn [%d] pinOut [%s] [%s]",
               MSG_OK_FAIL,
               pinIn,
               "*",
               e.what().toAscii().data());

    }

    try
    {
        pinIn = 27;
        pinOut = reflector.map(pinIn);
        qDebug("Reflector::map  pinIn [%d] pinOut [%d]",
               pinIn, pinOut);
    }
    catch (EnigmaException &e)
    {
        qDebug("%s Keyboard::keyIn pinIn [%d] pinOut [%s] [%s]",
               MSG_OK_FAIL,
               pinIn,
               "*",
               e.what().toAscii().data());

    }
}




/**********************************************************
***********************************************************

    //repeatRotate(rotor, 5, 1, "A");

    pinIn = 1;
    rotor.setRingSetting(26);
    rotor.setLetterSetting("A");
    pinOut = rotor.mapLeftToRight(pinIn);
    qDebug("%s rotor.mapLeftToRight windowChar [%s] ring [%d] [%s] pinIn [%d] mapped to pinOut [%d]",
           MSG_OK,
           rotor.getLetterSetting().toAscii().data(),
           rotor.getRingSetting(),
           rotorName.toAscii().data(),
           pinIn,
           pinOut);

    //repeatRotate(rotor, 5, 1, "A");


    qDebug("=======================================");

    pinIn = 1;
    rotor.setRingSetting(1);
    rotor.setLetterSetting("A");
    pinOut = rotor.mapLeftToRight(pinIn);
    qDebug("%s rotor.mapLeftToRight windowChar [%s] ring [%d] [%s] pinIn [%d] mapped to pinOut [%d]",
           MSG_OK,
           rotor.getLetterSetting().toAscii().data(),
           rotor.getRingSetting(),
           rotorName.toAscii().data(),
           pinIn,
           pinOut);

    //repeatRotate(rotor, 5, 1, "A");

    pinIn = 1;
    rotor.setRingSetting(1);
    rotor.setLetterSetting("Y");
    pinOut = rotor.mapLeftToRight(pinIn);
    qDebug("%s rotor.mapLeftToRight windowChar [%s] ring [%d] [%s] pinIn [%d] mapped to pinOut [%d]",
           MSG_OK,
           rotor.getLetterSetting().toAscii().data(),
           rotor.getRingSetting(),
           rotorName.toAscii().data(),
           pinIn,
           pinOut);

    //repeatRotate(rotor, 5, 1, "A");

    pinIn = 1;
    rotor.setRingSetting(1);
    rotor.setLetterSetting("Z");
    pinOut = rotor.mapLeftToRight(pinIn);
    qDebug("%s rotor.mapLeftToRight windowChar [%s] ring [%d] [%s] pinIn [%d] mapped to pinOut [%d]",
           MSG_OK,
           rotor.getLetterSetting().toAscii().data(),
           rotor.getRingSetting(),
           rotorName.toAscii().data(),
           pinIn,
           pinOut);

    //repeatRotate(rotor, 5, 1, "A");

    qDebug("=======================================");

    pinIn = 1;
    rotor.setRingSetting(1);
    rotor.setLetterSetting("A");
    pinOut = rotor.mapRightToLeft(pinIn);
    qDebug("%s rotor.mapRightToLeft windowChar [%s] ring [%d] [%s] pinIn [%d] mapped to pinOut [%d]",
           MSG_OK,
           rotor.getLetterSetting().toAscii().data(),
           rotor.getRingSetting(),
           rotorName.toAscii().data(),
           pinIn,
           pinOut);

    //repeatRotate(rotor, 5, 1, "A");

    pinIn = 1;
    rotor.setRingSetting(1);
    rotor.setLetterSetting("Y");
    pinOut = rotor.mapRightToLeft(pinIn);
    qDebug("%s rotor.mapRightToLeft windowChar [%s] ring [%d] [%s] pinIn [%d] mapped to pinOut [%d]",
           MSG_OK,
           rotor.getLetterSetting().toAscii().data(),
           rotor.getRingSetting(),
           rotorName.toAscii().data(),
           pinIn,
           pinOut);

    pinIn = 1;
    rotor.setRingSetting(1);
    rotor.setLetterSetting("Z");
    pinOut = rotor.mapRightToLeft(pinIn);
    qDebug("%s rotor.mapRightToLeft windowChar [%s] ring [%d] [%s] pinIn [%d] mapped to pinOut [%d]",
           MSG_OK,
           rotor.getLetterSetting().toAscii().data(),
           rotor.getRingSetting(),
           rotorName.toAscii().data(),
           pinIn,
           pinOut);





***********************************************************
***********************************************************/


void TestHarness::testTurnover()
{
    if (! perform.value(TEST_TURNOVER))
    {
        qDebug("TestHarness::testTurnover() disabled");
    }
    else
    {
        qDebug("TestHarness::testTurnover()");
        Rotor r_1("I", this);
        r_1.setLetterSetting("A");
        r_1.setRingSetting(1);

        for (int i = 1; i <= r_1.getAlphabetSize(); i++)
        {
            r_1.setRingSetting(i);
            r_1.rotate();
        }
    }

}


void TestHarness::createTestHash()
{
    perform.clear();

    perform.insert(TEST_KEYBOARD, false);
    perform.insert(TEST_STECKERBOARD, false);
    perform.insert(TEST_ENTRY, false);
    perform.insert(TEST_ROTOR, false);
    perform.insert(TEST_REFLECTOR, false);
    perform.insert(TEST_LAMPBOARD, true);
    perform.insert(TEST_RINGSETTING, false);
    perform.insert(TEST_TURNOVER, false);
    perform.insert(TEST_MACHINE, false);
    perform.insert(TEST_DOUBLE_STEP, false);
    perform.insert(TEST_VALIDATION, false);
    perform.insert(TEST_ADD_AMEND_DELETE, false);

}



void TestHarness::testMachine()
{
    qDebug("TestHarness::testMachine()");

    if (! perform.value(TEST_MACHINE))
    {
        qDebug("Test Disabled");
        qDebug("=============\n");
        return;
    }

    Machine machine("Wermacht", this);
    QMap<int, QPointer<Rotor> > rotors;

    try
    {
        rotors.insert(1, machine.rotorFactory("I",   1, "A"));
        rotors.insert(2, machine.rotorFactory("II",  1, "A"));
        rotors.insert(3, machine.rotorFactory("III", 1, "A"));

        machine.addRotors(rotors);

        qDebug("=========================");
        qDebug("G is expected to map to P");
        qDebug("=========================");

        QString keyIn = "G";
        QString keyOut;

        keyOut = machine.keyPress(keyIn);

        if (keyIn == "G" && keyOut == "P")
        {
            qDebug("%s [G] maps to [P] Through rotors I, II, III and reflector B",
                   TestHarness::MSG_OK);
        }
        else
        {

            qDebug("%s [G] should map to [P] Through rotors I, II, III and reflector B",
                   "FAIL:: ");
            qDebug("%s [G] mapped to [%s]",
                   "FAIL:: ",
                   keyOut.toAscii().data());
        }

    }
    catch (EnigmaException &e)
    {
        qDebug("Error Testing %s\n%s",
               "Test Machine",
               e.what().toAscii().data());
    }

}


void TestHarness::testDoubleStep()
{
    qDebug("TestHarness::testDoubleStep()");
    QString expected;
    QString winStr;

    if (! perform.value(TEST_DOUBLE_STEP))
    {
        qDebug("Test Disabled");
        qDebug("=============\n");
        return;
    }

    Machine machine("Wermacht", this);
    QMap<int, QPointer<Rotor> > rotors;


    try
    {
        qDebug("========================");
        qDebug("Initial set up");
        qDebug("------------------------");
        qDebug("Rotors III, II, I");
        qDebug("Ring   1,   1,  1");
        qDebug("Letter K    D   N");
        qDebug("\"_\" = Unchanged :: \"*\" = changed");
        qDebug("========================");

        rotors.insert(1, machine.rotorFactory("III", 1, "K"));
        rotors.insert(2, machine.rotorFactory("II",  1, "D"));
        rotors.insert(3, machine.rotorFactory("I",   1, "N"));
        machine.addRotors(rotors);


        expected = "KDO";
        machine.performTurnover();
        winStr = machine.getWindowChars();
        qDebug("%s Expected [%s] [___] Actual [%s]",
               QString(expected).compare(winStr) == 0 ? MSG_OK : MSG_FAIL_NO_EXCEPTION,
               expected.toAscii().data(),
               winStr.toAscii().data());



        expected = "KDP";
        machine.performTurnover();
        winStr = machine.getWindowChars();
        qDebug("%s Expected [%s] [__*] Actual [%s]",
               QString(expected).compare(winStr) == 0 ? MSG_OK : MSG_FAIL_NO_EXCEPTION,
               expected.toAscii().data(),
               winStr.toAscii().data());


        expected = "KDQ";
        machine.performTurnover();
        winStr = machine.getWindowChars();
        qDebug("%s Expected [%s] [__*] Actual [%s]",
               QString(expected).compare(winStr) == 0 ? MSG_OK : MSG_FAIL_NO_EXCEPTION,
               expected.toAscii().data(),
               winStr.toAscii().data());


        expected = "KER";
        machine.performTurnover();
        winStr = machine.getWindowChars();
        qDebug("%s Expected [%s] [_**] Actual [%s]",
               QString(expected).compare(winStr) == 0 ? MSG_OK : MSG_FAIL_NO_EXCEPTION,
               expected.toAscii().data(),
               winStr.toAscii().data());


        expected = "LFS";
        machine.performTurnover();
        winStr = machine.getWindowChars();
        qDebug("%s Expected [%s] [***] Actual [%s]",
               QString(expected).compare(winStr) == 0 ? MSG_OK : MSG_FAIL_NO_EXCEPTION,
               expected.toAscii().data(),
               winStr.toAscii().data());


        expected = "LFT";
        machine.performTurnover();
        winStr = machine.getWindowChars();
        qDebug("%s Expected [%s] [__*] Actual [%s]",
               QString(expected).compare(winStr) == 0 ? MSG_OK : MSG_FAIL_NO_EXCEPTION,
               expected.toAscii().data(),
               winStr.toAscii().data());


        expected = "LFU";
        machine.performTurnover();
        winStr = machine.getWindowChars();
        qDebug("%s Expected [%s] [__*] Actual [%s]",
               QString(expected).compare(winStr) == 0 ? MSG_OK : MSG_FAIL_NO_EXCEPTION,
               expected.toAscii().data(),
               winStr.toAscii().data());

    }
    catch (EnigmaException &e)
    {
        qDebug("Error Testing %s\n%s",
               "Test Machine",
               e.what().toAscii().data());
    }

}



int TestHarness::execValidationTest()
{
    qDebug("int TestHarness::execValidationTest()");

    if (! perform.value(TEST_VALIDATION))
    {
        qDebug("Test Disabled");
        qDebug("=============\n");
        return 1;
    }

    edb = EnigmaDatabase::getInstance();
    tdv = new TestDatabaseValidation(this);

    tdv->testAlphabetValidation();

    return 0;
}


int TestHarness::execAddAmendDelTest()
{
    qDebug("int TestHarness::execAddAmendDelTest()");

    if (! perform.value(TEST_ADD_AMEND_DELETE))
    {
        qDebug("Test Disabled");
        qDebug("=============\n");
        return 1;
    }

    edb = EnigmaDatabase::getInstance();


    AlphabetData ad(this);

    // Add
    /*********
    Alphabet a(this);
    QSqlRecord rec = a.getAlphabetRec();
    rec.setValue("name", "ABCDEF");
    rec.setValue("alphabet", "1234567890");
    ad.displayRec(rec);
    ad.writeRec(Globals::ROW_ADD, rec);
    ******************/


    // Edit
    /******************
    Alphabet a("ABCDEF", this);
    QSqlRecord rec = a.getAlphabetRec();
    rec.setValue("name", "ABCDEFXYZ");
    rec.setValue("alphabet", "1234567890ABC");
    ad.displayRec(rec);
    ad.writeRec(Globals::ROW_EDIT, rec);
    ************************/

    // Delete
    // /**********************
    Alphabet a("ABCDEFXYZ", this);
    QSqlRecord rec = a.getAlphabetRec();
    ad.displayRec(rec);
    ad.writeRec(Globals::ROW_DEL, rec);
    // ************************/
    ad.displayRec(rec);

    return 0;
}


void TestHarness::testLampboard()
{
    qDebug("TestHarness::testLampboard()");
    if (! perform.value(TEST_LAMPBOARD))
    {
        qDebug("Test Disabled");
        qDebug("=============\n");
        return;
    }
    Lampboard lb("default", this);

    QString keyIn;

    keyIn = "A";
    lb.illuminate(keyIn);

    keyIn = "z";
    lb.illuminate(keyIn);

    keyIn = "DE";
    lb.illuminate(keyIn);

    keyIn = "L";
    lb.illuminate(keyIn);

    qDebug("No test defined for Lampboard");
}

#pragma GCC diagnostic pop
