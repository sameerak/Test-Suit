#ifndef SPEEDNODE_H
#define SPEEDNODE_H

#include <qmath.h>
#include <QList>
#include <QStringList>
#include <QDebug>
#include <QHash>
#include <NoobaVSSAD/featurenode.h>

class SpeedNode : public FeatureNode
{
public:
    explicit SpeedNode(FeatureNode* parent = 0);
    ~SpeedNode();

    void processEvents(const QList<DetectedEvent> event);
    QList<DetectedEvent> processEventsLocal(const QList<DetectedEvent> event);
private:

    QHash<QString,DetectedEvent> previousEvents;
};

#endif // SPEEDNODE_H
