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

    qDebug("EntryPoint::exec()");

    try
    {
        edb = EnigmaDatabase::getInstance();

        //testKeyboard();
        //testSteckerboard();
        //testEntry();
        testRotor();
        //testReflector();


    }
    catch (EnigmaException &e)
    {
        qDebug("\n%s", e.what().toAscii().data());
        qApp->exit(1); // exit with error exit code
    }

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
