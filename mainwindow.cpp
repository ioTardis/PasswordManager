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

int auth = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.beginGroup( "Database" );
    path = settings.value( "Path", "" ).toString();
    settings.endGroup();
    if (path != "")
    {
        auth = 1;
        QFile file(path);
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//Подключение драйвера БД
        db.setDatabaseName(path);//Подключение к БД
        db.open();//Открытие БД
    } else QMessageBox::warning(0,"Ошибка", "А файла то и нет");

    if (auth == 0) //Отображение диалоговых окон перед основным
    {
        auth = 1;
        HelloDialog hellodialog;
        hellodialog.setModal(true);
        hellodialog.exec();
    }
    if (auth == 1)
    {
        updateQListWidget();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recieveMessage(QString getPath, int getAuth)
{
    path = getPath;
    auth = 1;

    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.beginGroup("Database");
    settings.setValue("Path", path);
    settings.endGroup();
}

void MainWindow::updateQListWidget() //Функция обновления QListWidget
{
    QSqlQuery listoutquery; //Создание переменной запроса
    listoutquery.exec("SELECT name, id FROM passwords");
    while(listoutquery.next()) //Перебор результатов запроса
    {
        auto *item = new QListWidgetItem(listoutquery.value("name").toString()); //Создание переменной с QListWidget
        QVariant v;
        v.setValue(listoutquery.value("id").toInt()); //Запись ID каждого поля
        item->setData(Qt::UserRole, v);//Присваивание QListWidget ID
        ui->listWidget->addItem(item);//Добавление элемента в QListWidget
        item->data(Qt::UserRole);
    }
}

void MainWindow::on_SaveButton_clicked() //Функция сохранения по нажатию кнопки "Сохранить"
{
    name = ui->NameEdit->text();
    source = ui->SourceEdit->text();
    login = ui->LoginEdit->text();
    password = ui->PasswordEdit->text();
    note = ui->NoteEdit->text();
    tag = ui->TagEdit->text();

    QVariant v = ui->listWidget->currentItem()->data(Qt::UserRole); //Взятие ID выбранного элемента
    int id = v.value<int>();
    if (id == 0)
    {
        if (login !="" || password !="" || name !="")
        {
            QSqlQuery edquery;
            edquery.prepare("INSERT INTO passwords (login, password, source, name, notes, tag)"
                            "VALUES (? , ?, ?, ?, ?, ?)");
            edquery.addBindValue(login); //Вставка подготовленного значения в запрос
            edquery.addBindValue(password);
            edquery.addBindValue(source);
            edquery.addBindValue(name);
            edquery.addBindValue(note);
            edquery.addBindValue(tag);
            edquery.addBindValue(id);
            edquery.exec();//Выполнение запроса
            edquery.clear();//Очистка запроса
        }else QMessageBox::warning(0, "Ошибка", "Введите данные");
        int queryid;
        QSqlQuery newrecord;
        newrecord.exec("SELECT id FROM passwords WHERE id = (SELECT MAX(id) FROM passwords)");
        while (newrecord.next())
        {
            queryid = newrecord.value("id").toInt();
        }

        auto *item = ui->listWidget->currentItem(); //Создание переменной с QListWidget
        v.setValue(queryid);
        item->setData(Qt::UserRole, v);//Присваивание QListWidget ID
    }else if (login !="" || password !="" || name !="")
    {
        QSqlQuery edquery;
        edquery.prepare("UPDATE passwords SET login = ?, password = ?, source = ?, name = ?, notes = ?, tag = ?  WHERE id = ?");
        edquery.addBindValue(login); //Вставка подготовленного значения в запрос
        edquery.addBindValue(password);
        edquery.addBindValue(source);
        edquery.addBindValue(name);
        edquery.addBindValue(note);
        edquery.addBindValue(tag);
        edquery.addBindValue(id);
        edquery.exec();//Выполнение запроса
        edquery.clear();//Очистка запроса
    } else QMessageBox::warning(0, "Ошибка", "Введите данные");

    ui->statusbar->showMessage("Изменения сохранены");
    ui->listWidget->currentItem()->setText(name);
}

void MainWindow::on_CleanButton_clicked() //Функция очищения полей по нажатию кнопки "Очистить"
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

void MainWindow::on_CopySourceButton_clicked() //Функция копирования URL-источника в буфер обмена ОС
{
    source = ui->SourceEdit->text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(source);
}

void MainWindow::on_CopyLoginButton_clicked()//Функция копирования логина в буфер обмена ОС
{
    login = ui->LoginEdit->text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(login);
}

void MainWindow::on_CopyPasswordButton_clicked()//Функция копирования пароля в буфер обмена ОС
{
    password = ui->PasswordEdit->text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(password);
}

void MainWindow::on_DeleteButton_clicked()//Функция удаления записи из БД
{
    QVariant v = ui->listWidget->currentItem()->data(Qt::UserRole);
    int id = v.value<int>();

    QSqlQuery deletequery;
    deletequery.prepare("DELETE FROM passwords WHERE id = ?");
    deletequery.addBindValue(id);
    deletequery.exec();

    delete ui->listWidget->currentItem();
    on_CleanButton_clicked();
}

void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item) //Функция открытия записи по активации элемента в QListWidget
{
    QVariant v = ui->listWidget->currentItem()->data(Qt::UserRole);
    int id = v.value<int>();

    QSqlQuery outquery;
    outquery.prepare("SELECT * FROM passwords WHERE id = ?");
    outquery.addBindValue(id);
    outquery.exec();
    while (outquery.next())
    {
        ui->NameEdit->setText(outquery.value("name").toString());
        ui->SourceEdit->setText(outquery.value("source").toString());
        ui->LoginEdit->setText(outquery.value("login").toString());
        ui->PasswordEdit->setText(outquery.value("password").toString());
        ui->NoteEdit->setText(outquery.value("notes").toString());
        ui->TagEdit->setText(outquery.value("tag").toString());

        name = outquery.value("name").toString();
        source = outquery.value("source").toString();
        login = outquery.value("login").toString();
        password = outquery.value("password").toString();
        note = outquery.value("notes").toString();
        tag = outquery.value("tag").toString();
    }
}

void MainWindow::on_AddButton_clicked() //Функция добавления новой записи
{
    auto *item = new QListWidgetItem("Новая запись"); //Создание переменной с QListWidget
    QVariant v;
    v.setValue(0);
    item->setData(Qt::UserRole, v);//Присваивание QListWidget ID
    ui->listWidget->addItem(item);//Добавление элемента в QListWidget
    item->data(Qt::UserRole);

    on_CleanButton_clicked();
}

void MainWindow::on_ShowPasswordButton_clicked()//Функция отображения скрытого пароля
{
    if (ui->PasswordEdit->echoMode() == QLineEdit::Password)
    {
        ui->PasswordEdit->setEchoMode(QLineEdit::Normal);
        ui->ShowPasswordButton->setChecked(true);
    } else
    {
        ui->PasswordEdit->setEchoMode(QLineEdit::Password);
        ui->ShowPasswordButton->setChecked(false);
    }
}
