#ifndef DONOTDISTURB_H
#define DONOTDISTURB_H

#include <QDialog>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QMediaPlayer>
namespace Ui {
class Donotdisturb;
}

class Donotdisturb : public QDialog
{
    Q_OBJECT

public:
    explicit Donotdisturb(QWidget *parent = nullptr);
    ~Donotdisturb();
private slots:
    void updateTime3();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public slots:
    void foo2();
private:
    Ui::Donotdisturb *ui;
    QTimer *timer;
};

#endif // DONOTDISTURB_H
