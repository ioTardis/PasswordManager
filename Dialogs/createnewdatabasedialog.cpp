#include "createnewdatabasedialog.h"
#include "ui_createnewdatabasedialog.h"
#include "choosedatabasedialog.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QtSql>

/*
 * Window for creating a new database. The user selects the path to the file and sets a 16-character password
 * that will be used to encrypt the information. Path and password transmitted to the main window using a signal sendInfo
*/

CreateNewDatabaseDialog::CreateNewDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNewDatabaseDialog) {
    ui->setupUi(this);

    MainWindow *main = new MainWindow();
    connect(this, SIGNAL(sendInfo(QString,QString,int)),
            main, SLOT(recieveMessage(QString,QString,int)));
}

CreateNewDatabaseDialog::~CreateNewDatabaseDialog() {
    delete ui;
}

void CreateNewDatabaseDialog::on_ExitButton_clicked() {
    exit(0);
}

void CreateNewDatabaseDialog::on_OpenPathButton_clicked() {
    createdbPath = QFileDialog::getSaveFileName(this, "Save file", "","*.db");
    if (createdbPath != "") ui->PathEdit->setText(createdbPath);
}

void CreateNewDatabaseDialog::on_PathEdit_textChanged(const QString) {
    createdbPath = ui->PathEdit->text();
}

void CreateNewDatabaseDialog::on_PasswordEdit_textChanged(const QString) {
    QString check = ui->PasswordEdit->text();
    if (check !="") createdbPassword = check;
}


void CreateNewDatabaseDialog::on_Password2Edit_textChanged(const QString) {
    QString check = ui->Password2Edit->text();
    if (check !="") createdbPasswordCheck = check;
}

void CreateNewDatabaseDialog::on_NextButton_clicked() { //Creating database
    QFile file(createdbPath);
    if (createdbPassword == "" || createdbPasswordCheck == "") QMessageBox::warning(0,"Error", "Enter the password");
    else if (createdbPassword.size() != 16 ) QMessageBox::warning(0,"Error", "The password must contain 16 characters");
        else {
            if (createdbPassword != createdbPasswordCheck) QMessageBox::warning(0,"Error", "Passwords don't match");
            else
                if (createdbPath !="") {
                    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
                    db.setDatabaseName(createdbPath);
                    db.open();

                    QSqlQuery query;
                    query.exec("CREATE TABLE passwords "
                               "(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                               "login VARCHAR NOT NULL, "
                               "password VARCHAR NOT NULL, "
                               "source VARCHAR, "
                               "name VARCHAR, "
                               "note VARCHAR, "
                               "tag VARCHAR)");
                    query.clear();

                    emit sendInfo(createdbPath,createdbPassword,1);
                    close();
                } else QMessageBox::warning(0,"Error", "Missing path");
        }
}

void CreateNewDatabaseDialog::on_BackButton_clicked() {
    hide();
    ChooseDatabaseDialog ChooseDatabase;
    ChooseDatabase.setModal(true);
    ChooseDatabase.exec();
}
