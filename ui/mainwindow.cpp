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
    loginWidget        = new QWidget(this);
    loginWidgetLayout  = new QGridLayout(loginWidget);
    loginLine          = new QLineEdit(loginWidget);
    passwordLine       = new QLineEdit(loginWidget);
    authHostLine       = new QLineEdit(loginWidget);
    authPortLine       = new QLineEdit(loginWidget);
    authDBLine         = new QLineEdit(loginWidget);
    loginButton        = new QPushButton("login", loginWidget);
    saveSettingsButton = new QPushButton("save" , loginWidget);

    QLabel *infoLabel     = new QLabel("Fill infromation about authentication database"
                                                  , loginWidget);
    QLabel *loginLabel    = new QLabel("login:"   , loginWidget);
    QLabel *passwordLabel = new QLabel("pass:"    , loginWidget);
    QLabel *authHostLabel = new QLabel("host:"    , loginWidget);
    QLabel *authPortLabel = new QLabel("port:"    , loginWidget);
    QLabel *authDBLabel   = new QLabel("database:", loginWidget);

    passwordLine->setEchoMode(QLineEdit::Password);

    loginWidgetLayout->addWidget(infoLabel,          0, 0, 1, 2);
    loginWidgetLayout->addWidget(loginLabel,         1, 0);
    loginWidgetLayout->addWidget(passwordLabel,      2, 0);
    loginWidgetLayout->addWidget(loginLine,          1, 1);
    loginWidgetLayout->addWidget(passwordLine,       2, 1);
    loginWidgetLayout->addWidget(authHostLabel,      3, 0);
    loginWidgetLayout->addWidget(authHostLine,       3, 1);
    loginWidgetLayout->addWidget(authPortLabel,      4, 0);
    loginWidgetLayout->addWidget(authPortLine,       4, 1);
    loginWidgetLayout->addWidget(authDBLabel,        5, 0);
    loginWidgetLayout->addWidget(authDBLine,         5, 1);
    loginWidgetLayout->addWidget(saveSettingsButton, 6, 0);
    loginWidgetLayout->addWidget(loginButton,        6, 1);

    connect(saveSettingsButton, SIGNAL(clicked()), this, SLOT(saveSettings()));
}

void MainWindow::loadSettings()
{
    QSettings settings(confFileName, QSettings::IniFormat);

    loginLine->setText(   settings.value("auth/login", "auth").toString());
    passwordLine->setText(settings.value("auth/pass" , "strongpassword").toString());
    authHostLine->setText(settings.value("auth/host" , "locahost").toString());
    authPortLine->setText(settings.value("auth/port" , "3306").toString());
    authDBLine->setText(  settings.value("auth/db"   , "auth").toString());
}

void MainWindow::saveSettings()
{
    QSettings settings(confFileName, QSettings::IniFormat);

    settings.setValue("auth/login", loginLine->text());
    settings.setValue("auth/pass" , passwordLine->text());
    settings.setValue("auth/host" , authHostLine->text());
    settings.setValue("auth/port" , authPortLine->text());
    settings.setValue("auth/db"   , authDBLine->text());
}

MainWindow::~MainWindow()
{
    
}
