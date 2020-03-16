#include "exportdatabasedialog.h"
#include "ui_exportdatabasedialog.h"

ExportDatabaseDialog::ExportDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDatabaseDialog)
{
    ui->setupUi(this);
}

ExportDatabaseDialog::~ExportDatabaseDialog()
{
    delete ui;
}
