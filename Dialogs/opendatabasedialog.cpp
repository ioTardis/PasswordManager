#include "opendatabasedialog.h"
#include "ui_opendatabasedialog.h"
#include "choosedatabasedialog.h"
#include "mainwindow.h"

#include <QSettings>
#include <QFile>
#include <QMessageBox>
#include <QtSql>

QString path;

opendatabasedialog::opendatabasedialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::opendatabasedialog)
{
    ui->setupUi(this);

    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.beginGroup( "Database" );
    path = settings.value( "Path", "" ).toString();
    settings.endGroup();

    ui->Path->setText(path);

//    MainWindow *main = new MainWindow();
//    connect(this, SIGNAL(sendAuth(QString, int)),
//            main, SLOT(recieveMessage(QString, int)));
}

opendatabasedialog::~opendatabasedialog()
{
    delete ui;
}

void opendatabasedialog::on_AnotherDBButton_clicked()
{
    hide();
    ChooseDatabaseDialog ChooseDatabase;
    ChooseDatabase.setModal(true);
    ChooseDatabase.exec();
}

void opendatabasedialog::on_OKButton_clicked()
{
    QString password = ui->PasswordEdit->text();
    QFile file(path);
    if (password !="")
    {
        QFile file(path);
        if (path !="")
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//Подключение драйвера БД
            db.setDatabaseName(path);//Подключение к БД
            db.open();//Открытие БД
        } else QMessageBox::warning(0,"Ошибка", "А файла то и нет");
        emit sendPath(path, 1);
        close();//Закрытие диалогового окна
    } else QMessageBox::warning(0,"Ошибка", "Пароль то введи");
}

void opendatabasedialog::on_ExitButton_clicked()
{
    delete ui;
    close();
}
