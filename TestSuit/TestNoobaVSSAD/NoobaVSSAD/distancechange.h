#ifndef DISTANCECHANGE_H
#define DISTANCECHANGE_H

#include <qmath.h>

#include <QDebug>
#include <QHash>
#include <QList>
#include <QStringList>
#include <NoobaVSSAD/featurenode.h>

class DistanceChange  : public FeatureNode
{
public:
    explicit DistanceChange(FeatureNode* parent = 0);
    ~DistanceChange();

    void processEvents(const QList<DetectedEvent> event);
    QList<DetectedEvent> processEventsLocal(const QList<DetectedEvent> event);

private:
    QHash<QString,DetectedEvent> previousEvents;
};

#endif // DISTANCECHANGE_H
