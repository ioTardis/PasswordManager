#include "importdatabasedialog.h"
#include "ui_importdatabasedialog.h"
#include "choosedatabasedialog.h"
#include "mainwindow.h"
#include "Qt-AES/qaesencryption.h"

#include <QCryptographicHash>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QtSql>

/*
 * Window opens an existing database. Available both at the beginning of the program and in the main window menu
 * Path and password transmitted to the main window using a signal sendInfo
*/

ImportDatabaseDialog::ImportDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDatabaseDialog){
    ui->setupUi(this);

    MainWindow *main = new MainWindow();
    connect(this, SIGNAL(sendInfo(QString,QString,int)),
            main, SLOT(recieveMessage(QString,QString,int)));
}

ImportDatabaseDialog::~ImportDatabaseDialog(){
    delete ui;
}

void ImportDatabaseDialog::on_ExitButton_clicked(){
    exit(0);
}

void ImportDatabaseDialog::on_PathButton_clicked(){
    importPath = QFileDialog::getOpenFileName(this, "Open file", "","*.db");
    if (importPath != "") ui->PathEdit->setText(importPath);
}

void ImportDatabaseDialog::on_PathEdit_textChanged(const QString){
    importPath = ui->PathEdit->text();
}

void ImportDatabaseDialog::on_importPasswordEdit_textChanged(const QString &arg1) {
    QString check = ui->importPasswordEdit->text();
    if (check !="") importPassword = check;
}

void ImportDatabaseDialog::on_NextButton_clicked() {
    QFile file(importPath);
    if (importPassword !="") {
        if (importPassword.size() != 16 ) QMessageBox::warning(0,"Error", "The password must contain 16 characters");
        else if (importPath !="") {
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(importPath);
            db.open();
        } else QMessageBox::warning(0,"Error", "File does not exist");
        emit sendInfo(importPath,importPassword, 1);
        close();
    } else QMessageBox::warning(0,"Error", "Enter the password");

}

void ImportDatabaseDialog::on_BackButton_clicked() {
    hide();
    ChooseDatabaseDialog ChooseDatabase;
    ChooseDatabase.setModal(true);
    ChooseDatabase.exec();
}

