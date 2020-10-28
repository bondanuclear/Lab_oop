#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QDebug>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QApplication>
SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}
void SecondWindow::updateTime1()
{
    ui->label1->setText(QTime::currentTime().toString()); // Обновляем время на экране
}
void SecondWindow::on_pushButton_clicked()
{
    int time1 = ui->spinBox->value();
    tmr1 = new QTimer(this);
    tmr1->setInterval(1000);
    connect(tmr1, SIGNAL(timeout()), this, SLOT(updateTime1()));
    tmr1->start();
QTimer::singleShot(time1, this, SLOT(foo1()));
}
void SecondWindow::foo1()
{
//ui->statusbar->showMessage("Done");
//QApplication::beep();
tmr1->stop();
ThirdWindow window1;
window1.setModal(true);
window1.exec();
//QMessageBox msgbox1;
//msgbox1.setText("Done!");
//msgbox1.exec();
//player->setMedia(QUrl::fromLocalFile("/Trash/test.mp3"));



}
