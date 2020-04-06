#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "coinbutton.h"
#include <QLabel>
#include <QPropertyAnimation>
#include <QSound>

class playScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit playScene(int levelNum);

    void paintEvent(QPaintEvent *);

    // 判断胜利的函数
    void judgePlayerWin();
    // 关卡属性
    int m_LevelNum;

    // 维护一个关卡数据二维数组
    int m_LevelArray[4][4];

    // 金银币按钮的二维数据
    CoinButton * m_coinBtns[4][4];

    // 判断胜利的标志
    bool m_IsWin;
    // 胜利的图片
    QLabel * winLabel;
    // 胜利的动画
    QPropertyAnimation * winAnimation;
    // 返回按钮音效
    QSound * backBtnSound = NULL;
    // 胜利音效
    QSound * winSound = NULL;
    // 翻币音效
    QSound * FlipSound = NULL;
signals:
    void clickBackBtn();
public slots:
    //接受金银币按钮翻转结束发出来的信号槽函数
    void coinFlipIsOver(int coinPosX, int coinPosY, bool face);
};

#endif // PLAYSCENE_H
