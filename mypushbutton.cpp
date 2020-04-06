#include "mypushbutton.h"

myPushButton::myPushButton(QString normalImg, QString pressImg)
{
    this->m_NormalImg = normalImg;
    this->m_PressImg = pressImg;
    this->setBgImg(this->m_NormalImg);

}
//设置背景图片
void myPushButton::setBgImg(QString bgImg)
{
    QPixmap pix;
    bool ret = pix.load(bgImg);
    if (!ret){return;};
    // 设置大小与图片大小一致
    this->setFixedSize(pix.width(), pix.height());
    // 设置不规则样式，去掉自己的border
    this->setStyleSheet("QPushButton{border:0}");
    //设置图标上去
    this->setIcon(QIcon(pix));
    // 设置图标的大小
    this->setIconSize(QSize(pix.width(), pix.height()));
}


// 下的动画
void myPushButton::animationDown()
{
    QPropertyAnimation * animationDown = new QPropertyAnimation(this,"geometry");
    animationDown->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animationDown->setEndValue(QRect(this->x(),this->y() + 10,this->width(), this->height()));
    animationDown->setDuration(200);
    animationDown->setEasingCurve(QEasingCurve::OutBounce);
    animationDown->start();
}
// 向上的动画
void myPushButton::animationUp()
{
    QPropertyAnimation * animationUp = new QPropertyAnimation(this, "geometry");
    animationUp->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    animationUp->setEndValue(QRect(this->x(),this->y(),this->width(), this->height()));
    animationUp->setDuration(200);
    animationUp->setEasingCurve(QEasingCurve::OutBounce);
    animationUp->start();
}

void myPushButton::mousePressEvent(QMouseEvent *e)
{
    if (this->m_PressImg != "")
    {
        this->setBgImg(this->m_PressImg);
    }
    return QPushButton::mousePressEvent(e);
}
void myPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    this->setBgImg(this->m_NormalImg);
    return QPushButton::mouseReleaseEvent(e);
}
