#include "thirdwindow.h"
#include "ui_thirdwindow.h"

ThirdWindow::ThirdWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThirdWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Alarm clock");
    tmr2 = new QTimer(this);
    tmr2->setInterval(1000);
    connect(tmr2, SIGNAL(timeout()), this, SLOT(updateTime2()));
    tmr2->start();
    player = new QMediaPlayer(this);
    connect(player,&QMediaPlayer::positionChanged,this,&ThirdWindow::on_positionChanged);
    connect(player,&QMediaPlayer::durationChanged,this,&ThirdWindow::on_durationChanged);

player->setMedia(QUrl::fromLocalFile("/Users/lanbo/Documents/timer_test/alarmsound.wav"));
player->play();

}
ThirdWindow::~ThirdWindow()
{
    delete ui;
}
void ThirdWindow::updateTime2()
{
    ui->label_2->setText(QTime::currentTime().toString()); // Обновляем время на экране
}

void ThirdWindow::on_pushButton_2_clicked()
{
    //QApplication::quit();
    QDialog::reject();
}

void ThirdWindow::on_horizontalSlider_sliderMoved(int position)
{
player->setVolume(position);
}

void ThirdWindow::on_positionChanged(qint64 position)
{

}

void ThirdWindow::on_durationChanged(qint64 position)
{

}

void ThirdWindow::on_pushButton_clicked()
{
 player->stop();
 tmr2 = new QTimer(this);
 tmr2->setInterval(1000);
 connect(tmr2, SIGNAL(timeout()), this, SLOT(updateTime2()));
 tmr2->start();
 QTimer::singleShot(10000, this, SLOT(foo1()));
}


void ThirdWindow::foo1()
{
    player->setMedia(QUrl::fromLocalFile("/Users/lanbo/test/Lab_oop/timer_test/alarmsound.wav"));
    player->play();
}
