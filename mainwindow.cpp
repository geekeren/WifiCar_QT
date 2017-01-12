#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkRequest>
#include<QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //显示图片
    QPixmap pixmap(":/shot");

    ui->label->setPixmap(pixmap);
    ui->label->setScaledContents(true);
    ui->label->resize(ui->label->width(),ui->label->height());
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(setNetworkPic())); // ***就是你所说的响应函数
    timer->start(80); // 每隔80ms


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::setNetworkPic()
{
    QString szUrl = "http://192.168.8.1:8083/?action=snapshot";
    QUrl url(szUrl);
    QNetworkAccessManager manager;
    QEventLoop loop;

    // qDebug() << "Reading picture form " << url;
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //开启子事件循环
    loop.exec();

    QByteArray jpegData = reply->readAll();
    if(jpegData.length()>0){
        QPixmap pixmap;
    pixmap.loadFromData(jpegData);
   if(pixmap.width()>0)
       ui->label->setPixmap(pixmap); // 你在QLabel显示图片
    }

}
