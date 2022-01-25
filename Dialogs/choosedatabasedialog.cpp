#include "choosedatabasedialog.h"
#include "ui_choosedatabasedialog.h"
#include "importdatabasedialog.h"
#include "createnewdatabasedialog.h"

//Window with option to choose to import DB/create a new DB

ChooseDatabaseDialog::ChooseDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDatabaseDialog){
    ui->setupUi(this);
}

ChooseDatabaseDialog::~ChooseDatabaseDialog() {
    delete ui;
}

void ChooseDatabaseDialog::on_NextButton_clicked() {
    if (ui->ExistDbRadioButton->isChecked()) {
        hide();
        ImportDatabaseDialog ImportDatabase;
        ImportDatabase.setModal(true);
        ImportDatabase.exec();
    }
    if (ui->NewDbRadioButton->isChecked()) {
        hide();
        CreateNewDatabaseDialog CreateNewDatabase;
        CreateNewDatabase.setModal(true);
        CreateNewDatabase.exec();
    }
}

void ChooseDatabaseDialog::on_ExitButton_clicked() {
    exit(0);
}
