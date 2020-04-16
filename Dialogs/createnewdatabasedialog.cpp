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

    MainWindow *main = new MainWindow();
    connect(this, SIGNAL(sendPath(QString, int)),
            main, SLOT(recieveMessage(QString, int)));
}

CreateNewDatabaseDialog::~CreateNewDatabaseDialog()
{
    delete ui;
}

void CreateNewDatabaseDialog::on_ExitButton_clicked() //Функция выхода из программы
{
    exit(0);
}

void CreateNewDatabaseDialog::on_OpenPathButton_clicked() //Функция открытия диалогового окна сохранения файла
{
    createPath = QFileDialog::getSaveFileName(this, "Сохранить файл", "","*.db");
    if (createPath != "") ui->PathEdit->setText(createPath);
}

void CreateNewDatabaseDialog::on_PathEdit_textChanged(const QString) //Функция записи пути из PathEdit
{
    createPath = ui->PathEdit->text();
}

void CreateNewDatabaseDialog::on_PasswordEdit_textChanged(const QString) //Функция записи пароля из PathEdit
{
    QString check = ui->PasswordEdit->text();
    if (check !="") password1 = check;
}


void CreateNewDatabaseDialog::on_Password2Edit_textChanged(const QString)
{
    QString check = ui->Password2Edit->text();
    if (check !="") password2 = check;
}

void CreateNewDatabaseDialog::on_NextButton_clicked() //Функция, создающая новую базу данных и открывающая новое соединение с ней
{
    QFile file(createPath);
    if (password1 == "" || password2 == "") QMessageBox::warning(0,"Ошибка", "Пароль введи слыш");
    else
    {
        if (password1 != password2) QMessageBox::warning(0,"Ошибка", "Пароли не совпадают");
        else if (createPath !="")
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //Подключение драйвера БД
            db.setDatabaseName(createPath); //Подключение к БД
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
            emit sendPath(createPath, 1);
            close();//Закрытие диалогового окна
        } else QMessageBox::warning(0,"Ошибка", "Куда сохранять то?");
    }

}

void CreateNewDatabaseDialog::on_BackButton_clicked()//Функция перехода на предыдущее окно
{
    hide();
    ChooseDatabaseDialog ChooseDatabase;
    ChooseDatabase.setModal(true);
    ChooseDatabase.exec();
}
