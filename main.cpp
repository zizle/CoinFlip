#include "mainwindow.h"
#include <QApplication>
#include "dataconfig.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // 测试关卡数据
//    DataConfig config;
//    for (int var = 0; var < 4; var++) {
//        for (int j=0; j<4; j++) {
//            qDebug() << config.m_Data[1][var][j];
//        }
//        qDebug() << "";
//    }

    return a.exec();
}
