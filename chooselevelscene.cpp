#include "chooselevelscene.h"
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QString>
#include <QDebug>
#include "playscene.h"
#include <QSound>

chooseLevelScene::chooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
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
    // 添加返回按钮音效
    this->backBtnSound = new QSound(":/resource/BackButtonSound.wav");
    // 添加选择关卡音效
    this->chooseLevelSound = new QSound(":/resource/TapButtonSound.wav");
    // 发出信号
    connect(backBtn, &myPushButton::clicked, this, [=](){
        QTimer::singleShot(100, this, [=](){
            this->backBtnSound->play();
            emit this->clickBackBtn();
        });
    });

    // 添加关卡选择按钮
    for (int i = 0; i < 20; i++)
    {
        myPushButton * levelBtn = new myPushButton(":/resource/LevelIcon.png");
        levelBtn->setParent(this);
        levelBtn->move( 55 + i % 4 * 70, 120 + i / 4 * 70);
        // 添加按钮点击事件
        connect(levelBtn, &myPushButton::clicked, this, [=](){
            //qDebug() << QString("点击了第%1关").arg(i + 1);
            this->chooseLevelSound->play();
            play = new playScene(i + 1); // 创建关卡游戏场景

            connect(play, &playScene::clickBackBtn, this, [=](){
                this->setGeometry(play->geometry());
                delete play;
                play = NULL;
                this->show();
            }); //链接信号//
            this->hide();
            play->setGeometry(this->geometry());
            play->show();

        });

        // 添加关卡文字显示
        QLabel * lb = new QLabel(levelBtn);
        lb->setText( QString::number(i + 1));
        lb->setFixedSize(levelBtn->width(), levelBtn->height());
        lb->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
}


// 重写paintEvent事件，绘制背景
void chooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter * painter = new QPainter(this);
    QPixmap pix;
    // 画背景
    pix.load(":/resource/OtherSceneBg.png");
    painter->drawPixmap(0,0,this->width(), this->height(), pix);
    // 画背景图标

    pix.load(":/resource/Title.png");
    painter->drawPixmap(this->width() *0.5 - pix.width() * 0.5, 30, pix);
    painter->end();
}
