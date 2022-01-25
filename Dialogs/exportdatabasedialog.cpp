#include "exportdatabasedialog.h"
#include "ui_exportdatabasedialog.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QtSql>

//Window for exporting an open database

ExportDatabaseDialog::ExportDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDatabaseDialog){
    ui->setupUi(this);
}

ExportDatabaseDialog::~ExportDatabaseDialog(){
    delete ui;
}

void ExportDatabaseDialog::on_PathEdit_textChanged(const QString &arg1){
    exportPath = ui->PathEdit->text();
}

void ExportDatabaseDialog::on_PathButton_clicked(){
    exportPath = QFileDialog::getSaveFileName(this, "Save file", "","*.db");
    if (exportPath != "") ui->PathEdit->setText(exportPath);
}

void ExportDatabaseDialog::on_exportPasswordEdit_textChanged(const QString &arg1) {
    QString check = ui->exportPasswordEdit->text();
    if (check !="") exportDBpassword = check;
}

void ExportDatabaseDialog::on_exportPasswordCheckEdit_textChanged(const QString &arg1)
{
    QString check = ui->exportPasswordCheckEdit->text();
    if (check !="") exportDBpasswordCheck = check;
}

void ExportDatabaseDialog::on_OKButton_clicked() {
    QFile file(exportPath);

    if (exportDBpassword == "" || exportDBpasswordCheck == "") QMessageBox::warning(0,"Error", "Enter the password");
    else if (exportDBpassword.size() != 16 ) QMessageBox::warning(0,"Error", "The password must contain 16 characters");
        else {
            if (exportDBpassword != exportDBpasswordCheck) QMessageBox::warning(0,"Error", "Passwords don't match");
            else if (exportPath !="") {
                QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
                db.setDatabaseName(exportPath);
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
                close();
            } else QMessageBox::warning(0,"Error", "Missing path");
        }
}

void ExportDatabaseDialog::on_ExitButton_clicked(){
    delete ui;
}

