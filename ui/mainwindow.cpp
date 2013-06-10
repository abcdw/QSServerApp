#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    confFileName = "server.conf";

    initLoginWidget();

    loadSettings();
    setCentralWidget(loginWidget);
}

bool MainWindow::openAuthDB()
{
    QSqlDatabase authDB = QSqlDatabase::addDatabase("QMYSQL", "auth");
    authDB.setHostName(authHostLine->text());
    authDB.setDatabaseName(authDBLine->text());
    authDB.setPort(authPortLine->text().toInt());
    authDB.setUserName(authLoginLine->text());
    authDB.setPassword(authPasswordLine->text());

    if (authDB.open()) {
        return true;
    }
    else {
        infoLabel->setText(authDB.lastError().text());
        return false;
    }
}

bool MainWindow::openMainDB()
{
    QSqlDatabase mainDB = QSqlDatabase::addDatabase("QMYSQL", "main");
    mainDB.setHostName(mainHostLine->text());
    mainDB.setDatabaseName(mainDBLine->text());
    mainDB.setPort(mainPortLine->text().toInt());
    mainDB.setUserName(mainLoginLine->text());
    mainDB.setPassword(mainPasswordLine->text());

    if (mainDB.open()) {
        return true;
    }
    else {
        infoLabel->setText(mainDB.lastError().text());
        return false;
    }
}

void MainWindow::startServer()
{
    if (!openAuthDB() || !openMainDB())
        return;

    initMainWidget();

    setCentralWidget(mainWidget);
    server = new Server();

    connect(server, SIGNAL(clientAuthenticated(User *)), userListModel, SLOT(addUser(User *)));
    connect(server, SIGNAL(clientDisconnected(User*)), userListModel, SLOT(delUser(User *)));
    server->startServer();
}

void MainWindow::initMainWidget()
{
    mainWidget    = new QWidget(this);
    serverLogEdit = new QTextEdit(mainWidget);
    userList      = new QTableView(mainWidget);
    mainLayout    = new QGridLayout(mainWidget);
    userListModel = new UserListModel(mainWidget);

    userList->setModel(userListModel);
    userList->setFixedWidth(320);
    userList->setColumnWidth(0, 30);
    userList->setColumnWidth(1, 140);
    userList->setColumnWidth(2, 70);
    userList->setColumnWidth(3, 70);
    mainLayout->addWidget(serverLogEdit, 0, 0);
    mainLayout->addWidget(userList,      0, 1);
}

