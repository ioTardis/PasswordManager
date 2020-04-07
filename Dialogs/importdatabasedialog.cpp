#include "importdatabasedialog.h"
#include "ui_importdatabasedialog.h"
#include "choosedatabasedialog.h"
#include "mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QtSql>

//QString password;
//QString importPath;

ImportDatabaseDialog::ImportDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDatabaseDialog)
{
    ui->setupUi(this);
}

ImportDatabaseDialog::~ImportDatabaseDialog()
{
    delete ui;
}

void ImportDatabaseDialog::on_ExitButton_clicked()
{
    exit(0);
}

void ImportDatabaseDialog::on_PathButton_clicked()
{
    importPath = QFileDialog::getOpenFileName(this, "Открыть файл", "","*.db");
    if (importPath != "") ui->PathEdit->setText(importPath);
}

void ImportDatabaseDialog::on_PathEdit_textChanged(const QString)
{
    importPath = ui->PathEdit->text();
}

void ImportDatabaseDialog::on_PasswordEdit_textChanged(const QString)
{
    QString check = ui->PasswordEdit->text();
    if (check !="") password = check;
}

void ImportDatabaseDialog::on_NextButton_clicked()
{
    if (password !="")
    {
        QFile file(importPath);
        if (importPath !="")
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(importPath);
            db.open();
        } else QMessageBox::warning(0,"Ошибка", "А файла то и нет");
        close();
    } else QMessageBox::warning(0,"Ошибка", "Пароль то введи");

}

void ImportDatabaseDialog::on_BackButton_clicked()
{
    hide();
    ChooseDatabaseDialog ChooseDatabase;
    ChooseDatabase.setModal(true);
    ChooseDatabase.exec();
}
