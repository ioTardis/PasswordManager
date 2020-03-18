#ifndef CREATENEWDATABASEDIALOG_H
#define CREATENEWDATABASEDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class CreateNewDatabaseDialog;
}

class CreateNewDatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateNewDatabaseDialog(QWidget *parent = nullptr);
    ~CreateNewDatabaseDialog();

signals:
    void sendFile(QString fileNameSend);

private slots:
    void on_ExitButton_clicked();

    void on_OpenPathButton_clicked();

    void on_PathEdit_textChanged(const QString);

    void on_PasswordEdit_textChanged(const QString);

    void on_Password2Edit_textChanged(const QString);

    void on_NextButton_clicked();

    void on_BackButton_clicked();

private:
    Ui::CreateNewDatabaseDialog *ui;
    MainWindow *main;
};

#endif // CREATENEWDATABASEDIALOG_H
