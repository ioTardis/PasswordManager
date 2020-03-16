#include "hellodialog.h"
#include "ui_hellodialog.h"
#include "choosedatabasedialog.h"

HelloDialog::HelloDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelloDialog)
{
    ui->setupUi(this);
}

HelloDialog::~HelloDialog()
{
    delete ui;
}

void HelloDialog::on_ExitButton_clicked()
{
    exit(0);
}

void HelloDialog::on_NextButton_clicked()
{
    hide();
    ChooseDatabaseDialog ChooseDatabase;
    ChooseDatabase.setModal(true);
    ChooseDatabase.exec();
}
