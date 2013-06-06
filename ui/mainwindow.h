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
    QGridLayout *loginWidgetLayout;
    QPushButton *loginButton;
    QPushButton *saveSettingsButton;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void saveSettings();
};

#endif // MAINWINDOW_H