void MainWindow::initLoginWidget()
{
    loginWidget        = new QWidget(this);
    loginWidgetLayout  = new QGridLayout(loginWidget);
    authLoginLine          = new QLineEdit(loginWidget);
    authPasswordLine       = new QLineEdit(loginWidget);
    authHostLine       = new QLineEdit(loginWidget);
    authPortLine       = new QLineEdit(loginWidget);
    authDBLine         = new QLineEdit(loginWidget);
    mainLoginLine      = new QLineEdit(loginWidget);
    mainPasswordLine   = new QLineEdit(loginWidget);
    mainHostLine       = new QLineEdit(loginWidget);
    mainPortLine       = new QLineEdit(loginWidget);
    mainDBLine         = new QLineEdit(loginWidget);

    startButton        = new QPushButton("start server", loginWidget);
    saveSettingsButton = new QPushButton("save"        , loginWidget);
    exitButton         = new QPushButton("exit"        , loginWidget);

    infoLabel             = new QLabel("Fill infromation about authentication database and main database"
                                                  , loginWidget);
    QLabel *loginLabel    = new QLabel("login:"   , loginWidget);
    QLabel *passwordLabel = new QLabel("pass:"    , loginWidget);
    QLabel *authHostLabel = new QLabel("host:"    , loginWidget);
    QLabel *authPortLabel = new QLabel("port:"    , loginWidget);
    QLabel *authDBLabel   = new QLabel("database:", loginWidget);

    authPasswordLine->setEchoMode(QLineEdit::Password);
    mainPasswordLine->setEchoMode(QLineEdit::Password);
    infoLabel->setAlignment(Qt::AlignCenter);

    loginWidgetLayout->addWidget(infoLabel,          0, 0, 1, 3);
    loginWidgetLayout->addWidget(loginLabel,         1, 0);
    loginWidgetLayout->addWidget(passwordLabel,      2, 0);
    loginWidgetLayout->addWidget(authLoginLine,          1, 1);
    loginWidgetLayout->addWidget(authPasswordLine,       2, 1);
    loginWidgetLayout->addWidget(authHostLabel,      3, 0);
    loginWidgetLayout->addWidget(authHostLine,       3, 1);
    loginWidgetLayout->addWidget(authPortLabel,      4, 0);
    loginWidgetLayout->addWidget(authPortLine,       4, 1);
    loginWidgetLayout->addWidget(authDBLabel,        5, 0);
    loginWidgetLayout->addWidget(authDBLine,         5, 1);

    loginWidgetLayout->addWidget(mainLoginLine,      1, 2);
    loginWidgetLayout->addWidget(mainPasswordLine,   2, 2);
    loginWidgetLayout->addWidget(mainHostLine,       3, 2);
    loginWidgetLayout->addWidget(mainPortLine,       4, 2);
    loginWidgetLayout->addWidget(mainDBLine,         5, 2);

    loginWidgetLayout->addWidget(saveSettingsButton, 6, 0);
    loginWidgetLayout->addWidget(startButton,        6, 1);
    loginWidgetLayout->addWidget(exitButton,         6, 2);

    connect(saveSettingsButton, SIGNAL(clicked()), this, SLOT(saveSettings()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startServer()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

void MainWindow::loadSettings()
{
    QSettings settings(confFileName, QSettings::IniFormat);

    authLoginLine->setText(   settings.value("auth/login", "auth").toString());
    authPasswordLine->setText(settings.value("auth/pass" , "strongpassword").toString());
    authHostLine->setText(settings.value(    "auth/host" , "localhost").toString());
    authPortLine->setText(settings.value(    "auth/port" , "3306").toString());
    authDBLine->setText(  settings.value(    "auth/db"   , "auth").toString());

    mainLoginLine->setText(   settings.value("main/login", "admin").toString());
    mainPasswordLine->setText(settings.value("main/pass" , "strongpassword").toString());
    mainHostLine->setText(settings.value(    "main/host" , "localhost").toString());
    mainPortLine->setText(settings.value(    "main/port" , "3306").toString());
    mainDBLine->setText(  settings.value(    "main/db"   , "main").toString());
}

void MainWindow::saveSettings()
{
    QSettings settings(confFileName, QSettings::IniFormat);

    settings.setValue("auth/login", authLoginLine->text());
    settings.setValue("auth/pass" , authPasswordLine->text());
    settings.setValue("auth/host" , authHostLine->text());
    settings.setValue("auth/port" , authPortLine->text());
    settings.setValue("auth/db"   , authDBLine->text());

    settings.setValue("main/login", mainLoginLine->text());
    settings.setValue("main/pass" , mainPasswordLine->text());
    settings.setValue("main/host" , mainHostLine->text());
    settings.setValue("main/port" , mainPortLine->text());
    settings.setValue("main/db"   , mainDBLine->text());
}

void MainWindow::outputMessage(QtMsgType type, const QString &msg)
{

    switch (type) {
    case QtDebugMsg:
        if (serverLogEdit) {
            QSignalMapper *sm = new QSignalMapper(this);
            QTimer *tm = new QTimer();

            tm->setSingleShot(true);
            tm->setInterval(0);

            sm->setMapping(tm, QString(msg));

            connect(tm, SIGNAL(timeout()), sm, SLOT(map()));
            connect(sm, SIGNAL(mapped(QString)), serverLogEdit, SLOT(append(QString)));

            tm->start();
        }
        else {
            fprintf(stderr, "Debug: %s\n", msg.toAscii().data());
        }
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", msg.toAscii().data());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", msg.toAscii().data());
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", msg.toAscii().data());
        abort();
    }
}

MainWindow::~MainWindow()
{

}
