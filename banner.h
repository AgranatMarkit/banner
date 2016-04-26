#ifndef BANNER_H
#define BANNER_H

#include <QWidget>
#include <QLabel>
#include <QDesktopWidget>
#include <QRect>
#include <QPoint>
#include <QApplication>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QPropertyAnimation>
#include <unistd.h>
#include <ctime>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QByteArray>
#include <QSettings>
#include <windows.h>
#include <string>

namespace Ui {
class banner;
}

class banner : public QWidget
{
    Q_OBJECT

public:
    explicit banner(QWidget *parent = 0);
    ~banner();

private slots:
    void on_pushButton_clicked();

private:
    Ui::banner *ui;
    QPushButton *btn;
    QLabel *lbl;
    void initializeAnimation();
    void onLoad();
    void copyToLoader();
};

#endif // BANNER_H
