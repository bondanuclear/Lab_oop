#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "secondwindow.h"
#include "donotdisturb.h"
#include "thirdwindow.h"
#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
    QMediaPlayer* player;
  //  SecondWindow *window;
    MainWindow *windoww;
public slots:
    void foo();
private slots:
    void updateTime();
    void on_pushButton_clicked();
    void on_actionExit_2_triggered();
    void on_actionAlarm_Clock_2_triggered();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

};
#endif // MAINWINDOW_H
