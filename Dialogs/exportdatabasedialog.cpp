#include "exportdatabasedialog.h"
#include "ui_exportdatabasedialog.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QtSql>

QString password1;
QString password2;
QString createPath;

ExportDatabaseDialog::ExportDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDatabaseDialog)
{
    ui->setupUi(this);
}

ExportDatabaseDialog::~ExportDatabaseDialog()
{
    delete ui;
}

void ExportDatabaseDialog::on_PathEdit_textChanged(const QString &arg1)
{
    createPath = ui->PathEdit->text();
}

void ExportDatabaseDialog::on_PathButton_clicked()
{
    createPath = QFileDialog::getSaveFileName(this, "Сохранить файл", "","*.db");
    if (createPath != "") ui->PathEdit->setText(createPath);
}

void ExportDatabaseDialog::on_OKButton_clicked()
{
    password1 = ui->PasswordEdit->text();
    password2 = ui->Password2Edit->text();
    QFile file(createPath);
    if (password1 == "" || password2 == "") QMessageBox::warning(0,"Ошибка", "Пароль введи слыш");
    else
    {
        if (password1 != password2) QMessageBox::warning(0,"Ошибка", "Пароли не совпадают");
        else if (createPath !="")
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //Подключение драйвера БД
            db.setDatabaseName(createPath); //Подключение к БД
            db.setPassword(password1);
            db.open(); //Открытие БД

            QSqlQuery query;
            query.exec("CREATE TABLE passwords "
                       "(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                       "login VARCHAR(30) NOT NULL, "
                       "password VARCHAR(40) NOT NULL, "
                       "source VARCHAR(100), "
                       "name TEXT, "
                       "notes TEXT, "
                       "tag VARCHAR(100))"); //Выполнение SQL-запроса с созданием новой таблицы в БД
            query.clear();//Очистка запроса
            close();//Закрытие диалогового окна
        } else QMessageBox::warning(0,"Ошибка", "Куда сохранять то?");
    }
}

void ExportDatabaseDialog::on_ExitButton_clicked()
{
    delete ui;
}
