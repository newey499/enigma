/************************************************************************
Copyright Chris Newey 2013

enigmasim@outlook.com

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

#include "testharness.h"

const char *TestHarness::MSG_FAIL = "FAIL:: Should throw exception :: ";
const char *TestHarness::MSG_OK   = "SUCCESS:: ";
const char *TestHarness::MSG_OK_FAIL = "SUCCESS:: Should throw exception :: ";

TestHarness::TestHarness(QObject *parent) :
    QObject(parent)
{
}


int TestHarness::exec()
{
    int result = 0;
    QString component;
    qDebug("TestHarness::exec()");
    edb = EnigmaDatabase::getInstance();

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
        qDebug("=======================================================");
        qDebug("Test Configuration with rotors I, II and III Relector B");
        qDebug("=======================================================");
        qDebug("The basic Enigma has been loaded with the rotors I, II, III.");
        qDebug("The right-hand rotor R is III");
        qDebug("=======================================================");
        qDebug("test Rotor III - map right to left input G maps to C");

        Entry entry("ENTRY", this);

        int pinIn;
        int pinOut;
        int ringSetting;
        int oldLetterOffset;
        QString charIn;
        QString charOut;

        component = "Machine with rotors I, II, III and reflector B";
        debugHeader(component);

        QString rotorName;
        rotorName = "III";

        Rotor r_1("I", this);
        r_1.setLetterSetting("A");
        r_1.setRingSetting(1);

        Rotor r_2("II", this);
        r_2.setLetterSetting("A");
        r_2.setRingSetting(1);

        Rotor r_3("III", this);
        r_3.setLetterSetting("A");
        r_3.setRingSetting(1);

        Reflector reflector("B", this);

        charIn = "G";
        pinIn = entry.mapCharToPin(charIn);
        qDebug("Entry maps [%s] to pin [%d] should be 7",
               charIn.toAscii().data(),
               pinIn);

        pinOut = r_3.mapRightToLeft(pinIn);
        qDebug("Rotor III maps right to left [%d] -> [%d] should be 3",
               pinIn,
               pinOut);

        pinIn = pinOut;
        pinOut = r_2.mapRightToLeft(pinIn);
        qDebug("Rotor II maps right to left [%d] -> [%d] should be 4",
               pinIn,
               pinOut);

        pinIn = pinOut;
        pinOut = r_1.mapRightToLeft(pinIn);
        qDebug("Rotor I maps right to left [%d] -> [%d] should be 6",
               pinIn,
               pinOut);


        pinIn = pinOut;
        pinOut = reflector.map(pinIn);
        qDebug("Reflector B maps [%d] -> [%d] should be 19",
               pinIn,
               pinOut);


        pinIn = pinOut;
        pinOut = r_1.mapLeftToRight(pinIn);
        qDebug("Rotor I maps left to right [%d] -> [%d] should be 19",
               pinIn,
               pinOut);

        pinIn = pinOut;
        pinOut = r_2.mapLeftToRight(pinIn);
        qDebug("Rotor II maps left to right [%d] -> [%d] should be 5",
               pinIn,
               pinOut);

        pinIn = pinOut;
        pinOut = r_3.mapLeftToRight(pinIn);
        qDebug("Rotor III maps left to right [%d] -> [%d] should be 16",
               pinIn,
               pinOut);

        pinIn = pinOut;
        charOut = entry.mapPinToChar(pinIn);
        qDebug("Entry maps pin [%d] to char [%s] should be P",
               pinIn,
               charOut.toAscii().data());

        qDebug("%s [G] maps to [P] Through rotors I, II, III and reflector B",
               TestHarness::MSG_OK);

        debugFooter(component);
    }
    catch (EnigmaException &e)
    {
        qDebug("Error Testing %s\n%s",
               component.toAscii().data(),
               e.what().toAscii().data());
        debugFooter(component);
    }



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

    //Reflector reflector("REFLECTORNOMAP", this);
    Reflector reflector("REFLECTORREVERSE", this);

    int pinIn;
    int pinOut;


    pinIn = 1;
    pinOut = reflector.map(pinIn);
    qDebug("Reflector::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);

    pinIn = 2;
    pinOut = reflector.map(pinIn);
    qDebug("Reflector::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);

    pinIn = 25;
    pinOut = reflector.map(pinIn);
    qDebug("Reflector::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);

    pinIn = 26;
    pinOut = reflector.map(pinIn);
    qDebug("Reflector::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);

    /***************
    pinIn = 27;
    pinOut = reflector.map(pinIn);
    qDebug("Reflector::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);
    ******************/
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
