#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <NoobaVSSAD/speednode.h>
#include <NoobaVSSAD/distancenode.h>
#include <QList>
#include <NoobaVSSAD/detectedevent.h>
#include <NoobaVSSAD/distancechange.h>

class TestNoobaVSSADTest : public QObject
{
    Q_OBJECT

public:
    TestNoobaVSSADTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    //---test speedNode-----------
    void testSpeedNode1();
    void testSpeedNode2();
    void testSpeedNode3();
    void testSpeedNode4();
    void testSpeedNode5();
    void testSpeedNode6();
    void testSpeedNode7();
    void testSpeedNode8();

    //---test DistanceNode-----------
    void testDistanceNode1();
    void testDistanceNode2();
    //void testDistanceNode3();

    //---test DistanceNode-----------
    void testDistanceChange1();
    void testDistanceChange2();
    void testDistanceChange3();
    void testDistanceChange4();

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

void TestNoobaVSSADTest::testSpeedNode1()//test number of results
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

void TestNoobaVSSADTest::testSpeedNode2()//
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

void TestNoobaVSSADTest::testSpeedNode3()//Test for result when a blob is presen6t in two consecative frames
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
    blobevents.append(DetectedEvent("blob","2,1,13.0,14.0",1.0));
    speedEvents = spnode.processEventsLocal(blobevents);
    QVERIFY2(speedEvents.count() == 1,QString("%1 events in results. should be 1").arg(speedEvents.count()).toLocal8Bit());

    QVERIFY2(speedEvents.first().getMessage().split(",").at(0).toInt() == 2, "Frame Number should be 2");
    QVERIFY2(speedEvents.first().getMessage().split(",").at(1).toInt() == 1, "Frame Number should be 1" );
    QVERIFY2(speedEvents.first().getMessage().split(",").at(2).toFloat() == 5, "Speed should be 5" );

}

void TestNoobaVSSADTest::testSpeedNode4()//test for same blob in several frames
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
    blobevents.append(DetectedEvent("blob","2,1,13.0,14.0",1.0));
    blobevents.append(DetectedEvent("blob","3,1,16.0,18.0",1.0));
    speedEvents = spnode.processEventsLocal(blobevents);
    QVERIFY2(speedEvents.count() == 2,QString("%1 events in results. should be 2").arg(speedEvents.count()).toLocal8Bit());

    QVERIFY2(speedEvents.at(0).getMessage().split(",").at(0).toInt() == 2, QString("Frame Number calculated as %1 should be 3").arg(speedEvents.at(0).getMessage().split(",").at(0)).toLocal8Bit() );
    QVERIFY2(speedEvents.at(0).getMessage().split(",").at(1).toInt() == 1, QString("Blob Id calculated as %1 should be 1").arg(speedEvents.at(1).getMessage().split(",").at(1)).toLocal8Bit() );
    QVERIFY2(speedEvents.at(0).getMessage().split(",").at(2).toFloat() == 5, QString("Speed calculated as %1 should be 5").arg(speedEvents.at(1).getMessage().split(",").at(2)).toLocal8Bit() );

    QVERIFY2(speedEvents.at(1).getMessage().split(",").at(0).toInt() == 3, QString("Frame Number calculated as %1 should be 3").arg(speedEvents.at(0).getMessage().split(",").at(0)).toLocal8Bit() );
    QVERIFY2(speedEvents.at(1).getMessage().split(",").at(1).toInt() == 1, QString("Blob Id calculated as %1 should be 1").arg(speedEvents.at(1).getMessage().split(",").at(1)).toLocal8Bit() );
    QVERIFY2(speedEvents.at(1).getMessage().split(",").at(2).toFloat() == 5, QString("Speed calculated as %1 should be 5").arg(speedEvents.at(1).getMessage().split(",").at(2)).toLocal8Bit() );

}

