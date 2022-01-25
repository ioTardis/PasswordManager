#include "opendatabasedialog.h"
#include "ui_opendatabasedialog.h"
#include "choosedatabasedialog.h"
#include "Qt-AES/qaesencryption.h"

#include <QCryptographicHash>
#include <QSettings>
#include <QFile>
#include <QMessageBox>
#include <QtSql>

/*
 * The window that opens if there is a path to the last opened database in the settings file.
 * Program reads the path and ask for password for decryption the information.
 * Path and password transmitted to the main window using a signal sendInfo
*/

opendatabasedialog::opendatabasedialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::opendatabasedialog){
    ui->setupUi(this);

    //Reading the settings file
    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.beginGroup( "Database" );
    openPath = settings.value( "Path", "" ).toString();
    settings.endGroup();

    ui->Path->setText(openPath);

    MainWindow *main = new MainWindow();
    connect(this, SIGNAL(sendInfo(QString,QString,int)),
            main, SLOT(recieveMessage(QString,QString,int)));
}

opendatabasedialog::~opendatabasedialog() {
    delete ui;
}

void opendatabasedialog::on_openPasswordEdit_textChanged(const QString &arg1) {
    QString check = ui->openPasswordEdit->text();
    if (check !="") openPassword = check;
}

void opendatabasedialog::on_AnotherDBButton_clicked() {
    hide();
    ChooseDatabaseDialog ChooseDatabase;
    ChooseDatabase.setModal(true);
    ChooseDatabase.exec();
}

void opendatabasedialog::on_OKButton_clicked() {
    QFile file(openPath);

    if (openPassword !="") {
        QFile file(openPath);
        if (openPath !="") {
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(openPath);
            db.open();
        } else QMessageBox::warning(0,"Error", "File does not exist");
        emit sendInfo(openPath,openPassword,1);
        close();
    } else QMessageBox::warning(0,"Error", "Enter the password");
}

void opendatabasedialog::on_ExitButton_clicked() {
    delete ui;
    exit(0);
}

