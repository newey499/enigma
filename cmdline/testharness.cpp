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
    perform = new TestHash(this);
}


TestHash * TestHarness::getPerform()
{
    return perform;
}


int TestHarness::exec()
{
    int result = 0;
    QString component;
    qDebug("TestHarness::exec()");
    edb = EnigmaDatabase::getInstance();

    //perform->setEnabled(TestHash::TEST_VALIDATE_MACHINE_CONFIG, true);
    perform->setEnabled(TestHash::TEST_MACHINE, true);

    result = execValidationTest();
    result = execAddAmendDelTest();

    try
    {
        testKeyboard();
    }
    catch (EnigmaException &e)
    {

        qDebug("Error Testing %s\n%s",
               component.toAscii().data(),
               e.what().toAscii().data());
    }

    try
    {
        testSteckerboard();
    }
    catch (EnigmaException &e)
    {
        qDebug("Error Testing %s\n%s",
               component.toAscii().data(),
               e.what().toAscii().data());
    }

    try
    {
        testEntry();
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
        testRotor();
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
        testReflector();
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
        testLampboard();
    }
    catch (EnigmaException &e)
    {
        qDebug("Error Testing %s\n%s",
               component.toAscii().data(),
               e.what().toAscii().data());
        debugFooter(component);
    }



    testTurnover();

    testDoubleStep();

    testMachineConfigurationValidation();

    testMachine();



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

    if (! perform->getEnabled(TestHash::TEST_KEYBOARD))
    {
        return;
    }

    QString component = "Keyboard";
    debugHeader(component);

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


    keyPress = "a";
    QString keyOut = keyboard.keyIn(keyPress);
    if (keyOut.isEmpty())
    {
        qDebug("%s key in [%s] valid %s - returned empty string",
               MSG_OK,
               keyPress.toAscii().data(),
               keyboard.isValidKey(keyPress) ? "Yes" : "No");
    }
    else
    {
        qDebug("%s key in [%s] valid %s - returned [%s] - should have returned empty string",
               MSG_FAIL,
               keyPress.toAscii().data(),
               keyboard.isValidKey(keyPress) ? "Yes" : "No",
               keyOut.toAscii().data());
    }


    debugFooter(component);
}


