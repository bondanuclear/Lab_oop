#include "donotdisturb.h"
#include "ui_donotdisturb.h"
#include <QDebug>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QApplication>
#include <QListWidget>
#include <QString>
#include <QSoundEffect>
#include <QtCore>
#include <QtGui>
#include <QStatusBar>
#include <QPixmap>
Donotdisturb::Donotdisturb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Donotdisturb)
{
    ui->setupUi(this);
    QPixmap pix(":/res/img/donot.png");
    int w = ui->image->width();
int h = ui->image->height();
ui->image->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

Donotdisturb::~Donotdisturb()
{
    delete ui;
    delete timer;
}
void Donotdisturb::updateTime3()
{
    ui->label_2->setText(QTime::currentTime().toString()); // Обновляем время на экране
}
void Donotdisturb::on_pushButton_clicked()
{
    int time2 = ui->spinBox->value();
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime3()));
    timer->start();
QTimer::singleShot(time2, this, SLOT(foo2()));
}
void Donotdisturb::foo2()
{

timer->stop();
QMessageBox msgbox;
msgbox.setText("Done!");
msgbox.exec();




}

void Donotdisturb::on_pushButton_2_clicked()
{
    QListWidgetItem * item = new QListWidgetItem;
    item->setText("The timer worked " + ui->spinBox->cleanText() + " ms");
    ui->listWidget->addItem(item);
}
