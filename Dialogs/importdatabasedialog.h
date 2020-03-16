#ifndef IMPORTDATABASEDIALOG_H
#define IMPORTDATABASEDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class ImportDatabaseDialog;
}

class ImportDatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportDatabaseDialog(QWidget *parent = nullptr);
    ~ImportDatabaseDialog();

signals:
    void sendFile(QString fileNameSend2);

private slots:
    void on_ExitButton_clicked();

    void on_PathButton_clicked();

    void on_PathEdit_textChanged(const QString &arg1);

    void on_PasswordEdit_textChanged(const QString &arg1);

    void on_NextButton_clicked();

    void on_BackButton_clicked();

private:
    Ui::ImportDatabaseDialog *ui;
    MainWindow *main;

    QString password;
    QString importPath;
};

#endif // IMPORTDATABASEDIALOG_H
