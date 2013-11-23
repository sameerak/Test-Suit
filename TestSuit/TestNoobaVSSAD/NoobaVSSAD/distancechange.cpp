#include "NoobaVSSAD/distancechange.h"

DistanceChange::DistanceChange(FeatureNode *parent) :
    FeatureNode(parent)
{
}

DistanceChange::~DistanceChange()
{

}

void DistanceChange::processEvents(const QList<DetectedEvent> event)
{

    //This should recieve distance events only.
    //TODO: Remove some old keys from hash map in timely mannar.

    //This is output event
    QList<DetectedEvent> distanceChangeEvent;

    distanceChangeEvent = processEventsLocal(event);

    if(!distanceChangeEvent.isEmpty()){
        emit generateEvent(distanceChangeEvent);
    }
}

QList<DetectedEvent> DistanceChange::processEventsLocal(const QList<DetectedEvent> event){

    //This should recieve distance events only.
    //TODO: Remove some old keys from hash map in timely mannar.

    //This is output event
    QList<DetectedEvent> distanceChangeEvent;

    //previousEvents hash map consists of previous events recieved before now.
    //if this is empty, we simply cannot find a difference.
    if(!previousEvents.isEmpty()){

        foreach(DetectedEvent newEvent, event){

            //We are checking is there any previous matching distance for each new distance.
            //If so, we calcuate difference and add an DetectedEvent to the output List.

            QList<QString> newMessage = newEvent.getMessage().split(",");
            if(previousEvents.contains(newMessage.at(1))){
                //Then we have two instances, so can calculate a difference/change of distance.

                //expected to be newMessage.at(1) as 1-2 which are the ids of two blobs
                DetectedEvent oldEvent = previousEvents.value(newMessage.at(1));
                QList<QString> oldMessage = oldEvent.getMessage().split(",");

                if(newMessage.at(0).toFloat() - oldMessage.at(0).toFloat() == 0.0){
                    continue;
                }
                float distanceChange = (newMessage.at(2).toFloat() - oldMessage.at(2).toFloat())/ (newMessage.at(0).toFloat() - oldMessage.at(0).toFloat());

                distanceChangeEvent.append(DetectedEvent("distChange",QString("%1,%2,%3").arg(newMessage.at(0)).arg(newMessage.at(1)).arg(distanceChange),1.0));

            }
        }
    }

    //Insert new events anyway to the hash map.
    //If already exists the key, this will replace the previous version
    foreach(DetectedEvent e, event){
        QList<QString> message = e.getMessage().split(",");
        previousEvents.insert(message.at(1),e);
    }
    return distanceChangeEvent;

}
