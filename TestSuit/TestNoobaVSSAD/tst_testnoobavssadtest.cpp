#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <NoobaVSSAD/speednode.h>
#include <NoobaVSSAD/distancenode.h>
#include <QList>
#include <NoobaVSSAD/detectedevent.h>
#include <NoobaVSSAD/distancechange.h>
#include <NoobaVSSAD/filewriternode.h>
#include <testdatanode.h>

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
    void testSpeedNode9();
    void testSpeedNodeSignalSlot();

    //---test DistanceNode-----------
    void testDistanceNode1();
    void testDistanceNode2();
    void testDistanceNodeSiglanSlot();
    //void testDistanceNode3();

    //---test DistanceNode-----------
    void testDistanceChange1();
    void testDistanceChange2();
    void testDistanceChange3();
    void testDistanceChange4();

    //---test DistanceNode-----------
    void testFileWriter1();
    void testFileWriter2();
    void testFileWriter3();
    void testFileWriter4();
    void testFileWriter5();
    void testFileWriter6();
    void testSpeedNode1_data();

private:
    //SpeedNode spnode;
    testdatanode testData;
    QList<DetectedEvent> capturedEvent;

public slots:
    //void onCaptureEventFirst(QList<DetectedEvent> captured_event);
    void onCaptureEvent(QList<DetectedEvent> captured_event);

signals:
    void generateEvent(QList<DetectedEvent> generated_event);

};

void TestNoobaVSSADTest::onCaptureEvent(QList<DetectedEvent> captured_event){
   capturedEvent = captured_event;
}

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

void TestNoobaVSSADTest::testSpeedNode9()//test case for same position in two frames
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");

    SpeedNode spnode;

    testData.blobevents.clear();//clear all the data in testdata->blobevents list
    testData.blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));//add one item to teastdata->blob events

    testData.speedEvents = spnode.processEventsLocal(testData.blobevents);//calculate speed using speed node

    QVERIFY2(testData.speedEvents.isEmpty(),"If no previous blobs from same tag, this should be empty");

    testData.blobevents.clear();//clear blob events data
    testData.blobevents.append(DetectedEvent("blob","2,1,10.0,10.0",1.0));//add one detectedevents object to testdata->blobevents
    testData.blobevents.append(DetectedEvent("blob","3,1,16.0,18.0",1.0));//add second detectedevents object to testdata->blobevents
    //delete this check count for 1 and see
    testData.speedEvents = spnode.processEventsLocal(testData.blobevents);//calculate speed using speed node

    QVERIFY2(testData.speedEvents.count() == 2,QString("%1 events in results. should be 2").arg(testData.speedEvents.count()).toLocal8Bit());

    QVERIFY2(testData.speedEvents.at(0).getMessage().split(",").at(0).toInt() == 2, QString("Frame Number calculated as %1 should be 3").arg(testData.speedEvents.at(0).getMessage().split(",").at(0)).toLocal8Bit() );
    QVERIFY2(testData.speedEvents.at(0).getMessage().split(",").at(1).toInt() == 1, QString("Blob Id calculated as %1 should be 1").arg(testData.speedEvents.at(1).getMessage().split(",").at(1)).toLocal8Bit() );
    QVERIFY2(testData.speedEvents.at(0).getMessage().split(",").at(2).toFloat() == 0, QString("Speed calculated as %1 should be 0").arg(testData.speedEvents.at(1).getMessage().split(",").at(2)).toLocal8Bit() );

 }

