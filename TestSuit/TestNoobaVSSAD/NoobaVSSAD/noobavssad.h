#ifndef NOOBAVSSAD_H
#define NOOBAVSSAD_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <NoobaVSSAD/readernode.h>
#include <NoobaVSSAD/distancenode.h>
#include <NoobaVSSAD/delaynode.h>
#include <NoobaVSSAD/filewriternode.h>
#include <NoobaVSSAD/speednode.h>
#include <NoobaVSSAD/distancechange.h>
#include <NoobaVSSAD/abandonedobjectnode.h>


class NoobaVSSAD : public QObject
{
    Q_OBJECT
public:
    explicit NoobaVSSAD(QObject *parent = 0);
    void launch();

signals:

public slots:
    void readInputs();

private:

    QTimer timer;
    QList<DetectedEvent> startingDummy;
    ReaderNode blobPositionReader;
    ReaderNode facePositionReader;
    DistanceNode blobDistanceNode;
    //DelayNode blobPositionDelayedNode;
    SpeedNode blobSpeedNode;
    AbandonedObjectNode leftBagNode;
    FileWriterNode blobDistanceWriterNode;
    FileWriterNode blobSpeedWriterNode;
    DistanceChange distanceChangeNode;
    FileWriterNode distanceChangeWriterNode;
    FileWriterNode leftBagWriterNode;


};

#endif // NOOBAVSSAD_H
