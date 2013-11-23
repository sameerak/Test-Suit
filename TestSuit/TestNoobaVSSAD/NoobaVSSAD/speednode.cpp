#include "NoobaVSSAD/speednode.h"

SpeedNode::SpeedNode(FeatureNode *parent) :
    FeatureNode(parent)
{
}

SpeedNode::~SpeedNode()
{

}

void SpeedNode::processEvents(const QList<DetectedEvent> event)
{

    //This is output event
    QList<DetectedEvent> speedEvent;

    speedEvent = processEventsLocal(event);

    if(!speedEvent.isEmpty()){
        emit generateEvent(speedEvent);
    }


}

QList<DetectedEvent> SpeedNode::processEventsLocal(const QList<DetectedEvent> event){

    //This should recieve blob events only.
    //TODO: Remove some old keys from hash map in timely mannar.


    //This is output event
    QList<DetectedEvent> speedEventLocal;


    //previousEvents hash map consists of previous events recieved before now.
    //if this is empty, we simply cannot find a speed.
    if(!previousEvents.isEmpty()){

        foreach(DetectedEvent newEvent, event){

            //We are checking is there any previous matching blob for each new blob.
            //If so, we calcuate speed and add an DetectedEvent to the output List.

            QList<QString> newMessage = newEvent.getMessage().split(",");
            if(previousEvents.contains(newMessage.at(1))){
                //Then we have two instances, so can calculate a speed of blob.

                //expected to be newMessage.at(1) as 1 which are the id of a blob
                DetectedEvent oldEvent = previousEvents.value(newMessage.at(1));
                QList<QString> oldMessage = oldEvent.getMessage().split(",");

                float speedX = (newMessage.at(2).toFloat() - oldMessage.at(2).toFloat()) / (newMessage.at(0).toFloat() - oldMessage.at(0).toFloat());
                float speedY = (newMessage.at(3).toFloat() - oldMessage.at(3).toFloat()) / (newMessage.at(0).toFloat() - oldMessage.at(0).toFloat());

                float speed = sqrt(speedX * speedX + speedY * speedY);
                speedEventLocal.append(DetectedEvent("speed",QString("%1,%2,%3").arg(newMessage.at(0)).arg(newMessage.at(1)).arg(speed),1.0));

            }
        }
    }

    //Insert new events anyway to the hash map.
    //If already exists the key, this will replace the previous version
    foreach(DetectedEvent e, event){
        QList<QString> message = e.getMessage().split(",");
        previousEvents.insert(message.at(1),e);
    }
    return speedEventLocal;
}