void TestNoobaVSSADTest::testSpeedNodeSignalSlot()//test case for same position in two frames
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");

    SpeedNode spnode;
    DetectedEvent newEvent;

    connect(this, SIGNAL(generateEvent(QList<DetectedEvent>)), &spnode, SLOT(captureEvent(QList<DetectedEvent>)));
    connect(&spnode, SIGNAL(generateEvent(QList<DetectedEvent>)), this, SLOT(onCaptureEvent(QList<DetectedEvent>)));

    testData.resetAllLists();//empty all the test data

    testData.blobevents.clear();//clear all the data in testdata->blobevents list
    newEvent = DetectedEvent("blob","1,1,10.0,10.0",1.0);
    testData.addBLobEvents(newEvent);//add one item to teastdata->blob events

    emit generateEvent(testData.blobevents);
   // testData.speedEvents = spnode.processEventsLocal(testData.blobevents);//calculate speed using speed node
    testData.speedEvents = capturedEvent;//calculate speed using speed node

    QVERIFY2(capturedEvent.isEmpty(),"If no previous blobs from same tag, this should be empty");

    testData.resetAllLists();

    testData.blobevents.clear();//clear blob events data
    testData.blobevents.append(DetectedEvent("blob","2,1,10.0,10.0",1.0));//add one detectedevents object to testdata->blobevents
    testData.blobevents.append(DetectedEvent("blob","3,1,16.0,18.0",1.0));//add second detectedevents object to testdata->blobevents

    emit generateEvent(testData.blobevents);
   // testData.speedEvents = spnode.processEventsLocal(testData.blobevents);//calculate speed using speed node
    testData.speedEvents = capturedEvent;//calculate speed using speed node


    //testData.speedEvents = spnode.processEventsLocal(testData.blobevents);//calculate speed using speed node

    QVERIFY2(testData.speedEvents.count() == 2,QString("%1 events in results. should be 2").arg(testData.speedEvents.count()).toLocal8Bit());

    QVERIFY2(testData.speedEvents.at(0).getMessage().split(",").at(0).toInt() == 2, QString("Frame Number calculated as %1 should be 3").arg(testData.speedEvents.at(0).getMessage().split(",").at(0)).toLocal8Bit() );
    QVERIFY2(testData.speedEvents.at(0).getMessage().split(",").at(1).toInt() == 1, QString("Blob Id calculated as %1 should be 1").arg(testData.speedEvents.at(1).getMessage().split(",").at(1)).toLocal8Bit() );
    QVERIFY2(testData.speedEvents.at(0).getMessage().split(",").at(2).toFloat() == 0, QString("Speed calculated as %1 should be 0").arg(testData.speedEvents.at(1).getMessage().split(",").at(2)).toLocal8Bit() );

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

void TestNoobaVSSADTest::testDistanceNodeSiglanSlot()//test number of results
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    DistanceNode distnode;
    //QList<DetectedEvent> blobevents;
    QList<DetectedEvent> distanceEvents;
    DetectedEvent newBlob;

    testData.resetAllLists();

    connect(this, SIGNAL(generateEvent(QList<DetectedEvent>)), &distnode, SLOT(captureEvent(QList<DetectedEvent>)));
    connect(&distnode, SIGNAL(generateEvent(QList<DetectedEvent>)), this, SLOT(onCaptureEvent(QList<DetectedEvent>)));



   // blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));
    newBlob= DetectedEvent("blob","1,1,10.0,10.0",1.0);
    testData.addBLobEvents(newBlob);;
   //distanceEvents = distnode.processEventsLocal(blobevents);

    capturedEvent.clear();
    emit generateEvent(testData.getBlobEvents());

    distanceEvents = capturedEvent;

    QVERIFY2(distanceEvents.isEmpty(),"If no previous blobs from same tag, this should be empty");

    //blobevents.clear();
    //blobevents.append(DetectedEvent("blob","2,1,13.0,14.0",1.0));
    newBlob = DetectedEvent("blob","2,1,13.0,14.0",1.0);
    testData.addBLobEvents(newBlob);

    emit generateEvent(testData.getBlobEvents());

    distanceEvents = capturedEvent;
    //distanceEvents = distnode.processEventsLocal(blobevents);
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


//-----------------------Test Filewritenode-----------------------------------------------------------------------------

void TestNoobaVSSADTest::testFileWriter1()//to test whether a new file is created when non empty detected events list is passed into
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    FileWriterNode filewriternode;

    QDir dir(QDir::home());
    if(!dir.exists("NoobaVSS_testdata")){
        dir.mkdir("NoobaVSS_testdata");
    }
    dir.cd("NoobaVSS_testdata");
    if(!dir.exists("data")){
        dir.mkdir("data");
    }
    dir.cd("data");
    if(!dir.exists("text")){
        dir.mkdir("text");
    }
    dir.cd("text");


    QDateTime timestamp = QDateTime::currentDateTime();// current time is taken in to create a unique file name that is already not created
    QString test_file =  dir.absoluteFilePath(timestamp.currentDateTime().toString("yyyy-MM-dd-hhmm") + "-test_filewriter_node.txt");

    //QString test_file = dir.absoluteFilePath("testing_01");
    QList<DetectedEvent> blobevents;
    blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));//set data to write into file

    filewriternode.openFile(test_file);//open a file with the above name using filewriter object filewriternode
    filewriternode.processEvents(blobevents);//write data to the file
    filewriternode.closeFile();//close the file

    QFile file;

    if(file.isOpen()){
        file.close();
    }
    file.setFileName(test_file);

    //QTextStream in_stream;
    //in_stream.setDevice(&file);

    QVERIFY2(file.open(QIODevice::ReadOnly | QIODevice::Text),"File named "+test_file.toLocal8Bit()+" has not created");

}

