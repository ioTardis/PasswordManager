#include "importdatabasedialog.h"
#include "ui_importdatabasedialog.h"
#include "choosedatabasedialog.h"
#include "mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QtSql>


ImportDatabaseDialog::ImportDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDatabaseDialog)
{
    ui->setupUi(this);

    MainWindow *main = new MainWindow();
    connect(this, SIGNAL(sendPath(QString, int)),
            main, SLOT(recieveMessage(QString, int)));
}

ImportDatabaseDialog::~ImportDatabaseDialog()
{
    delete ui;
}

void ImportDatabaseDialog::on_ExitButton_clicked()//Функция выхода из программы
{
    exit(0);
}

void ImportDatabaseDialog::on_PathButton_clicked() //Функция открытия диалогового окна открытия файла
{
    importPath = QFileDialog::getOpenFileName(this, "Открыть файл", "","*.db");
    if (importPath != "") ui->PathEdit->setText(importPath);
}

void ImportDatabaseDialog::on_PathEdit_textChanged(const QString)//Функция записи пути из PathEdit
{
    importPath = ui->PathEdit->text();
}

void ImportDatabaseDialog::on_PasswordEdit_textChanged(const QString)//Функция записи пароля из PathEdit
{
    QString check = ui->PasswordEdit->text();
    if (check !="") password = check;
}

void ImportDatabaseDialog::on_NextButton_clicked() //Функция, открывающая БД и открывающая соединение с ней
{
    if (password !="")
    {
        QFile file(importPath);
        if (importPath !="")
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//Подключение драйвера БД
            db.setDatabaseName(importPath);//Подключение к БД
            db.open();//Открытие БД
        } else QMessageBox::warning(0,"Ошибка", "А файла то и нет");
        emit sendPath(importPath, 1);
        close();//Закрытие диалогового окна
    } else QMessageBox::warning(0,"Ошибка", "Пароль то введи");

}

void ImportDatabaseDialog::on_BackButton_clicked()
{
    hide();
    ChooseDatabaseDialog ChooseDatabase;
    ChooseDatabase.setModal(true);
    ChooseDatabase.exec();
}
