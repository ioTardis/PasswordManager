#include "createnewdatabasedialog.h"
#include "ui_createnewdatabasedialog.h"
#include "choosedatabasedialog.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QtSql>

QString password1;
QString password2;
QString createPath;

CreateNewDatabaseDialog::CreateNewDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNewDatabaseDialog)
{
    ui->setupUi(this);

}

CreateNewDatabaseDialog::~CreateNewDatabaseDialog()
{
    delete ui;
}

void CreateNewDatabaseDialog::on_ExitButton_clicked()
{
    exit(0);
}

void CreateNewDatabaseDialog::on_OpenPathButton_clicked()
{
    createPath = QFileDialog::getSaveFileName(this, "Сохранить файл", "","*.db");
    if (createPath != "") ui->PathEdit->setText(createPath);
}

void CreateNewDatabaseDialog::on_PathEdit_textChanged(const QString)
{
    createPath = ui->PathEdit->text();
}

void CreateNewDatabaseDialog::on_PasswordEdit_textChanged(const QString)
{
    QString check = ui->PasswordEdit->text();
    if (check !="") password1 = check;
}


void CreateNewDatabaseDialog::on_Password2Edit_textChanged(const QString)
{
    QString check = ui->Password2Edit->text();
    if (check !="") password2 = check;
}

void CreateNewDatabaseDialog::on_NextButton_clicked()
{
    QFile file(createPath);
    if (password1 == "" || password2 == "") QMessageBox::warning(0,"Ошибка", "Пароль введи слыш");
    else
    {
        if (password1 != password2) QMessageBox::warning(0,"Ошибка", "Пароли не совпадают");
        else if (createPath !="")
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(createPath);
            db.open();
            QSqlQuery query;
            query.exec("CREATE TABLE passwords "
                       "(ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "login VARCHAR(30), "
                       "password VARCHAR(40), "
                       "source VARCHAR(100), "
                       "name TEXT, "
                       "notes TEXT, "
                       "tag VARCHAR(100))");
            query.clear();
            query.exec("INSERT INTO passwords (login, password, source, name, notes, tag)"
                       "VALUES ('zina4ka', 'zina666', 'mail.ru', 'Ящик', 'почта', 'майлру')");
            query.clear();
            close();
        } else QMessageBox::warning(0,"Ошибка", "Куда сохранять то?");
    }

}

void CreateNewDatabaseDialog::on_BackButton_clicked()
{
    hide();
    ChooseDatabaseDialog ChooseDatabase;
    ChooseDatabase.setModal(true);
    ChooseDatabase.exec();
}
