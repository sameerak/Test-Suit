#include "NoobaVSSAD/distancenode.h"

DistanceNode::DistanceNode(FeatureNode *parent) :
    FeatureNode(parent)
{
}


DistanceNode::~DistanceNode()
{

}

void DistanceNode::processEvents(const QList<DetectedEvent> event)
{
    if(event.count() < 2){
        return;
    }
    QList<DetectedEvent> distanceEvent;
    distanceEvent = processEventsLocal(event);

    emit generateEvent(distanceEvent);
}

QList<DetectedEvent> DistanceNode::processEventsLocal(const QList<DetectedEvent> event){

    QList<DetectedEvent> distanceEvent;
    if(event.count() < 2){
        return distanceEvent;
    }
    for(int i = 0; i < event.count(); i++){
        for(int j = i+1; j < event.count(); j++){

            QList<QString> params1 = event.at(i).getMessage().split(",");
            QList<QString> params2 = event.at(j).getMessage().split(",");
            float distX = params1.at(2).toFloat() - params2.at(2).toFloat();
            float distY = params1.at(3).toFloat() - params2.at(3).toFloat();

            float distance = qSqrt(distX* distX + distY * distY);
            distanceEvent.append(DetectedEvent("distance",QString("%1,%2-%3,%4").arg(params1.at(0)).arg(params1.at(1)).arg(params2.at(1)).arg(distance),1.0));
        }
    }
    return distanceEvent;
}
