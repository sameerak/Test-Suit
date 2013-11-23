#ifndef DELAYNODE_H
#define DELAYNODE_H

#include <QList>
#include <QQueue>
#include <QDebug>
#include <NoobaVSSAD/featurenode.h>

class DelayNode : public FeatureNode
{
public:
    explicit DelayNode(FeatureNode* parent = 0);
    ~DelayNode();

    void processEvents(const QList<DetectedEvent> event);

private:
    QQueue<QList<DetectedEvent> > previousEventQueue;
    int delaySteps;
};

#endif // DELAYNODE_H
