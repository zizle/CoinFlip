#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include "mypushbutton.h"
#include "chooselevelscene.h"
#include <QSound>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 重写paintEvent事件，绘制背景
    void paintEvent(QPaintEvent *);

    // 开始按钮
    myPushButton * startBtn = NULL;
    // 点击开始按钮的音效
    QSound * startBtnSound = NULL;
    // 关卡选择界面
    chooseLevelScene * levelScene = NULL;

public slots:
    // 开始按钮点击
    void startButtonClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
