#include "NoobaVSSAD/noobavssad.h"

NoobaVSSAD::NoobaVSSAD(QObject *parent) :
    QObject(parent),
    blobPositionReader("/home/chathuranga/Programming/FYP/data/text/2013-10-24-sample-blobs.txt"),
   //facePositionReader("/home/chathuranga/Programming/FYP/data/text/pets2006-test3-blobs.txt"),
    //blobDistanceWriterNode("/home/chathuranga/Programming/FYP/data/text/2013-10-18-blob-distances.txt"),
    //blobSpeedWriterNode("/home/chathuranga/Programming/FYP/data/text/2013-10-18-blob-speeds.txt"),
    //distanceChangeWriterNode("/home/chathuranga/Programming/FYP/data/text/2013-10-18-distance-changes.txt"),
    leftBagWriterNode("/home/chathuranga/Programming/FYP/data/text/2013-10-24-blobs-sample-abobjects.txt"),
    startingDummy()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(readInputs()));
    connect(&blobPositionReader, SIGNAL(generateEvent(QList<DetectedEvent>)), &blobDistanceNode, SLOT(captureEvent(QList<DetectedEvent>)));
    //connect(&blobPositionReader, SIGNAL(generateEvent(QList<DetectedEvent>)), &blobPositionDelayedNode, SLOT(captureEvent(QList<DetectedEvent>)));
    //connect(&blobDistanceNode, SIGNAL(generateEvent(QList<DetectedEvent>)), &blobDistanceWriterNode, SLOT(captureEvent(QList<DetectedEvent>)));

    connect(&blobPositionReader, SIGNAL(generateEvent(QList<DetectedEvent>)), &blobSpeedNode, SLOT(captureEvent(QList<DetectedEvent>)));
    //connect(&blobPositionDelayedNode, SIGNAL(generateEvent(QList<DetectedEvent>)), &blobSpeedNode, SLOT(captureEvent(QList<DetectedEvent>)));

    connect(&blobDistanceNode, SIGNAL(generateEvent(QList<DetectedEvent>)), &distanceChangeNode, SLOT(captureEvent(QList<DetectedEvent>)));
    connect(&blobDistanceNode, SIGNAL(generateEvent(QList<DetectedEvent>)), &leftBagNode, SLOT(captureEvent(QList<DetectedEvent>)));
    connect(&distanceChangeNode, SIGNAL(generateEvent(QList<DetectedEvent>)), &leftBagNode, SLOT(captureEvent(QList<DetectedEvent>)));
    connect(&blobSpeedNode, SIGNAL(generateEvent(QList<DetectedEvent>)), &leftBagNode, SLOT(captureEvent(QList<DetectedEvent>)));
    //connect(&distanceChangeNode, SIGNAL(generateEvent(QList<DetectedEvent>)), &distanceChangeWriterNode, SLOT(captureEvent(QList<DetectedEvent>)));

    //connect(&blobSpeedNode, SIGNAL(generateEvent(QList<DetectedEvent>)), &blobSpeedWriterNode, SLOT(captureEvent(QList<DetectedEvent>)));
    connect(&leftBagNode, SIGNAL(generateEvent(QList<DetectedEvent>)), &leftBagWriterNode, SLOT(captureEvent(QList<DetectedEvent>)));

}

void NoobaVSSAD::launch(){
    timer.start(1);
}

void NoobaVSSAD::readInputs(){
    blobPositionReader.processEvents(startingDummy);
    facePositionReader.processEvents(startingDummy);
}
