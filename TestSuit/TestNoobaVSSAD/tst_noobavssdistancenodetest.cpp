#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <NoobaVSSAD/speednode.h>
#include <QList>
#include <NoobaVSSAD/detectedevent.h>

class TestNoobaVSSADDistanceNodeTest : public QObject
{
    Q_OBJECT

public:
    TestNoobaVSSADDistanceNodeTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testDistanceNode1();
    void testDistanceNode2();
    void testDistanceNode3();
    void testDistanceNode4();
    void testDistanceNode5();
    void testDistanceNode6();
    void testDistanceNode7();
    void testSpeedNode1_data();

private:
    //SpeedNode spnode;
};

TestNoobaVSSADDistanceNodeTest::TestNoobaVSSADDistanceNodeTest()
{
}

void TestNoobaVSSADDistanceNodeTest::initTestCase()
{
}

void TestNoobaVSSADDistanceNodeTest::cleanupTestCase()
{
}




void TestNoobaVSSADDistanceNodeTest::testSpeedNode1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_MAIN(TestNoobaVSSADDistanceNodeTest)

#include "tst_testnoobavssadtest.moc"

