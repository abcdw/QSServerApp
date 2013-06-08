#include "ui/mainwindow.h"
#include <QApplication>
#include <QPointer>

QPointer<MainWindow> w;

void MessageOutput(QtMsgType type, const char *msg)
{
    if(w)
        w->outputMessage( type, msg );
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new MainWindow();
    qInstallMsgHandler(MessageOutput);
    w->show();
    w->resize(800, 300);
    return a.exec();
}
