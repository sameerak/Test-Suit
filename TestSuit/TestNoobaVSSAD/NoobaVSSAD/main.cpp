#include <QtCore/QCoreApplication>
#include <QDebug>
#include <NoobaVSSAD/readernode.h>
#include <NoobaVSSAD/noobavssad.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NoobaVSSAD application;

    application.launch();

    return a.exec();
}
