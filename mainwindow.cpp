#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Dialogs/hellodialog.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>

//qDebug для отображения инфы в строку

QString path;
QString zazaa;
QString name;
QString source;
QString login;
QString password;
QString note;

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
    if (file.open(QIODevice::WriteOnly))
    {
        file.write("Писю мужичка.\n");
        qDebug() << "все заебумба";
        file.close();
    } else QMessageBox::warning(0,"Ошибка", "Ошибачка с сохранением?");
}


void MainWindow::on_NameEdit_textChanged(const QString &arg1)
{
    name = ui->NameEdit->text();
}

void MainWindow::on_SourceEdit_textChanged(const QString &arg1)
{
    source = ui->SourceEdit->text();
}

void MainWindow::on_LoginEdit_textChanged(const QString &arg1)
{
    login = ui->LoginEdit->text();
}

void MainWindow::on_PasswordEdit_textChanged(const QString &arg1)
{
    password = ui->PasswordEdit->text();
}

void MainWindow::on_NoteEdit_textChanged(const QString &arg1)
{
    note = ui->NoteEdit->text();
}

void MainWindow::on_SaveButton_clicked()
{
    qDebug() << name + " " + source + " " + login + " " + password + " " + note;
}

void MainWindow::on_CleanButton_clicked()
{
    name = "";
    source = "";
    login = "";
    password = "";
    note = "";
    ui->NameEdit->setText("");
    ui->SourceEdit->setText("");
    ui->LoginEdit->setText("");
    ui->PasswordEdit->setText("");
    ui->NoteEdit->setText("");
}


