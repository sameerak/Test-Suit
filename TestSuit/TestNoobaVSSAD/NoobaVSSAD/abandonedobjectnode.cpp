#include "NoobaVSSAD/abandonedobjectnode.h"

AbandonedObjectNode::AbandonedObjectNode(FeatureNode *parent) :
    FeatureNode(parent)
{

}


AbandonedObjectNode::~AbandonedObjectNode()
{

}

void AbandonedObjectNode::processEvents(const QList<DetectedEvent> event)
{

    //This is output event
    QList<DetectedEvent> abandonedObjectEvent;

    if(!event.isEmpty()){

        abandonedObjectEvent = processEventsLocal(event);
        if(!abandonedObjectEvent.isEmpty()){
            emit generateEvent(abandonedObjectEvent);
        }
    }

}

QList<DetectedEvent> AbandonedObjectNode::processEventsLocal(const QList<DetectedEvent> event){
    //    foreach( DetectedEvent e, event){
    //        qDebug() << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << e.getIdentifier() << " " << e.getMessage() << " " << e.getConfidence();

    //    }

        //This is output event
        QList<DetectedEvent> abandonedObjectEvent;

        //Recieve both speed and relative distance at two calls.
        //This will gather both, and when both are recieced it will process.

        if(!event.isEmpty()){
            QList<QString> id = event.at(0).getIdentifier().split("_");
            if(id.at(0) == "distance"){

                //Check firstever occurances of distance event, if it is near zero,
                // make a note of that by assigning lable in to a list
                foreach(DetectedEvent e, event){
                    QList<QString> message = e.getMessage().split(",");

                    if(message.at(0) == "3011"){
                        qDebug()<<"List";
                        foreach(QString str, splittedObjects){
                            qDebug() << str;
                        }
                        qDebug()<<"EndList";
                    }

                    //TODO: These splittedObjects and nonSplittedObjects String Lists are not released at any time. so those are continuously growing. have to clean somehow
                    if(!splittedObjects.contains(message.at(1)) && !nonSplittedObjects.contains(message.at(1))){
                        if(message.at(2).toFloat() > split_min_limit && message.at(2).toFloat() < split_max_limit){
                            splittedObjects.append(message.at(1));
                            //qDebug() << "Added to Splitted objects" << message.at(1);
                        }
                        else{
                            nonSplittedObjects.append(message.at(1));
                        }
                    }

                }
            }
            else if( id.at(0) == "distChange"){

                foreach(DetectedEvent distChangeEvent, event){
                    QList<QString> message = distChangeEvent.getMessage().split(",");

                    float distChange = message.at(2).toFloat();


                    if(distChange < distance_change_rate_threshold || !splittedObjects.contains(message.at(1))){
                        continue;
                    }

                    //else, distance is changing, so we are looking weather one blob is not moving
                    QList<QString> blobIds = message.at(1).split("-");

                     float speedFirstBlob = 0.0;
                     float speedSecondBlob = 0.0;
                    if(speedEvents.contains(blobIds.at(0)) && speedEvents.contains(blobIds.at(1))){
                        DetectedEvent speedEvent = speedEvents.value(blobIds.at(0));
                        speedFirstBlob = speedEvent.getMessage().split(",").at(2).toFloat();

                        speedEvent = speedEvents.value(blobIds.at(1));
                        speedSecondBlob = speedEvent.getMessage().split(",").at(2).toFloat();

                        if(speedFirstBlob < still_object_speed_threshold && speedSecondBlob > leaving_object_speed_threshold){
                            abandonedObjectEvent.append(DetectedEvent("<FONT COLOR='#ff0000'>ABObj",QString("%1,%2,%3,%4,%5,%6").arg(message.at(0)).arg(blobIds.at(0)).arg(blobIds.at(1)).arg(distChange).arg(speedFirstBlob).arg(speedSecondBlob),1.0));
                        }
                        else if(speedFirstBlob > leaving_object_speed_threshold && speedSecondBlob < still_object_speed_threshold){
                            abandonedObjectEvent.append(DetectedEvent("<FONT COLOR='#ff0000'>ABObj",QString("%1,%2,%3,%4,%5,%6").arg(message.at(0)).arg(blobIds.at(1)).arg(blobIds.at(0)).arg(distChange).arg(speedSecondBlob).arg(speedFirstBlob),1.0));
                        }
                    }
                    //else continue;
                }
            }
            else if(id.at(0) == "speed"){
                //Insert new speed events to the hash map.
                //If already exists the key, this will replace the previous version
                foreach(DetectedEvent e, event){
                    QList<QString> message = e.getMessage().split(",");
                    speedEvents.insert(message.at(1),e);
                }
            }

        }
        return abandonedObjectEvent;
}
