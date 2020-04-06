#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit myPushButton(QWidget *parent = nullptr);
    myPushButton(QString normalImg, QString pressImg="");

    //设置背景图片
    void setBgImg(QString bgImg);

    // 向下的动画
    void animationDown();
    // 向上的动画
    void animationUp();

    // 重写按下和释放鼠标的事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    // 成员属性
    QString m_NormalImg;
    QString m_PressImg;

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
