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
    void loadSettings();
    void saveSettings();
    void initLoginWidget();

    QString confFileName;

    QWidget     *loginWidget;
    QLineEdit   *loginLine;
    QLineEdit   *passwordLine;
    QGridLayout *loginWidgetLayout;
    QPushButton *loginButton;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