void TestNoobaVSSADTest::testFileWriter2()//to test whether a new file is not created when an empty detected events list is passed into
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    FileWriterNode filewriternode;

    QDir dir(QDir::home());
    if(!dir.exists("NoobaVSS_testdata")){
        dir.mkdir("NoobaVSS_testdata");
    }
    dir.cd("NoobaVSS_testdata");
    if(!dir.exists("data")){
        dir.mkdir("data");
    }
    dir.cd("data");
    if(!dir.exists("text")){
        dir.mkdir("text");
    }
    dir.cd("text");


    QDateTime timestamp = QDateTime::currentDateTime();// current time is taken in to create a unique file name that is already not created
    QString test_file =  dir.absoluteFilePath(timestamp.currentDateTime().toString("yyyy-MM-dd-hhmm") + "-test_filewriter_node.txt");

    //QString test_file = dir.absoluteFilePath("testing_01");
    QList<DetectedEvent> blobevents;
    //blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));

    filewriternode.openFile(test_file);//open a file with the above name using filewriter object filewriternode
    filewriternode.processEvents(blobevents);//write data to the file
    filewriternode.closeFile();//close the file

    QFile file;
    //QTextStream in_stream;
    //in_stream.setDevice(&file);


    if(file.isOpen()){
        file.close();
    }
    file.setFileName(test_file);

    //QTextStream in_stream;
    //in_stream.setDevice(&file);

    QVERIFY2(file.open(QIODevice::ReadOnly | QIODevice::Text),"File named "+test_file.toLocal8Bit()+" should not be created, but is has created");

}

void TestNoobaVSSADTest::testFileWriter3()//to test whether the data written into file using filewritenode is correct
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    FileWriterNode filewriternode;

    QDir dir(QDir::home());
    if(!dir.exists("NoobaVSS_testdata")){
        dir.mkdir("NoobaVSS_testdata");
    }
    dir.cd("NoobaVSS_testdata");
    if(!dir.exists("data")){
        dir.mkdir("data");
    }
    dir.cd("data");
    if(!dir.exists("text")){
        dir.mkdir("text");
    }
    dir.cd("text");


    QDateTime timestamp = QDateTime::currentDateTime();// current time is taken in to create a unique file name that is already not created
    QString test_file =  dir.absoluteFilePath(timestamp.currentDateTime().toString("yyyy-MM-dd-hhmm") + "-test_filewriter_node.txt");

    //QString test_file = dir.absoluteFilePath("testing_01");
    QList<DetectedEvent> blobevents;
    blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));

    filewriternode.openFile(test_file);//open a file with the above name using filewriter object filewriternode
    filewriternode.processEvents(blobevents);//write data to the file
    filewriternode.closeFile();//close the file

    QFile file;

    if(file.isOpen()){
        file.close();
    }
    file.setFileName(test_file);

    QTextStream in_stream;
    in_stream.setDevice(&file);

    QVERIFY2(file.open(QIODevice::ReadOnly | QIODevice::Text),"File named "+test_file.toLocal8Bit()+" has not created");
    QString read = in_stream.readLine(0);

    QVERIFY2(read.toLocal8Bit()== "blob,1,1,10.0,10.0" ,read.toLocal8Bit() + " is read from the file, but should be blob,1,1,10.0,10.0");


}

void TestNoobaVSSADTest::testFileWriter4()//to test whether the data written into file using filewritenode is correct
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    FileWriterNode filewriternode;

    QDir dir(QDir::home());
    if(!dir.exists("NoobaVSS_testdata")){
        dir.mkdir("NoobaVSS_testdata");
    }
    dir.cd("NoobaVSS_testdata");
    if(!dir.exists("data")){
        dir.mkdir("data");
    }
    dir.cd("data");
    if(!dir.exists("text")){
        dir.mkdir("text");
    }
    dir.cd("text");


    QDateTime timestamp = QDateTime::currentDateTime();// current time is taken in to create a unique file name that is already not created
    QString test_file =  dir.absoluteFilePath(timestamp.currentDateTime().toString("yyyy-MM-dd-hhmm") + "-test_filewriter_node.txt");

    //QString test_file = dir.absoluteFilePath("testing_01");
    QList<DetectedEvent> blobevents;
    blobevents.append(DetectedEvent("Test","This is test Line 1",1.0));
    blobevents.append(DetectedEvent("Test","This is test Line 2",1.0));
    blobevents.append(DetectedEvent("Test","This is test Line 3",1.0));

    filewriternode.openFile(test_file);//open a file with the above name using filewriter object filewriternode
    filewriternode.processEvents(blobevents);//write data to the file
    filewriternode.closeFile();//close the file

    QFile file;

    if(file.isOpen()){
        file.close();
    }
    file.setFileName(test_file);

    QTextStream in_stream;
    in_stream.setDevice(&file);

    QVERIFY2(file.open(QIODevice::ReadOnly | QIODevice::Text),"File named "+test_file.toLocal8Bit()+" has not created");
    QString read = in_stream.readLine(0);

    QVERIFY2(read.toLocal8Bit()== "Test,This is test Line 1" ,read.toLocal8Bit() + " is read from the file, but should be Test,This is test Line 1");


}

