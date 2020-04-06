#include "playscene.h"
#include <QMenuBar>
#include <QAction>
#include "mypushbutton.h"
#include <QTimer>
#include <QPainter>
#include <QLabel>
#include "coinbutton.h"
#include "dataconfig.h"
#include <QDebug>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QRect>
#include <QEasingCurve>

playScene::playScene(int levelNum)
{
    this->m_LevelNum = levelNum;

    // 初始化窗口
    this->setFixedSize(380,588);
    this->setWindowTitle("翻钱币-选择关卡");  // 设置窗口标题
    this->setWindowIcon(QIcon(":/resource/Coin0001.png"));  // 设置窗体图标
    // 添加菜单栏
    QMenuBar * menuBar = this->menuBar();
    this->setMenuBar(menuBar);
    QMenu * startMenu = menuBar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction, &QAction::triggered, this, [=](){
        this->close();
    });
    // 添加返回按钮
    myPushButton * backBtn = new myPushButton(":/resource/BackButton.png", ":/resource/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());
    this->backBtnSound = new QSound(":/resource/BackButtonSound.wav");
    this->FlipSound = new QSound(":/resource/ConFlipSound.wav");
    this->winSound = new QSound(":/resource/LevelWinSound.wav");

    // 发出信号
    connect(backBtn, &myPushButton::clicked, this, [=](){
        QTimer::singleShot(100, this, [=](){
            this->backBtnSound->play();
            emit this->clickBackBtn();
        });
    });

    // 显示当前关卡
    QLabel * levelLabel = new QLabel(this);
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(20);
    levelLabel->setFont(font);
    levelLabel->setText(QString("Level %1").arg(this->m_LevelNum));
    levelLabel->setGeometry(30, this->height() - 50, 120,50);

    // 初始化关卡数据
    DataConfig dataconfig;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->m_LevelArray[i][j] = dataconfig.m_Data[this->m_LevelNum][i][j];
        }
    }
    // 监听金币翻转成功后发回来的信号用于维护m_LevelArray

    // 绘制金币背景
    for (int i=0; i<4;i++)
    {
        for (int j= 0; j< 4;j++)
        {
            QLabel * coinBg = new QLabel(this);
            QPixmap pix = QPixmap(":/resource/BoardNode.png");
            pix = pix.scaled(pix.width() * 1.2, pix.height() * 1.2);
            coinBg->setGeometry(0,0,pix.width(),pix.height());
            coinBg->setPixmap(pix);
            coinBg->move(75 + i * pix.width(), 180 + j *pix.height());

            // 根据数据设置金币或者银币
            QString coinInitImg;
            if (this->m_LevelArray[i][j] == 1)
            {
                coinInitImg = ":/resource/Coin0001.png";
            }
            else
            {
                coinInitImg = ":/resource/Coin0008.png";
            }
            CoinButton * coinBtn = new CoinButton(coinInitImg);
            coinBtn->setParent(coinBg);
            coinBtn->move(2,4);  // 微调位置居中
            // 设置金币的属性
            coinBtn->m_PosX = i;
            coinBtn->m_PoxY = j;
            coinBtn->m_Face = this->m_LevelArray[i][j]; // 1是正面 0是反面

            this->m_coinBtns[i][j] = coinBtn;

            void (playScene:: *coinFlipOver)(int pX, int pY, bool cf) = &playScene::coinFlipIsOver;
            connect(coinBtn, &CoinButton::flipOver, this, coinFlipOver);

            // 监听金银币的点击事件
            connect(coinBtn,&CoinButton::clicked, [=](){
                this->FlipSound->play();
                coinBtn->CoinClicked();  // 翻转金银币

                // 延时翻转周围金币
                QTimer::singleShot(150,[=](){
                    if(coinBtn->m_PosX + 1 <= 3)
                    {
                        this->m_coinBtns[coinBtn->m_PosX+1][coinBtn->m_PoxY]->CoinClicked();
                    }
                    if(coinBtn->m_PosX - 1 >=0)
                    {
                        this->m_coinBtns[coinBtn->m_PosX-1][coinBtn->m_PoxY]->CoinClicked();
                    }
                    if(coinBtn->m_PoxY + 1 <=3)
                    {
                        this->m_coinBtns[coinBtn->m_PosX][coinBtn->m_PoxY + 1]->CoinClicked();
                    }
                    if(coinBtn->m_PoxY - 1 >=0)
                    {
                        this->m_coinBtns[coinBtn->m_PosX][coinBtn->m_PoxY - 1]->CoinClicked();
                    }
                });



            });
        }
    }

    // 绘制胜利图片
    this->winLabel = new QLabel;
    QPixmap winPix;
    winPix.load(":/resource/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,winPix.width(), winPix.height());
    winLabel->setPixmap(winPix);
    winLabel->setParent(this);
    winLabel->move(this->width() *0.5 - winPix.width() *0.5 , -winPix.height());

    this->winAnimation = new QPropertyAnimation(this->winLabel, "geometry");
    this->winAnimation->setStartValue(QRect(this->winLabel->x(), this->winLabel->y(), this->winLabel->width(), this->winLabel->height()));
    this->winAnimation->setEndValue(QRect(this->winLabel->x(), this->winLabel->y() + 150, this->winLabel->width(), this->winLabel->height()));
    this->winAnimation->setDuration(1000);
    this->winAnimation->setEasingCurve(QEasingCurve::OutBounce);
}


// 重写paintEvent事件，绘制背景
void playScene::paintEvent(QPaintEvent *)
{
    QPainter * painter = new QPainter(this);
    QPixmap pix;
    // 画背景
    pix.load(":/resource/PlayLevelSceneBg.png");
    painter->drawPixmap(0,0,this->width(), this->height(), pix);
    // 画背景图标

    pix.load(":/resource/Title.png");
//    pix = pix.scaled(pix.width() * 0.5, pix.height() *0.5);
    painter->drawPixmap(this->width() *0.5 - pix.width() * 0.5, 30, pix);
    painter->end();
}


void playScene::coinFlipIsOver(int coinPosX, int coinPosY, bool face)
{
    //qDebug() << QString("翻转结束, %1, %2, %3").arg(coinPosX).arg(coinPosY).arg(face);
    // 修改维护的二维数据
    this->m_LevelArray[coinPosX][coinPosY] = face;
    // 每个金银币翻完之后判断是否胜利
    this->judgePlayerWin();
}

// 判断胜利的标志
void playScene::judgePlayerWin()
{
    this->m_IsWin = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(this->m_coinBtns[i][j]->m_Face == false)
            {
                this->m_IsWin = false;
                break;
            }
        }
    }
    if (this->m_IsWin)
    {
        //qDebug() << "胜利啦";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_coinBtns[i][j]->m_IsWin = true;
            }
        }
        // 动画加载胜利图片
        if (this->winAnimation->state() == QPropertyAnimation::Stopped)  // 只允许加载一次，而不是5个按钮返回都加载一次
        {
            qDebug() << "动画加载胜利图片";
           this->winAnimation->start();
            this->winSound->play();
        }
    }

}
