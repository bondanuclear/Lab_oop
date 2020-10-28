#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H
#include "thirdwindow.h"
#include <QDialog>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QMediaPlayer>
namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private slots:
    void on_pushButton_clicked();
public slots:
    void foo1();
private slots:
     void updateTime1();
private:
    Ui::SecondWindow *ui;
    QTimer *tmr1;
};

#endif // SECONDWINDOW_H
