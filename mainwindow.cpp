#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    confFileName = "server.conf";

    initLoginWidget();

    loadSettings();
    setCentralWidget(loginWidget);
}

void MainWindow::initLoginWidget()
{
    loginWidget       = new QWidget(this);
    loginWidgetLayout = new QGridLayout(loginWidget);
    loginLine         = new QLineEdit(loginWidget);
    passwordLine      = new QLineEdit(loginWidget);
    loginButton       = new QPushButton("login", loginWidget);

    QLabel *loginLabel    = new QLabel("login:", loginWidget);
    QLabel *passwordLabel = new QLabel("pass:", loginWidget);

    passwordLine->setEchoMode(QLineEdit::Password);

    loginWidgetLayout->addWidget(loginLabel,    0, 0);
    loginWidgetLayout->addWidget(passwordLabel, 1, 0);
    loginWidgetLayout->addWidget(loginLine,     0, 1);
    loginWidgetLayout->addWidget(passwordLine,  1, 1);
    loginWidgetLayout->addWidget(loginButton,   2, 0, 1, 2);
}

void MainWindow::loadSettings()
{
    QSettings settings(confFileName, QSettings::IniFormat);


}

void MainWindow::saveSettings()
{
    QSettings settings(confFileName, QSettings::IniFormat);

    settings.setValue("auth/login", "root");
    settings.setValue("auth/pass" , "root");
    settings.setValue("auth/db"   , "auth");

}

MainWindow::~MainWindow()
{
    
}
