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

#include "enigmadatabase.h"
#include "entry.h"
#include "rotor.h"
#include "reflector.h"
#include "keyboard.h"
#include "steckerboard.h"

#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QVariant>

//#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>




class UnitTest : public QObject
{
    Q_OBJECT

public:
    UnitTest();

private Q_SLOTS:
    //void initTestCase();
    //void cleanupTestCase();
    void testStrUpperCase();
    void testStrUpperCase_data();

};


UnitTest::UnitTest()
{
}

/********
void UnitTest::initTestCase()
{
}
**************/

/********
void UnitTest::cleanupTestCase()
{
}
**************/

// ========================================================

void UnitTest::testStrUpperCase()
{
    QFETCH(QString, data);
    QFETCH(QString, result);

    /*************
    // Standard Test
    QVERIFY(data.toUpper() == "HELLO");
    ********************/
    // Verbose Test
    QCOMPARE(data.toUpper(), result);
}

void UnitTest::testStrUpperCase_data()
{
    QTest::addColumn<QString>("data");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello" << "HELLO";
    QTest::newRow("mixed")     << "Hello" << "HELLO";
    QTest::newRow("all upper") << "HELLO" << "HELLO";
}

// ========================================================



// ========================================================

QTEST_MAIN(UnitTest)

#include "tst_unittest.moc"