void TestHarness::testSteckerboard()
{
    if (! perform->getEnabled(TestHash::TEST_STECKERBOARD))
    {
        return;
    }

    QString component = "Steckerboard";
    debugHeader(component);

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
    to = "W";
    qDebug("%s addStecker failed A already steckered [%s, %s] %s",
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

    debugFooter(component);
}



void TestHarness::testEntry()
{
    QString name;


    if (! perform->getEnabled(TestHash::TEST_ENTRY))
    {
        return;
    }

    QString component = "Entry Wheel";
    debugHeader(component);

    QString tmp = MySql::getEnum("enigma", "rotor", "type").join(",");
    qDebug("Entry: MySQL enum[%s]", tmp.toAscii().data());

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
    pinIn = 27;
    charOut = entry.mapPinToChar(pinIn);
    qDebug("%s Fails - Should return empty string :: Entry::mapPinToChar pinIn [%d] charOut [%s]",
           MSG_OK, pinIn, charOut.toAscii().data());



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
    charIn = "a";
    pinOut = entry.mapCharToPin(charIn);
    qDebug("%s Fails Should return invalid pin no [%d] :: mapCharToPin  charIn [%s] pinOut [%d]",
           MSG_OK,
           Globals::INVALID_PIN_NUMBER,
           charIn.toAscii().data(),
           pinOut);

    qDebug("*********************************");
    qDebug("Test Add Entry Wheel Rec");
    qDebug("*************************************");
    EntryData ed;

    ed.dispRec();
    ed.writeRec(Globals::ROW_ADD);
    qDebug("Class EntryData\n%s", ed.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    ed.setName("AA");
    ed.dispRec();
    ed.writeRec(Globals::ROW_ADD);
    qDebug("Class EntryData\n%s", ed.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    ed.setName("Name");
    ed.dispRec();
    ed.writeRec(Globals::ROW_ADD);
    qDebug("Class EntryData\n%s", ed.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    ed.setAlphabetId(99);
    ed.dispRec();
    ed.writeRec(Globals::ROW_ADD);
    qDebug("Class EntryData\n%s", ed.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    ed.setAlphabetId(5);
    ed.dispRec();
    ed.writeRec(Globals::ROW_ADD);
    qDebug("Class EntryData\n%s", ed.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    ed.setPinRight("ABCD");
    ed.dispRec();
    ed.writeRec(Globals::ROW_ADD);
    qDebug("Class EntryData\n%s", ed.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    ed.setPinRight("ABCDEF");
    ed.dispRec();
    ed.writeRec(Globals::ROW_ADD);
    qDebug("Class EntryData\n%s", ed.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    qDebug("*********************************");
    qDebug("Test Edit Entry Wheel Rec");
    qDebug("*************************************");

    name = "Name";
    qDebug("Loading Entry wheel [%s]", name.toAscii().data());
    ed.getEntry(name);
    ed.dispRec();
    qDebug("==========================================");

    ed.setPinRight("FEDCBA");
    ed.dispRec();
    ed.writeRec(Globals::ROW_EDIT);
    qDebug("Class EntryData\n%s", ed.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    qDebug("*********************************");
    qDebug("Test Delete Entry Wheel Rec");
    qDebug("*************************************");

    name = "Name";
    qDebug("Loading Entry wheel [%s]", name.toAscii().data());
    ed.getEntry(name);
    ed.dispRec();
    qDebug("==========================================");

    ed.dispRec();
    ed.writeRec(Globals::ROW_DEL);
    qDebug("Class EntryData\n%s", ed.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    name = "ENTRY";
    qDebug("Loading Entry wheel [%s]", name.toAscii().data());
    ed.getEntry(name);
    ed.dispRec();
    qDebug("==========================================");

    ed.dispRec();
    ed.writeRec(Globals::ROW_DEL);
    qDebug("Class EntryData\n%s", ed.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    debugFooter(component);
}


void TestHarness::testRotor()
{

    if (! perform->getEnabled(TestHash::TEST_ROTOR))
    {
        return;
    }

    QString component = "Rotor";
    debugHeader(component);

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

    qDebug("********************************************");
    qDebug("START: Test Add/Amend/Delete Rotor Wheel Rec");
    qDebug("********************************************");
    RotorData rd;

    rd.dispRec();
    rd.writeRec(Globals::ROW_ADD);
    qDebug("Class RotorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");



    rd.setAlphabetId(5);
    rd.setNotches("A ,B,D");
    rd.dispRec();
    rd.writeRec(Globals::ROW_ADD);
    qDebug("Class RotorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    rd.setPinRight("ABCDEF");
    rd.dispRec();
    rd.writeRec(Globals::ROW_ADD);
    qDebug("Class RotorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");


    rd.setName("testrotor");
    rd.dispRec();
    rd.writeRec(Globals::ROW_ADD);
    qDebug("Class RotorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    // This add should fail
    rd.dispRec();
    rd.writeRec(Globals::ROW_ADD);
    qDebug("Class RotorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    rd.setPinRight("FEDCBA");
    rd.dispRec();
    rd.writeRec(Globals::ROW_EDIT);
    qDebug("Class RotorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");


    rd.getRotor("testrotor");
    rd.dispRec();
    rd.writeRec(Globals::ROW_DEL);
    qDebug("Class RotorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    qDebug("*********************************************");
    qDebug("FINISH: Test Add/Amend/Delete Rotor Wheel Rec");
    qDebug("*********************************************");

    debugFooter(component);

}


void TestHarness::testInvalidRingSetting(Rotor &rotor, int ringSetting)
{
    if (! perform->getEnabled(TestHash::TEST_RINGSETTING))
    {
        return;
    }

    QString component = "Reflector";
    debugHeader(component);

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

    debugFooter(component);

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
    if (! perform->getEnabled(TestHash::TEST_REFLECTOR))
    {
        return;
    }

    QString component = "Reflector";
    debugHeader(component);

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


    pinIn = 0;
    pinOut = reflector.map(pinIn);
    qDebug("%s Reflector::map Expected Failure pin returned [%d] returned pinIn [%d] pinOut [%d]",
           MSG_OK,
           Globals::INVALID_PIN_NUMBER,
           pinIn,
           pinOut);


    pinIn = 27;
    pinOut = reflector.map(pinIn);
    qDebug("%s Reflector::map Expected Failure pin returned [%d] pinIn [%d] pinOut [%d]",
           MSG_OK,
           Globals::INVALID_PIN_NUMBER,
           pinIn,
           pinOut);


    qDebug("********************************************");
    qDebug("START: Test Add/Amend/Delete Reflector Wheel Rec");
    qDebug("********************************************");
    ReflectorData rd;

    rd.dispRec();
    rd.writeRec(Globals::ROW_ADD);
    qDebug("Class ReflectorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");



    rd.setAlphabetId(5);
    rd.setNotches("A ,B,D");
    rd.dispRec();
    rd.writeRec(Globals::ROW_ADD);
    qDebug("Class ReflectorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    rd.setPinRight("ABCDEF");
    rd.dispRec();
    rd.writeRec(Globals::ROW_ADD);
    qDebug("Class ReflectorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");


    rd.setName("testreflector");
    rd.dispRec();
    rd.writeRec(Globals::ROW_ADD);
    qDebug("Class ReflectorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");

    // This add should fail
    rd.dispRec();
    rd.writeRec(Globals::ROW_ADD);
    qDebug("Class ReflectorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");


    rd.setPinRight("FEDCBA");
    rd.dispRec();
    rd.writeRec(Globals::ROW_EDIT);
    qDebug("Class ReflectorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");


    rd.getReflector("testreflector");
    rd.dispRec();
    rd.writeRec(Globals::ROW_DEL);
    qDebug("Class ReflectorData\n%s", rd.lastError("\t\n").toAscii().data());
    qDebug("==========================================");


    qDebug("*********************************************");
    qDebug("FINISH: Test Add/Amend/Delete Rotor Wheel Rec");
    qDebug("*********************************************");


    debugFooter(component);
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
    if (! perform->getEnabled(TestHash::TEST_TURNOVER))
    {
        return;
    }

    QString component = "Test Turnover";
    debugHeader(component);

    Rotor r_1("I", this);
    r_1.setLetterSetting("A");
    r_1.setRingSetting(1);

    for (int i = 1; i <= r_1.getAlphabetSize(); i++)
    {
        r_1.setRingSetting(i);
        r_1.rotate();
    }

    debugFooter(component);
}


void TestHarness::testDoubleStep()
{
    QString expected;
    QString winStr;

    if (! perform->getEnabled(TestHash::TEST_DOUBLE_STEP))
    {
        return;
    }

    QString component = "Double Step rotor turnover";
    debugHeader(component);

    Machine machine("Wermacht", this);
    QMap<int, QPointer<Rotor> > rotors;


    try
    {
        qDebug("===================================");
        qDebug("START: Test machine double stepping");
        qDebug("===================================");
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

        qDebug("===================================");
        qDebug("FINISH: Test machine double stepping");
        qDebug("===================================");
    }
    catch (EnigmaException &e)
    {
        qDebug("Error Testing %s\n%s",
               "Test Machine",
               e.what().toAscii().data());
    }

    debugFooter(component);

}



int TestHarness::execValidationTest()
{
    if (! perform->getEnabled(TestHash::TEST_VALIDATION))
    {
        return 1;
    }

    QString component = "Alphabet Validation ";
    debugHeader(component);

    edb = EnigmaDatabase::getInstance();
    tdv = new TestDatabaseValidation(this);

    tdv->testAlphabetValidation();

    debugFooter(component);

    return 0;
}


int TestHarness::execAddAmendDelTest()
{

    if (! perform->getEnabled(TestHash::TEST_ADD_AMEND_DEL))
    {
        return 1;
    }

    QString component = "Add/Amend/Delete";
    debugHeader(component);

    edb = EnigmaDatabase::getInstance();


    AlphabetData ad(this);

    // Add
    /*********
    ad.setName("ABCDEF");
    ad.setAlphabet("1234567890");
    ad.displayRec(rec);
    ad.writeRec(Globals::ROW_ADD, rec);
    ******************/


    // Edit
    /******************
    ad.setName("ABCDEFXYZ");
    ad.setAlphabet("1234567890ABC");
    ad.dispRec();
    ad.writeRec(Globals::ROW_EDIT);
    ************************/

    // Delete
    // /**********************
    ad.setName("ABCDEFXYZ");
    ad.dispRec();
    ad.writeRec(Globals::ROW_DEL);
    // ************************/
    ad.dispRec();

    debugFooter(component);

    return 0;
}


void TestHarness::testLampboard()
{

    if (! perform->getEnabled(TestHash::TEST_LAMPBOARD))
    {
        return;
    }

    QString component = "Lampboard";
    debugHeader(component);

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

    debugFooter(component);
}


void TestHarness::testMachine()
{

    if (! perform->getEnabled(TestHash::TEST_MACHINE))
    {
        return;
    }

    QString component = "MACHINE with rotors I, II, III and reflector B\n"
            "all rotors are set to ring setting 1 and window char \"A\"";
    debugHeader(component);

    Machine machine("Wermacht", this);


    try
    {
        /**************
        QMap<int, QPointer<Rotor> > rotors;
        rotors.insert(1, machine.rotorFactory("I",   1, "A"));
        rotors.insert(2, machine.rotorFactory("II",  1, "A"));
        rotors.insert(3, machine.rotorFactory("III", 1, "Z"));
        machine.addRotors(rotors);
        ***********************/

        Entry *oEntry = new Entry("ENTRY", this);
        machine.addEntry(oEntry);

        machine.addRotor(1, machine.rotorFactory("I",   1, "A"));
        machine.addRotor(2, machine.rotorFactory("II",  1, "A"));
        machine.addRotor(3, machine.rotorFactory("III", 1, "Z"));

        Reflector *oReflector = new Reflector("B", this);
        machine.addReflector(oReflector);

        qDebug("=========================");
        qDebug("G is expected to map to P");
        qDebug("=========================");

        QString keyIn = "G";
        QString keyOut;

        keyOut = machine.keyPress(keyIn);

        if (keyIn == "G" && keyOut == "P")
        {
            qDebug("%s [%s] maps to [%s] Through rotors I, II, III and reflector B",
                   TestHarness::MSG_OK,
                   keyIn.toAscii().data(),
                   keyOut.toAscii().data());
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

    debugFooter(component);

}

void TestHarness::performMachineTest(MachineData *md, Globals::EDIT_MODE mode)
{
    md->dispRec();
    md->validateMachine(mode);
    qDebug("-----------------------------");
    md->dispError();
    qDebug("=============================");
}

void TestHarness::testMachineConfigurationValidation()
{

    if (! perform->getEnabled(TestHash::TEST_VALIDATE_MACHINE_CONFIG))
    {
        return;
    }

    QString component = "Validate machine configuration";
    debugHeader(component);

    MachineData *md = new MachineData(this);

    performMachineTest(md, Globals::ROW_ADD);

    md->setName("AB");
    performMachineTest(md, Globals::ROW_ADD);

    md->setName("ABCD");
    performMachineTest(md, Globals::ROW_ADD);


    md->setAlphabetId(888);
    performMachineTest(md, Globals::ROW_ADD);

    md->setAlphabetId(5);
    performMachineTest(md, Globals::ROW_ADD);

    md->setSteckerboard("Rubbish");
    performMachineTest(md, Globals::ROW_ADD);

    md->setSteckerboard("yes");
    performMachineTest(md, Globals::ROW_ADD);

    md->setSteckerboard("YES");
    performMachineTest(md, Globals::ROW_ADD);

    md->setRotorCount(-99);
    performMachineTest(md, Globals::ROW_ADD);

    md->setRotorCount(0);
    performMachineTest(md, Globals::ROW_ADD);

    md->setRotorCount(3);
    performMachineTest(md, Globals::ROW_ADD);

    debugFooter(component);
}


#pragma GCC diagnostic pop

