#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"
#include <QSound>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("翻钱币");  // 设置窗口标题
    this->setWindowIcon(QIcon(":/resource/Coin0001.png"));  // 设置窗体图标
    this->setFixedSize(380,588);  // 设置固定大小
    // 点击开始菜单内的退出按钮退出
    connect(ui->actionquit, &QAction::triggered, this,
    [=](){
        this->close();
    });
    // 创建选择关卡的界面
    this->levelScene = new chooseLevelScene;

    // 设置开始按钮
    this->startBtn = new myPushButton(":/resource/MenuSceneStartButton.png");

    this->startBtn->setParent(this);  // 加载到对象树

    this->startBtn->move(this->width()/2 - startBtn->width()/2, this->height() * 0.7);

    // 设置开始按钮音效
    this->startBtnSound = new QSound(":/resource/TapButtonSound.wav", this);
    // 点击开始信号链接
    connect(this->startBtn, &QPushButton::clicked, this, &MainWindow::startButtonClicked);

    // 链接关卡界面的返回按钮信号
    connect(this->levelScene, &chooseLevelScene::clickBackBtn, this, [=](){
        this->levelScene->hide();
        this->setGeometry(this->levelScene->geometry());
        this->show();
    });
}

// 点击开始按钮
void MainWindow::startButtonClicked()
{
    this->startBtnSound->play();
    //qDebug() << "点击了开始";
    this->startBtn->animationDown(); // 向下跳动画
    this->startBtn->animationUp(); // 向上弹动画
    // 设置延时，防止没看到按钮动画
    // 表示在220毫秒之后执行lambda内的代码
    QTimer::singleShot(220, [=](){
        // 进入选择关卡的界面
        this->hide();
        this->levelScene->setGeometry(this->geometry());
        this->levelScene->show();
    });


}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter * painter = new QPainter(this);
    QPixmap pix;
    // 画背景
    pix.load(":/resource/MenuSceneBg.png");
    painter->drawPixmap(0,0,this->width(), this->height(), pix);

    // 画背景图标
//    pix.load(":/resource/Title.png");
//    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
//    painter->drawPixmap(10, 30, pix);
    painter->end();
}

MainWindow::~MainWindow()
{
    delete ui;
}
