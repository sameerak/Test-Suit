#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <NoobaVSSAD/speednode.h>
#include <QList>
#include <NoobaVSSAD/detectedevent.h>

class TestNoobaVSSADTest : public QObject
{
    Q_OBJECT

public:
    TestNoobaVSSADTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testSpeedNode1();
    void testSpeedNode2();
    void testSpeedNode1_data();

private:
    //SpeedNode spnode;
};

TestNoobaVSSADTest::TestNoobaVSSADTest()
{
}

void TestNoobaVSSADTest::initTestCase()
{
}

void TestNoobaVSSADTest::cleanupTestCase()
{
}

void TestNoobaVSSADTest::testSpeedNode1()
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    SpeedNode spnode;
    QList<DetectedEvent> blobevents;
    QList<DetectedEvent> speedEvents;

    blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));
    speedEvents = spnode.processEventsLocal(blobevents);

    QVERIFY2(speedEvents.isEmpty(),"If no previous blobs from same tag, this should be empty");

    blobevents.clear();
    blobevents.append(DetectedEvent("blob","2,1,20.0,10.0",1.0));
    speedEvents = spnode.processEventsLocal(blobevents);
    QVERIFY2(speedEvents.count() == 1,QString("%1 events in results. should be 1").arg(speedEvents.count()).toLocal8Bit());
    //Can test the actual speed too.
}

void TestNoobaVSSADTest::testSpeedNode2()
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");

    SpeedNode spnode;
    QList<DetectedEvent> blobevents;
    QList<DetectedEvent> speedEvents;

    blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));
    speedEvents = spnode.processEventsLocal(blobevents);

    QVERIFY2(speedEvents.isEmpty(),"If no previous blobs from same tag, this should be empty");

    blobevents.clear();
    blobevents.append(DetectedEvent("blob","2,1,20.0,10.0",1.0));
    speedEvents = spnode.processEventsLocal(blobevents);
    QVERIFY2(speedEvents.count() == 1,QString("%1 events in results. should be 1").arg(speedEvents.count()).toLocal8Bit());
}

void TestNoobaVSSADTest::testSpeedNode1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_MAIN(TestNoobaVSSADTest)

#include "tst_testnoobavssadtest.moc"
