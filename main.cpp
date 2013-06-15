#include "ui/mainwindow.h"
#include <QApplication>
#include <QPointer>

QPointer<MainWindow> w;

void MessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if(w)
        w->outputMessage( type, msg );
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new MainWindow();
    qInstallMessageHandler(MessageOutput);
    w->show();

    return a.exec();
}
