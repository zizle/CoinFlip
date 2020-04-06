#include "coinbutton.h"
#include <QDebug>

CoinButton::CoinButton(QString coinImg)
{
    QPixmap pix;
    bool ret = pix.load(coinImg);
    if(!ret){return;}
    pix = pix.scaled(pix.width() * 1.2, pix.height() *1.2);
    // 设置大小与图片大小一致
    this->setFixedSize(pix.width(), pix.height());
    // 设置不规则样式，去掉自己的border
    this->setStyleSheet("QPushButton{border:0}");
    //设置图标上去
    this->setIcon(QIcon(pix));
    // 设置图标的大小
    this->setIconSize(QSize(pix.width(), pix.height()));
    // 初始化定时器
    this->m_FlipTimer = new QTimer(this);
    // 监听定时器的timeout
    connect(this->m_FlipTimer, &QTimer::timeout, this, &CoinButton::changingFace);

}


// 点击的槽函数
void CoinButton::CoinClicked()
{
    // 改掉正反面标志
    this->m_Face = !this->m_Face;
    this->m_FlipTimer->start(35);  // 启动定时器
    this->m_isFliping = true;
}

// 重写点击事件，防止用户一直点击，金币还没翻转完就重复翻转事件。自定义标志判断
void CoinButton::mousePressEvent(QMouseEvent *e)
{
    if(this->m_isFliping || this->m_IsWin){return;}
    return QPushButton::mousePressEvent(e);
}

// 翻转的槽函数即定时器timeout,此时正反面标志是相反的，因为点击事件中已经修改
void CoinButton::changingFace()
{
    if(this->m_Face)  // 此时this->m_Face=1是反面
    {
        QPixmap pix;
        QString coinImg = QString(":/resource/Coin000%1.png").arg(--this->m_ImgMaxIndex);
        bool ret = pix.load(coinImg);
        if(!ret){
            if(this->m_ImgMinIndex > this->m_ImgMaxIndex)
            {
                this->m_ImgMaxIndex = 8;
                this->m_FlipTimer->stop();
                this->m_isFliping = false;
                // 翻转结束发出信号
                emit flipOver(this->m_PosX, this->m_PoxY, this->m_Face);
            }
            return;
        }
        pix = pix.scaled(pix.width() * 1.2, pix.height() *1.2);
        this->setIcon(QIcon(pix));
        this->setIconSize(QSize(pix.width(), pix.height()));
        if(this->m_ImgMinIndex > this->m_ImgMaxIndex)
        {
            this->m_ImgMaxIndex = 8;
            this->m_FlipTimer->stop();
            this->m_isFliping = false;
            emit flipOver(this->m_PosX, this->m_PoxY, this->m_Face);
        }
    }
    else
    {
        QPixmap pix;
        QString coinImg = QString(":/resource/Coin000%1.png").arg(++this->m_ImgMinIndex);
        bool ret = pix.load(coinImg);
        if(!ret){
            if(this->m_ImgMinIndex > this->m_ImgMaxIndex)
            {
                this->m_ImgMinIndex = 1;
                this->m_FlipTimer->stop();
                this->m_isFliping = false;
                emit flipOver(this->m_PosX, this->m_PoxY, this->m_Face);
            }
            return;
        }
        pix = pix.scaled(pix.width() * 1.2, pix.height() *1.2);
        this->setIcon(QIcon(pix));
        this->setIconSize(QSize(pix.width(), pix.height()));
        // 翻转完了重置
        if(this->m_ImgMinIndex > this->m_ImgMaxIndex)
        {
            this->m_ImgMinIndex = 1;
            this->m_FlipTimer->stop();
            this->m_isFliping = false;
            emit flipOver(this->m_PosX, this->m_PoxY, this->m_Face);
        }
    }
}
