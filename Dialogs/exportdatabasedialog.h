#ifndef EXPORTDATABASEDIALOG_H
#define EXPORTDATABASEDIALOG_H

#include <QDialog>

namespace Ui {
class ExportDatabaseDialog;
}

class ExportDatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDatabaseDialog(QWidget *parent = nullptr);
    ~ExportDatabaseDialog();

private:
    Ui::ExportDatabaseDialog *ui;
};

#endif // EXPORTDATABASEDIALOG_H