void TestNoobaVSSADTest::testSpeedNode5()//test case for larger diffrence
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
    blobevents.append(DetectedEvent("blob","2,1,16.0,18.0",1.0));
    blobevents.append(DetectedEvent("blob","3,1,16.0,18.0",1.0));
    speedEvents = spnode.processEventsLocal(blobevents);
    QVERIFY2(speedEvents.count() == 2,QString("%1 events in results. should be 2").arg(speedEvents.count()).toLocal8Bit());

    QVERIFY2(speedEvents.at(0).getMessage().split(",").at(0).toInt() == 2, QString("Frame Number calculated as %1 should be 3").arg(speedEvents.at(0).getMessage().split(",").at(0)).toLocal8Bit() );
    QVERIFY2(speedEvents.at(0).getMessage().split(",").at(1).toInt() == 1, QString("Blob Id calculated as %1 should be 1").arg(speedEvents.at(1).getMessage().split(",").at(1)).toLocal8Bit() );
    QVERIFY2(speedEvents.at(0).getMessage().split(",").at(2).toFloat() == 10, QString("Speed calculated as %1 should be 5").arg(speedEvents.at(1).getMessage().split(",").at(2)).toLocal8Bit() );

    QVERIFY2(speedEvents.at(1).getMessage().split(",").at(0).toInt() == 3, QString("Frame Number calculated as %1 should be 3").arg(speedEvents.at(0).getMessage().split(",").at(0)).toLocal8Bit() );
    QVERIFY2(speedEvents.at(1).getMessage().split(",").at(1).toInt() == 1, QString("Blob Id calculated as %1 should be 1").arg(speedEvents.at(1).getMessage().split(",").at(1)).toLocal8Bit() );
    QVERIFY2(speedEvents.at(1).getMessage().split(",").at(2).toFloat() ==5, QString("Speed calculated as %1 should be 5").arg(speedEvents.at(1).getMessage().split(",").at(2)).toLocal8Bit() );

}

void TestNoobaVSSADTest::testSpeedNode6()//test case for different blobs in differenct frames
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
    blobevents.append(DetectedEvent("blob","2,2,13.0,14.0",1.0));
    blobevents.append(DetectedEvent("blob","3,3,16.0,18.0",1.0));
    speedEvents = spnode.processEventsLocal(blobevents);
    QVERIFY2(speedEvents.count() == 0,QString("%1 events in results. should be 0").arg(speedEvents.count()).toLocal8Bit());

}

void TestNoobaVSSADTest::testSpeedNode7()//test case for same position in two frames
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
    blobevents.append(DetectedEvent("blob","2,1,10.0,10.0",1.0));
    blobevents.append(DetectedEvent("blob","3,1,16.0,18.0",1.0));
    speedEvents = spnode.processEventsLocal(blobevents);
    QVERIFY2(speedEvents.count() == 2,QString("%1 events in results. should be 2").arg(speedEvents.count()).toLocal8Bit());

    QVERIFY2(speedEvents.at(0).getMessage().split(",").at(0).toInt() == 2, QString("Frame Number calculated as %1 should be 3").arg(speedEvents.at(0).getMessage().split(",").at(0)).toLocal8Bit() );
    QVERIFY2(speedEvents.at(0).getMessage().split(",").at(1).toInt() == 1, QString("Blob Id calculated as %1 should be 1").arg(speedEvents.at(1).getMessage().split(",").at(1)).toLocal8Bit() );
    QVERIFY2(speedEvents.at(0).getMessage().split(",").at(2).toFloat() == 0, QString("Speed calculated as %1 should be 0").arg(speedEvents.at(1).getMessage().split(",").at(2)).toLocal8Bit() );

 }

void TestNoobaVSSADTest::testSpeedNode8()//test case for same position in two frames
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
    blobevents.append(DetectedEvent("blob","2,1,10.0,10.0",1.0));

    blobevents.append(DetectedEvent("blob","3,1,16.0,18.0",1.0));
    //delete this check count for 1 and see
    speedEvents = spnode.processEventsLocal(blobevents);
    QVERIFY2(speedEvents.count() == 2,QString("%1 events in results. should be 2").arg(speedEvents.count()).toLocal8Bit());

    QVERIFY2(speedEvents.at(0).getMessage().split(",").at(0).toInt() == 2, QString("Frame Number calculated as %1 should be 3").arg(speedEvents.at(0).getMessage().split(",").at(0)).toLocal8Bit() );
    QVERIFY2(speedEvents.at(0).getMessage().split(",").at(1).toInt() == 1, QString("Blob Id calculated as %1 should be 1").arg(speedEvents.at(1).getMessage().split(",").at(1)).toLocal8Bit() );
    QVERIFY2(speedEvents.at(0).getMessage().split(",").at(2).toFloat() == 0, QString("Speed calculated as %1 should be 0").arg(speedEvents.at(1).getMessage().split(",").at(2)).toLocal8Bit() );

 }

