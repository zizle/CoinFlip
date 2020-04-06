#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QPainter>
#include "playscene.h"
#include <QSound>


class chooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseLevelScene(QWidget *parent = nullptr);
    // 重写paintEvent事件，绘制背景
    void paintEvent(QPaintEvent *);
    // 游戏场景
    playScene * play = NULL;
    // 选择关卡的音效
    QSound * backBtnSound = NULL;
    QSound * chooseLevelSound = NULL;

signals:
    void clickBackBtn();

public slots:
};

#endif // CHOOSELEVELSCENE_H
