#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Dialogs/hellodialog.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QClipboard>
#include <QtSql>

//qDebug для отображения инфы в строку

QString path;
QString name;
QString source;
QString login;
QString password;
QString note;
QString tag;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlQuery query;
    query.exec("SELECT * FROM passwords");
    while (query.next()) {
    QString zina = query.value(0).toString() + query.value(1).toString() + query.value(2).toString() + query.value(3).toString() + query.value(4).toString() + query.value(5).toString();
    qDebug() << zina;
    }
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

void MainWindow::on_NameEdit_textChanged(const QString)
{
    name = ui->NameEdit->text();
}

void MainWindow::on_SourceEdit_textChanged(const QString)
{
    source = ui->SourceEdit->text();
}

void MainWindow::on_LoginEdit_textChanged(const QString)
{
    login = ui->LoginEdit->text();
}

void MainWindow::on_PasswordEdit_textChanged(const QString)
{
    password = ui->PasswordEdit->text();
}

void MainWindow::on_NoteEdit_textChanged(const QString)
{
    note = ui->NoteEdit->text();
}

void MainWindow::on_SaveButton_clicked()
{
    QSqlQuery edquery;
    qDebug() << login + password + source + name + note + tag;
    edquery.prepare("INSERT INTO passwords (login, password, source, name, notes, tag) "
                 "VALUES (:login, :password, :source, :name, :notes, :tag)");
    edquery.bindValue(":login", login);
    edquery.bindValue(":password", password);
    edquery.bindValue(":source", source);
    edquery.bindValue(":name", name);
    edquery.bindValue(":notes", note);
    edquery.bindValue(":tag", tag);
    edquery.exec();
    edquery.clear();
}

void MainWindow::on_CleanButton_clicked()
{
    name = "";
    source = "";
    login = "";
    password = "";
    note = "";
    tag = "";
    ui->NameEdit->setText("");
    ui->SourceEdit->setText("");
    ui->LoginEdit->setText("");
    ui->PasswordEdit->setText("");
    ui->NoteEdit->setText("");
    ui->TagEdit->setText("");
}



void MainWindow::on_CopySourceButton_clicked()
{
    source = ui->SourceEdit->text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(source);
}

void MainWindow::on_CopyLoginButton_clicked()
{
    login = ui->LoginEdit->text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(login);
}

void MainWindow::on_CopyPasswordButton_clicked()
{
    password = ui->PasswordEdit->text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(password);
}

void MainWindow::on_TagEdit_textChanged(const QString)
{
    tag = ui->TagEdit->text();
}
