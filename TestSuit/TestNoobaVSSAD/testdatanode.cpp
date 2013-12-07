#include "testdatanode.h"

testdatanode::testdatanode()
{
}

void testdatanode::addBLobEvents(DetectedEvent &newEvent){

    blobevents.append(newEvent);

}

QList<DetectedEvent> testdatanode::getBlobEvents(){
    return blobevents;

}

void testdatanode::addSpeedEvents(DetectedEvent &newEvent){
    speedEvents.append(newEvent);
}

QList<DetectedEvent> testdatanode::getSpeedEvents(){
    return speedEvents;

}

void testdatanode::addDistanceEvents(DetectedEvent &newEvent){
    distanceEvents.append(newEvent);
}

QList<DetectedEvent> testdatanode::getDistanceEvents(){
    return distanceEvents;

}

void testdatanode::resetAllLists(){

    speedEvents.clear();
    blobevents.clear();
    distanceEvents.clear();
}
