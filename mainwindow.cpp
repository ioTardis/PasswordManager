#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Dialogs/hellodialog.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>

//qDebug для отображения инфы в строку

QString path;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_9_clicked()
{
    HelloDialog hellodialog;
    hellodialog.setModal(true);
    hellodialog.exec();
}

void MainWindow::recieveMessage(QString fileNameGet)
{
    path = fileNameGet;
    QFile file(path);
    if (file.open(QIODevice::Append | QIODevice::Text)){
        QString pass = file.readAll();
        file.close();
        qDebug() << QString(pass);
        file.close();
    } else QMessageBox::warning(0,"Ошибка", "Ошибачка с сохранением?");
    qDebug() << "все заебумба";
}

void MainWindow::recieveMessage2(QString fileNameGet2)
{
    path = fileNameGet2;
    QFile file(path);
    if (file.open(QIODevice::Append | QIODevice::Text)){
        QString pass = file.readAll();
        file.close();
        qDebug() << QString(pass);
        file.close();
    } else QMessageBox::warning(0,"Ошибка", "Ошибачка с сохранением?");
    qDebug() << "все заебумба";
}
