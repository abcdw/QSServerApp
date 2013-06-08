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
    authDB.setUserName(loginLine->text());
    authDB.setPassword(passwordLine->text());

    if (authDB.open()) {
        infoLabel->setText("Success!");
        emit authSuccessfullOpened();
        return true;
    }
    else {
        infoLabel->setText(authDB.lastError().text());
        emit authConnectionFailed();
        return false;
    }
}

void MainWindow::startServer()
{
    if (!openAuthDB())
        return;

    initMainWidget();

    setCentralWidget(mainWidget);
    server = new Server();
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

    mainLayout->addWidget(serverLogEdit, 0, 0);
    mainLayout->addWidget(userList,      0, 1);
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
    startButton        = new QPushButton("start server", loginWidget);
    saveSettingsButton = new QPushButton("save"        , loginWidget);

    infoLabel             = new QLabel("Fill infromation about authentication database"
                                                  , loginWidget);
    QLabel *loginLabel    = new QLabel("login:"   , loginWidget);
    QLabel *passwordLabel = new QLabel("pass:"    , loginWidget);
    QLabel *authHostLabel = new QLabel("host:"    , loginWidget);
    QLabel *authPortLabel = new QLabel("port:"    , loginWidget);
    QLabel *authDBLabel   = new QLabel("database:", loginWidget);

    passwordLine->setEchoMode(QLineEdit::Password);
    infoLabel->setAlignment(Qt::AlignCenter);

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
    loginWidgetLayout->addWidget(startButton,        6, 1);

    connect(saveSettingsButton, SIGNAL(clicked()), this, SLOT(saveSettings()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startServer()));
}

void MainWindow::loadSettings()
{
    QSettings settings(confFileName, QSettings::IniFormat);

    loginLine->setText(   settings.value("auth/login", "auth").toString());
    passwordLine->setText(settings.value("auth/pass" , "strongpassword").toString());
    authHostLine->setText(settings.value("auth/host" , "localhost").toString());
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
