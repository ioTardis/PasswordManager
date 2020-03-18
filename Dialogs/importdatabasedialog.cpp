#include "importdatabasedialog.h"
#include "ui_importdatabasedialog.h"
#include "choosedatabasedialog.h"
#include "mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

//QString password;
//QString importPath;

ImportDatabaseDialog::ImportDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDatabaseDialog)
{
    ui->setupUi(this);

    main = new MainWindow();
    connect(this, SIGNAL(sendFile(QString)),
            main, SLOT(recieveMessage(QString)));

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
    importPath = QFileDialog::getOpenFileName(this, "Открыть файл", "","*.txt");
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
            if (file.open(QIODevice::ReadOnly))
            {
                QString info = file.readAll();
                file.close();
                qDebug() << QString(info);
                close();
            } else QMessageBox::warning(0,"Ошибка", "Ошибачка с открытием");
        } else QMessageBox::warning(0,"Ошибка", "А файла то и нет");
        emit sendFile(importPath);
    } else QMessageBox::warning(0,"Ошибка", "Пароль то введи");

}

void ImportDatabaseDialog::on_BackButton_clicked()
{
    hide();
    ChooseDatabaseDialog ChooseDatabase;
    ChooseDatabase.setModal(true);
    ChooseDatabase.exec();
}
