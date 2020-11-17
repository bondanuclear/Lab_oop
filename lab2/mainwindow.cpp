#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "dialog.h"
#include <QDebug>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QApplication>
#include <QListWidget>
#include <QString>
#include <QSoundEffect>
#include <QtCore>
#include <QtGui>
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        this->setWindowTitle("Timer");
player = new QMediaPlayer(this);
}
void MainWindow::on_pushButton_clicked()
{
    int time = ui->spinBox->value();
    tmr = new QTimer(this);
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();
    QTimer::singleShot(time, this, SLOT(foo()));


}

MainWindow::~MainWindow()
{
    delete ui;
    delete tmr;
}
void MainWindow::updateTime()
{
    ui->label->setText(QTime::currentTime().toString()); // Обновляем время на экране
}
void MainWindow::foo()
{
ui->statusbar->showMessage("Done");
//QSoundEffect::setVolume();

QApplication::beep();
tmr->stop();
QMessageBox msgbox;
msgbox.setText("Done!");
msgbox.exec();
//player->setMedia(QUrl::fromLocalFile(":/Trash/test.mp3"));



}



void MainWindow::on_actionExit_2_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAlarm_Clock_2_triggered()
{
 SecondWindow window;
 window.setModal(true);
 window.exec();

}

void MainWindow::on_pushButton_2_clicked()
{
QListWidgetItem * item = new QListWidgetItem;
item->setText("The timer worked " + ui->spinBox->cleanText() + " ms");
ui->listWidget->addItem(item);
}


void MainWindow::on_pushButton_3_clicked()
{
    Donotdisturb window2;
    window2.setModal(true);
    window2.exec();

}

void MainWindow::on_pushButton_4_clicked()
{
    windoww = new MainWindow(this);
    windoww->show();

}
void MainWindow::on_pushButton_5_clicked()
{
QString name = ui->lineEdit->text();
this->setWindowTitle(name);
}