void TestNoobaVSSADTest::testFileWriter5()//to test whether the size of written file is same as input
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    FileWriterNode filewriternode;

    QDir dir(QDir::home());
    if(!dir.exists("NoobaVSS_testdata")){
        dir.mkdir("NoobaVSS_testdata");
    }
    dir.cd("NoobaVSS_testdata");
    if(!dir.exists("data")){
        dir.mkdir("data");
    }
    dir.cd("data");
    if(!dir.exists("text")){
        dir.mkdir("text");
    }
    dir.cd("text");


    QDateTime timestamp = QDateTime::currentDateTime();// current time is taken in to create a unique file name that is already not created
    QString test_file =  dir.absoluteFilePath(timestamp.currentDateTime().toString("yyyy-MM-dd-hhmm") + "-test_filewriter_node.txt");

    //QString test_file = dir.absoluteFilePath("testing_01");
    QList<DetectedEvent> blobevents;

    blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));
    blobevents.append(DetectedEvent("blob","2,1,10.0,10.0",1.0));
    blobevents.append(DetectedEvent("blob","3,1,16.0,18.0",1.0));

    int initial_file_size = 57;


    filewriternode.openFile(test_file);//open a file with the above name using filewriter object filewriternode
    filewriternode.processEvents(blobevents);//write data to the file
    filewriternode.closeFile();//close the file

    QFile file;

    if(file.isOpen()){
        file.close();
    }
    file.setFileName(test_file);
    file.size();
    QTextStream in_stream;
    in_stream.setDevice(&file);
    int final_file_size = file.size();

    QVERIFY2(file.open(QIODevice::ReadOnly | QIODevice::Text),"File named "+test_file.toLocal8Bit()+" has not created");
    QString read = in_stream.readLine(0);

    //qDebug()<<QString("%1").arg(final_file_size).toLocal8Bit();
    //qDebug()<<"------------------";
    QVERIFY2(final_file_size== initial_file_size,QString("%1 is read as the file size, but should be %1").arg(final_file_size,initial_file_size).toLocal8Bit());

}


void TestNoobaVSSADTest::testFileWriter6()//to test whether the size of written file is same as input
{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
    FileWriterNode filewriternode;

    QDir dir(QDir::home());
    if(!dir.exists("NoobaVSS_testdata")){
        dir.mkdir("NoobaVSS_testdata");
    }
    dir.cd("NoobaVSS_testdata");
    if(!dir.exists("data")){
        dir.mkdir("data");
    }
    dir.cd("data");
    if(!dir.exists("text")){
        dir.mkdir("text");
    }
    dir.cd("text");


    QDateTime timestamp = QDateTime::currentDateTime();// current time is taken in to create a unique file name that is already not created
    QString test_file =  dir.absoluteFilePath(timestamp.currentDateTime().toString("yyyy-MM-dd-hhmm") + "-test_filewriter_node.txt");

    //QString test_file = dir.absoluteFilePath("testing_01");
    QList<DetectedEvent> blobevents;

    blobevents.append(DetectedEvent("blob","1,1,10.0,10.0",1.0));
    blobevents.append(DetectedEvent("blob","2,1,10.0,10.0",1.0));
    blobevents.append(DetectedEvent("blob","3,1,16.0,18.0",1.0));

    int initial_file_size = 57;


    filewriternode.openFile(test_file);//open a file with the above name using filewriter object filewriternode
    filewriternode.processEvents(blobevents);//write data to the file
    filewriternode.closeFile();//close the file

    QFile file;

    if(file.isOpen()){
        file.close();
    }
    file.setFileName(test_file);
    file.size();
    QTextStream in_stream;
    in_stream.setDevice(&file);
    int final_file_size = file.size();

    QVERIFY2(file.open(QIODevice::ReadOnly | QIODevice::Text),"File named "+test_file.toLocal8Bit()+" has not created");
    QString read = in_stream.readLine(0);

    //qDebug()<<QString("%1").arg(final_file_size).toLocal8Bit();
    //qDebug()<<"------------------";
    QVERIFY2(final_file_size== initial_file_size,QString("%1 is read as the file size, but should be %1").arg(final_file_size,initial_file_size).toLocal8Bit());

}


QTEST_MAIN(TestNoobaVSSADTest)

#include "tst_testnoobavssadtest.moc"

