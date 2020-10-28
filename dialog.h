#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include <QMediaPlayer>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QTimer *tmr1;
public slots:
    void foo();
private slots:
    void updateTime();
    void on_radioButton_clicked();
};

#endif // DIALOG_H
