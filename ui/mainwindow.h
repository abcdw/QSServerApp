#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSettings>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlError>
#include <QTextEdit>
#include <QTableView>
#include <QTimer>
#include <QSignalMapper>

#include "src/server.h"
#include "src/userlistmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString confFileName;

    void initLoginWidget();
    void loadSettings();

    QWidget     *loginWidget;
    QLineEdit   *authLoginLine;
    QLineEdit   *authPasswordLine;
    QLineEdit   *authHostLine;
    QLineEdit   *authPortLine;
    QLineEdit   *authDBLine;

    QLineEdit   *mainLoginLine;
    QLineEdit   *mainPasswordLine;
    QLineEdit   *mainHostLine;
    QLineEdit   *mainPortLine;
    QLineEdit   *mainDBLine;

    QLabel      *infoLabel;
    QGridLayout *loginWidgetLayout;
    QPushButton *startButton;
    QPushButton *saveSettingsButton;
    QPushButton *exitButton;

    Server *server;

    void initMainWidget();

    QWidget       *mainWidget;
    QTextEdit     *serverLogEdit;
    QTableView    *userList;
    QGridLayout   *mainLayout;
    UserListModel *userListModel;

public:
    void outputMessage(QtMsgType type, const QString &msg);
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void saveSettings();
    bool openAuthDB();
    bool openMainDB();
    void startServer();

signals:
    void authConnectionFailed();
    void authSuccessfullOpened();
};

#endif // MAINWINDOW_H