//-----------------------Test distance node-----------------------------------------------------------------------------
void TestNoobaVSSADTest::testDistanceNode1()//test number of results
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    DistanceNode distnode;
    QList<DetectedEvent> blobevents;
    QList<DetectedEvent> distanceEvents;

    blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));
    distanceEvents = distnode.processEventsLocal(blobevents);

    QVERIFY2(distanceEvents.isEmpty(),"If no previous blobs from same tag, this should be empty");

    //blobevents.clear();
    blobevents.append(DetectedEvent("blob","2,1,20.0,30.0",1.0));
    distanceEvents = distnode.processEventsLocal(blobevents);
    QVERIFY2(distanceEvents.count() == 1,QString("%1 events in results. should be 1").arg(distanceEvents.count()).toLocal8Bit());
    //Can test the actual speed too.
}

void TestNoobaVSSADTest::testDistanceNode2()//test number of results
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    DistanceNode distnode;
    QList<DetectedEvent> blobevents;
    QList<DetectedEvent> distanceEvents;

    blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));
    distanceEvents = distnode.processEventsLocal(blobevents);

    QVERIFY2(distanceEvents.isEmpty(),"If no previous blobs from same tag, this should be empty");

    //blobevents.clear();
    blobevents.append(DetectedEvent("blob","2,1,13.0,14.0",1.0));
    distanceEvents = distnode.processEventsLocal(blobevents);
    QVERIFY2(distanceEvents.count() == 1,QString("%1 events in results. should be 1").arg(distanceEvents.count()).toLocal8Bit());
    //Can test the actual speed too.
    //QVERIFY2(distanceEvents.at(0).getMessage().split(",").at(0).toInt() == 2, QString("Blob Id calculated as %1 should be 1").arg(distanceEvents.at(0).getMessage().split(",").at(2).toFloat() ).toLocal8Bit() );


    QVERIFY2(distanceEvents.at(0).getMessage().split(",").at(0).toInt() == 1, QString("Frame Number calculated as %1 should be 2").arg(distanceEvents.at(0).getMessage().split(",").at(0)).toLocal8Bit() );
    QVERIFY2(distanceEvents.at(0).getMessage().split(",").at(1).split("-").at(0).toInt() == 1, QString("Blob Id calculated as %1 should be 1").arg(distanceEvents.at(0).getMessage().split(",").at(1).split("-").at(0)).toLocal8Bit() );
    QVERIFY2(distanceEvents.at(0).getMessage().split(",").at(1).split("-").at(1).toInt() == 1, QString("Blob Id calculated as %1 should be 1").arg(distanceEvents.at(0).getMessage().split(",").at(1).split("-").at(1)).toLocal8Bit() );
    QVERIFY2(distanceEvents.at(0).getMessage().split(",").at(2).toFloat() == 5, "Distance calculated should be 0");//QString("Speed calculated as %7 should be 0").arg(distanceEvents.at(1).getMessage().split(",").at(2)).toLocal8Bit() );

}

//-----------------------Test distancechangenode-----------------------------------------------------------------------------
void TestNoobaVSSADTest::testDistanceChange1()//test two inputs
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    DistanceChange distchangenode;
    QList<DetectedEvent> blobevents;
    QList<DetectedEvent> distchangeEvents;

    blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));
    distchangeEvents = distchangenode.processEventsLocal(blobevents);

    QVERIFY2(distchangeEvents.isEmpty(),"If no previous blobs from same tag, this should be empty");

    //blobevents.clear();
    blobevents.append(DetectedEvent("blob","2,1,20.0,30.0",1.0));
    distchangeEvents = distchangenode.processEventsLocal(blobevents);
    QVERIFY2(distchangeEvents.count() == 0,QString("%1 events in results. should be 1").arg(distchangeEvents.count()).toLocal8Bit());
    //Can test the actual speed too.
}

