#include "NoobaVSSAD/readernode.h"

ReaderNode::ReaderNode(FeatureNode* parent):
    FeatureNode(parent)
{
}

ReaderNode::~ReaderNode(){
    file.close();
}

void ReaderNode::processEvents(const QList<DetectedEvent> event)
{

    QList<DetectedEvent> generatedEvents;

    generatedEvents = processEventsLocal(event);
    if(!generatedEvents.isEmpty()){
        emit generateEvent(generatedEvents);
    }
}

QList<DetectedEvent> ReaderNode::processEventsLocal(const QList<DetectedEvent> event){

    QList<DetectedEvent> generatedEvents;
    //qDebug() << event.getIdentifier() << " " << event.getMessage() << " " << event.getConfidence();
    QString eventmessage = readFile();

    if(eventmessage == ""){
        return generatedEvents;
    }

    QStringList event_strings = eventmessage.split("|");


    if(event_strings.count() != 0){

        for(int i = 0; i < event_strings.count(); i++){
            if(event_strings.at(i) == ""){
                continue;
            }
//            QStringList parameters =  event_strings.at(i).split(",");

//            bool ok;

//            int frame = parameters.at(0).toInt(&ok);
//            int tag = parameters.at(1).toInt(&ok);
//            int x_position = parameters.at(2).toInt(&ok);
//            int y_position = parameters.at(3).toInt(&ok);
//            if(!ok) return;

//            qDebug() << frame << " " << tag << " " << x_position << " " << y_position;
//            qDebug() << "blob " << i << " " << event_strings.at(i);
            DetectedEvent newEvent("blob",event_strings.at(i),1.0);
            generatedEvents.append(newEvent);
        }
    }
    return generatedEvents;
}

QString ReaderNode::readFile(){
    if(!in.device()){
        qDebug() << "No input file to read! Abort.";
        exit(1);
    }
     if(!in.atEnd()) {
         QString line = in.readLine();
         return line;
     }
     else{
         qDebug() << "end of file";
         exit(0);
         //return "\n";
     }
}

bool ReaderNode::openFile(QString filename){

    if(file.isOpen()){
        file.close();
    }
    file.setFileName(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "No input file named " << filename << "! Abort.";
        return false;
    }
    in.setDevice(&file);
    return true;
}

void ReaderNode::closeFile(void){
    file.close();
}
