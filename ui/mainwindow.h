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
#include "src/server.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString confFileName;

    void initLoginWidget();
    void loadSettings();


    QWidget     *loginWidget;
    QLineEdit   *loginLine;
    QLineEdit   *passwordLine;
    QLineEdit   *authHostLine;
    QLineEdit   *authPortLine;
    QLineEdit   *authDBLine;
    QLabel      *infoLabel;
    QGridLayout *loginWidgetLayout;
    QPushButton *startButton;
    QPushButton *saveSettingsButton;

    Server *server;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void saveSettings();
    bool openAuthDB();
    void startServer();

signals:
    void authConnectionFailed();
    void authSuccessfullOpened();
};

#endif // MAINWINDOW_H