void TestNoobaVSSADTest::testDistanceChange2()//test two inputs
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    DistanceChange distchangenode;
    DistanceNode distnode;

    QList<DetectedEvent> blobevents;
    QList<DetectedEvent> distEvents;

    QList<DetectedEvent> distchangeEvents;

    blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));
    //distEvents = distnode.processEventsLocal(blobevents);
    //distchangeEvents = distchangenode.processEventsLocal(blobevents);


    QVERIFY2(distchangeEvents.isEmpty(),"If no previous blobs from same tag, this should be empty");
    QVERIFY2(distEvents.isEmpty(),"If no previous blobs from same tag, this should be empty");

    blobevents.clear();
    blobevents.append(DetectedEvent("blob","1,1,20.0,30.0",1.0));
    blobevents.append(DetectedEvent("blob","1,1,25.0,35.0",1.0));

    distEvents = distnode.processEventsLocal(blobevents);
    distchangeEvents = distchangenode.processEventsLocal(distEvents);
    //qDebug()<<"00000--------";
    //connect(&distnode, SIGNAL(generateEvent(QList<DetectedEvent>)), &distchangenode, SLOT(captureEvent(QList<DetectedEvent>)));

    //blobevents.clear();
    blobevents.append(DetectedEvent("blob","1,1,30.0,40.0",1.0));
    blobevents.append(DetectedEvent("blob","1,1,35.0,45.0",1.0));
    distEvents = distnode.processEventsLocal(blobevents);
    distchangeEvents = distchangenode.processEventsLocal(distEvents);

    QVERIFY2(distEvents.count() ==6,QString("%1 events in results. should be 0").arg(distEvents.count()).toLocal8Bit());
    QVERIFY2(distchangeEvents.count() == 0,QString("%1 events in results. should be 0").arg(distchangeEvents.count()).toLocal8Bit());
    //QVERIFY2(distchangeEvents.last().getMessage().split(",").at(0).toInt() == 5,QString("%1 as the result. should be 5").arg(distchangeEvents.first().getMessage().split(",").at(0)).toLocal8Bit());

    //
}

void TestNoobaVSSADTest::testDistanceChange3()//test two inputs
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    DistanceChange distchangenode;
    DistanceNode distnode;

    QList<DetectedEvent> blobevents;
    QList<DetectedEvent> distEvents;

    QList<DetectedEvent> distchangeEvents;

    blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));
    //distEvents = distnode.processEventsLocal(blobevents);
    //distchangeEvents = distchangenode.processEventsLocal(blobevents);


    QVERIFY2(distchangeEvents.isEmpty(),"If no previous blobs from same tag, this should be empty");
    QVERIFY2(distEvents.isEmpty(),"If no previous blobs from same tag, this should be empty");

    blobevents.clear();
    blobevents.append(DetectedEvent("blob","1,1,20.0,30.0",1.0));
    blobevents.append(DetectedEvent("blob","2,1,25.0,35.0",1.0));

    distEvents = distnode.processEventsLocal(blobevents);
    distchangeEvents = distchangenode.processEventsLocal(distEvents);
    //qDebug()<<"00000--------";
    //connect(&distnode, SIGNAL(generateEvent(QList<DetectedEvent>)), &distchangenode, SLOT(captureEvent(QList<DetectedEvent>)));

    //blobevents.clear();
    blobevents.append(DetectedEvent("blob","3,1,30.0,40.0",1.0));
    blobevents.append(DetectedEvent("blob","4,1,35.0,45.0",1.0));
    distEvents = distnode.processEventsLocal(blobevents);
    distchangeEvents = distchangenode.processEventsLocal(distEvents);

    QVERIFY2(distEvents.count() == 6,QString("%1 events in results. should be 6").arg(distEvents.count()).toLocal8Bit());
    QVERIFY2(distchangeEvents.count() == 0,QString("%1 events in results. should be 0").arg(distchangeEvents.count()).toLocal8Bit());

    //
}

void TestNoobaVSSADTest::testDistanceChange4()//test two inputs
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    DistanceChange distchangenode;
    DistanceNode distnode;

    QList<DetectedEvent> blobevents;
    QList<DetectedEvent> distchangeEvents;

    blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));
    distchangeEvents = distchangenode.processEventsLocal(blobevents);


    QVERIFY2(distchangeEvents.isEmpty(),"If no previous blobs from same tag, this should be empty");

    blobevents.clear();
    blobevents.append(DetectedEvent("blob","1,1,20.0,30.0",1.0));
    blobevents.append(DetectedEvent("blob","2,1,25.0,35.0",1.0));

    //qDebug()<<"00000--------";
    //connect(&distnode, SIGNAL(generateEvent(QList<DetectedEvent>)), &distchangenode, SLOT(captureEvent(QList<DetectedEvent>)));

    //blobevents.clear();
    blobevents.append(DetectedEvent("blob","3,1,30.0,40.0",1.0));
    blobevents.append(DetectedEvent("blob","4,1,35.0,45.0",1.0));

    distchangeEvents = distchangenode.processEventsLocal(blobevents);

    //QVERIFY2(distEvents.count() ==0,QString("%1 events in results. should be 0").arg(distEvents.count()).toLocal8Bit());
    QVERIFY2(distchangeEvents.count() == 0,QString("%1 events in results. should be 0").arg(distchangeEvents.count()).toLocal8Bit());

    //
}

void TestNoobaVSSADTest::testSpeedNode1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_MAIN(TestNoobaVSSADTest)

#include "tst_testnoobavssadtest.moc"
