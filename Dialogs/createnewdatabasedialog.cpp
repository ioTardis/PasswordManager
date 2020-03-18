#include "createnewdatabasedialog.h"
#include "ui_createnewdatabasedialog.h"
#include "choosedatabasedialog.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

QString password1;
QString password2;
QString createPath;

CreateNewDatabaseDialog::CreateNewDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNewDatabaseDialog)
{
    ui->setupUi(this);

    main = new MainWindow();
    connect(this, SIGNAL(sendFile(QString)),
            main, SLOT(recieveMessage(QString))); //Связывание слота и сигнала

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
    createPath = QFileDialog::getSaveFileName(this, "Сохранить файл", "","*.txt");
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
            if (file.open(QIODevice::WriteOnly))
            {
                file.write("Доброе утро девачки\n");
                file.write("Записываем пароли девачки\n");
                file.close();
                emit sendFile(createPath);
                close();
            } else QMessageBox::warning(0,"Ошибка", "Ошибачка с сохранением?");
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
