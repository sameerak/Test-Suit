#ifndef TESTDATANODE_H
#define TESTDATANODE_H

#include <NoobaVSSAD/detectedevent.h>

class testdatanode
{
public:
    testdatanode();

    QList<DetectedEvent> blobevents;
    QList<DetectedEvent> speedEvents;


    void addBLobEvents(DetectedEvent& newEvent);
    QList<DetectedEvent> getBlobEvents();

    void addSpeedEvents(DetectedEvent& newEvent);
    QList<DetectedEvent> getSpeedEvents();

    void addDistanceEvents(DetectedEvent& newEvent);
    QList<DetectedEvent> getDistanceEvents();

    void resetAllLists();

private:
    QList<DetectedEvent> distanceEvents;

};

#endif // TESTDATANODE_H
