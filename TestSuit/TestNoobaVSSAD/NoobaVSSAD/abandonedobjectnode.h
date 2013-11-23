#ifndef ABANDONEDOBJECTNODE_H
#define ABANDONEDOBJECTNODE_H

#include <NoobaVSSAD/featurenode.h>
#include <QList>
#include <QStringList>
#include <QHash>
#include <QDebug>

class AbandonedObjectNode : public FeatureNode
{
public:
    explicit AbandonedObjectNode(FeatureNode* parent = 0);
    ~AbandonedObjectNode();

    void processEvents(const QList<DetectedEvent> event);
    QList<DetectedEvent> processEventsLocal(const QList<DetectedEvent> event);


    /**
     * @brief Even still blobs might have sevaral spikes of position.
     *        by setting this parameter, we can roundup those to still objects.
     * @param value:     new still_object_speed_threshold value. suggestion: 0.01
     * @return
     */
    void setStillObjectSpeedThreshold(double value){ still_object_speed_threshold = value;}

    /**
     * @brief There are some objects enter the scene together..
     *        by setting this parameter, we can identify really moving objects.
     * @param value:     new leaving_object_speed_threshold value. suggestion: 3.0
     * @return
     */
    void setLeavingObjectSpeedThreshold(double value){ leaving_object_speed_threshold = value;}

    /**
     * @brief Before checking other logics, we check weather are any objects
     *        which are separating from one another. If those are separating,
     *        then we proceed further.
     *        by setting this parameter, we can roundup those to still objects.
     * @param value:     new distance_change_rate_threshold value. suggestion: 1.0
     * @return
     */
    void setDistanceChangeRateThreshold(double value){ distance_change_rate_threshold = value;}

    /**
     * @brief One should be still. This is the minimum speed threshold to determining still.
     *        by setting this parameter, we can roundup those to still objects.
     * @param value:     new split_min_limit value. suggestion: 250.0
     * @return
     */
    void setSplitMinLimit(double value){ split_min_limit = value;}

    /**
     * @brief One should be moving. This is the minimum speed threshold to determining still.
     *        by setting this parameter, we can isolate moving objects.
     * @param value:     new split_max_limit value. suggestion: 300.0
     * @return
     */
    void setSplitMaxLimit(double value){ split_max_limit = value;}

private:
     QHash<QString,DetectedEvent> speedEvents;
     QList<QString> splittedObjects;
     QList<QString> nonSplittedObjects;

     double still_object_speed_threshold;
     double leaving_object_speed_threshold;
     double distance_change_rate_threshold;
     double split_min_limit;
     double split_max_limit;
};

#endif // ABANDONEDOBJECTNODE_H
