#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>

class UnitTest : public QObject
{
    Q_OBJECT

public:
    UnitTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();
};

UnitTest::UnitTest()
{
}

void UnitTest::initTestCase()
{
}

void UnitTest::cleanupTestCase()
{
}

void UnitTest::testCase1()
{
    //QFETCH(QString, data);
    //QVERIFY2(true, "Failure");
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

void UnitTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_MAIN(UnitTest)

#include "tst_unittest.moc"
