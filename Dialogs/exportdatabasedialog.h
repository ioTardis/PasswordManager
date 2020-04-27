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

private slots:
    void on_PathEdit_textChanged(const QString &arg1);

    void on_PathButton_clicked();

    void on_OKButton_clicked();

    void on_ExitButton_clicked();

private:
    Ui::ExportDatabaseDialog *ui;
};

#endif // EXPORTDATABASEDIALOG_H
