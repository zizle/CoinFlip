#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QPushButton>
#include <QTimer>

class CoinButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit CoinButton(QWidget *parent = nullptr);
    CoinButton(QString coinImg);

    // 增加点击后的链接函数
    void CoinClicked();

    // 定时器结束的槽函数
    void changingFace();

    void mousePressEvent(QMouseEvent *);

    // 金币的位置属性
    int m_PosX;
    int m_PoxY;
    bool m_Face;

    QTimer * m_FlipTimer;  // 定时器对象用于翻转金银币
    int m_ImgMinIndex = 1;
    int m_ImgMaxIndex = 8;
    bool m_isFliping = false; // 正在翻转的标志
    bool m_IsWin = false;

signals:
    void flipOver(int posX, int posY, bool c_Face);

public slots:
};

#endif // COINBUTTON_H
