#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Dialogs/hellodialog.h"
#include "Dialogs/opendatabasedialog.h"
#include "Dialogs/importdatabasedialog.h"
#include "Dialogs/createnewdatabasedialog.h"
#include "Dialogs/exportdatabasedialog.h"
#include "Qt-AES/qaesencryption.h"

#include <QCryptographicHash>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QClipboard>
#include <QtSql>

/*
 * The main window of the program. Receives a signal from windows with a file path, encryption password, and authentication status.
 * Uses an open database connection to read and write information.
*/

QString userPass;
int auth = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Reading the settings file
    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.beginGroup( "Database" );
    path = settings.value( "Path", "" ).toString();
    settings.endGroup();
    if (path != "" && auth == 0) {
        auth = 1;
        opendatabasedialog opendatabasedialog;
        opendatabasedialog.setModal(true);
        opendatabasedialog.exec();
    }

    if (auth == 0){  //Showing Hello dialog
        HelloDialog hellodialog;
        hellodialog.setModal(true);
        hellodialog.exec();
    }

    if (auth == 1){
        ui->setupUi(this);
        updateQListWidget();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::recieveMessage(QString getPath, QString getDBpass, int getAuth) {  //Slot for recieving the signal from windows
    path = getPath;
    auth = getAuth;
    userPass = getDBpass;

    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.beginGroup("Database");
    settings.setValue("Path", path);
    settings.endGroup();
}

void MainWindow::updateQListWidget() {  //Displaying an entry list
    QSqlQuery listoutquery;
    listoutquery.exec("SELECT name, id FROM passwords");
    while(listoutquery.next()){  //Iterating through the query results
        QString listItem = decodeData(QByteArray::fromBase64(listoutquery.value("name").toByteArray()));
        listItem.chop(8);
        auto *item = new QListWidgetItem(listItem); //Creating a QListWidget variable
        QVariant v;
        v.setValue(listoutquery.value("id").toInt()); //Record the ID of each field
        item->setData(Qt::UserRole, v);//Assigning ID to QListWidget
        ui->listWidget->addItem(item);//Adding an item to QListWidget
        item->data(Qt::UserRole);
    }
}

QByteArray MainWindow::encodeData(QString DBinput) {  //Data encryption using a user-defined password
    QAESEncryption passEncryption(QAESEncryption::AES_128, QAESEncryption::ECB);
    QString input = DBinput.simplified().remove(' ');

    QByteArray encodedText = passEncryption.encode(input.toUtf8(), userPass.toUtf8());
    return encodedText.toBase64();
}

QByteArray MainWindow::decodeData(QByteArray DBentry) {  //Data decryption using a user-defined password
    QAESEncryption passEncryption(QAESEncryption::AES_128, QAESEncryption::ECB);

    QByteArray decodedText = passEncryption.decode(DBentry, userPass.toUtf8());
    return decodedText;
}

void MainWindow::on_SaveButton_clicked() {  //Saving information to the database
    name = ui->NameEdit->text();
    source = ui->SourceEdit->text();
    login = ui->LoginEdit->text();
    password = ui->PasswordEdit->text();
    note = ui->NoteEdit->text();
    tag = ui->TagEdit->text();

    QVariant v = ui->listWidget->currentItem()->data(Qt::UserRole); //Taking an ID of selected element
    int id = v.value<int>();
    if (id == 0){
        if (login !="" || password !="" || name !="") {
            QSqlQuery edquery;
            edquery.prepare("INSERT INTO passwords (login, password, source, name, note, tag)"
                            "VALUES (? , ?, ?, ?, ?, ?)");
            edquery.addBindValue(encodeData(login)); //Input information to query
            edquery.addBindValue(encodeData(password));
            edquery.addBindValue(source);
            edquery.addBindValue(encodeData(name));
            edquery.addBindValue(encodeData(note));
            edquery.addBindValue(encodeData(tag));
            edquery.exec();//Query execution
            edquery.clear();

            ui->listWidget->currentItem()->setText(name);
            ui->statusbar->showMessage("Changes saved");
        } else QMessageBox::warning(0, "Error", "Enter the data");

        int queryid;
        QSqlQuery newrecord;
        newrecord.exec("SELECT id FROM passwords WHERE id = (SELECT MAX(id) FROM passwords)");
        while (newrecord.next()) {
            queryid = newrecord.value("id").toInt();
        }

        auto *item = ui->listWidget->currentItem();
        v.setValue(queryid);
        item->setData(Qt::UserRole, v);
    } else if (login !="" || password !="" || name !="") {
        QSqlQuery edquery;
        edquery.prepare("UPDATE passwords SET login = ?, password = ?, source = ?, name = ?, note = ?, tag = ?  WHERE id = ?");
        edquery.addBindValue(encodeData(login));
        edquery.addBindValue(encodeData(password));
        edquery.addBindValue(source);
        edquery.addBindValue(encodeData(name));
        edquery.addBindValue(encodeData(note));
        edquery.addBindValue(encodeData(tag));
        edquery.addBindValue(id);
        edquery.exec();
        edquery.clear();

        ui->listWidget->currentItem()->setText(name);
        ui->statusbar->showMessage("Changes saved");
    } else QMessageBox::warning(0, "Error", "Enter the data");
}

void MainWindow::on_CleanButton_clicked() {  //Emptying fields by clicking the "Clear" button
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

void MainWindow::on_CopySourceButton_clicked() {
    source = ui->SourceEdit->text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(source);
}

void MainWindow::on_CopyLoginButton_clicked() {
    login = ui->LoginEdit->text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(login);
}

void MainWindow::on_CopyPasswordButton_clicked() {
    password = ui->PasswordEdit->text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(password);
}

void MainWindow::on_DeleteButton_clicked() {
    QVariant v = ui->listWidget->currentItem()->data(Qt::UserRole);
    int id = v.value<int>();

    QSqlQuery deletequery;
    deletequery.prepare("DELETE FROM passwords WHERE id = ?");
    deletequery.addBindValue(id);
    deletequery.exec();

    delete ui->listWidget->currentItem();
    on_CleanButton_clicked();
}

void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item) {  //Open entry
    on_CleanButton_clicked();
    QVariant v = ui->listWidget->currentItem()->data(Qt::UserRole);
    int id = v.value<int>();

    QSqlQuery outquery;
    outquery.prepare("SELECT * FROM passwords WHERE id = ?");
    outquery.addBindValue(id);
    outquery.exec();
    while (outquery.next()){

        login = decodeData(QByteArray::fromBase64(outquery.value("login").toByteArray()));
        password = decodeData(QByteArray::fromBase64(outquery.value("password").toByteArray()));
        name = decodeData(QByteArray::fromBase64(outquery.value("name").toByteArray()));
        note = decodeData(QByteArray::fromBase64(outquery.value("note").toByteArray()));
        tag = decodeData(QByteArray::fromBase64(outquery.value("tag").toByteArray()));
        source = outquery.value("source").toString();

        ui->NameEdit->setText(name);
        ui->SourceEdit->setText(source);
        ui->LoginEdit->setText(login);
        ui->PasswordEdit->setText(password);
        ui->NoteEdit->setText(note);
        ui->TagEdit->setText(tag);
    }
}

void MainWindow::on_AddButton_clicked() {
    QList<QListWidgetItem *> list = ui->listWidget->findItems("New entry", Qt::MatchExactly);
    if (list.count() > 0) {
        QMessageBox::warning(0, "Error", "The new entry already exists!");
    } else {
        auto *item = new QListWidgetItem("New entry");
        QVariant v;
        v.setValue(0);
        item->setData(Qt::UserRole, v);
        ui->listWidget->addItem(item);
        item->data(Qt::UserRole);
    }

    on_CleanButton_clicked();
}

void MainWindow::on_ShowPasswordButton_clicked() {
    if (ui->PasswordEdit->echoMode() == QLineEdit::Password) {
        ui->PasswordEdit->setEchoMode(QLineEdit::Normal);
        ui->ShowPasswordButton->setChecked(true);
    } else {
        ui->PasswordEdit->setEchoMode(QLineEdit::Password);
        ui->ShowPasswordButton->setChecked(false);
    }
}

void MainWindow::on_SearchEdit_textChanged(const QString &arg1) {
    QString searchstring = ui->SearchEdit->text();
    if (searchstring == "") {
        ui->listWidget->clear();
        updateQListWidget();
    } else {
        searchstring = encodeData(searchstring);
        searchstring = searchstring + "%";
        ui->listWidget->clear();
        QSqlQuery search;
        search.prepare("SELECT * FROM passwords WHERE lower(name) LIKE lower(?)");
        search.addBindValue(searchstring);
        search.exec();
        while (search.next()){
            auto *item = new QListWidgetItem(decodeData(QByteArray::fromBase64(search.value("name").toByteArray())));
            QVariant v;
            v.setValue(search.value("id").toInt());
            item->setData(Qt::UserRole, v);
            ui->listWidget->addItem(item);
            item->data(Qt::UserRole);
        }
    }
}

void MainWindow::on_NewDatabaseAction_triggered() {
    clearSettings();
    ui->listWidget->clear();

    hide();
    CreateNewDatabaseDialog CreateNewDatabase;
    CreateNewDatabase.setModal(true);
    CreateNewDatabase.exec();
    show();
    updateQListWidget();
}

void MainWindow::on_ChangeDatabaseAction_triggered() {
    clearSettings();
    ui->listWidget->clear();

    hide();
    ImportDatabaseDialog ImportDatabase;
    ImportDatabase.setModal(true);
    ImportDatabase.exec();
    show();
    updateQListWidget();
}

void MainWindow::on_ExportDatabaseAction_triggered() {
    ExportDatabaseDialog ExportDatabase;
    ExportDatabase.setModal(true);
    ExportDatabase.exec();
}

void MainWindow::clearSettings() {
    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.beginGroup("Database");
    settings.setValue("Path", "");
    settings.endGroup();
}

void MainWindow::on_ExitAction_triggered() {
    delete ui;
    exit(0);
}

