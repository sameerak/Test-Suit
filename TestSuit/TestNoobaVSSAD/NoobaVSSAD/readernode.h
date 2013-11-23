#ifndef READERNODE_H
#define READERNODE_H

#include <QFile>
#include <QDebug>
#include <QList>
#include <QStringList>
#include <NoobaVSSAD/featurenode.h>

class ReaderNode : public FeatureNode
{
public:
    explicit ReaderNode(FeatureNode* parent = 0);
    ~ReaderNode();

    void processEvents(const QList<DetectedEvent> event);
    QList<DetectedEvent> processEventsLocal(const QList<DetectedEvent> event);
    bool openFile(QString filename);
    void closeFile(void);


private:

    QFile file;
    QTextStream in;
    QString readFile();
};

#endif // READERNODE_H
