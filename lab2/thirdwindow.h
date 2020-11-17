#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QMediaPlayer>
namespace Ui {
class ThirdWindow;
}

class ThirdWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ThirdWindow(QWidget *parent = nullptr);
    ~ThirdWindow();
    public slots:
    void foo1();

private slots:
     void updateTime2();
     void on_pushButton_2_clicked();

     void on_horizontalSlider_sliderMoved(int position);
     void on_positionChanged(qint64 position);
     void on_durationChanged(qint64 position);
     void on_pushButton_clicked();

private:
     QTimer *tmr2;
    Ui::ThirdWindow *ui;
    QMediaPlayer* player;
};

#endif // THIRDWINDOW_H
