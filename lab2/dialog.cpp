#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_radioButton_clicked()
{
    int time = ui->spinBox->value();
    tmr1 = new QTimer(this);
    tmr1->setInterval(1000);
    connect(tmr1, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr1->start();
QTimer::singleShot(time, this, SLOT(foo()));
}
void Dialog::foo()
{
ui->statusbar->showMessage("Done");
QApplication::beep();
tmr->stop();
QMessageBox msgbox;
msgbox.setText("Done!");
msgbox.exec();
//player->setMedia(QUrl::fromLocalFile("/Trash/test.mp3"));



}
