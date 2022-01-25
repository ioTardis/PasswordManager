#ifndef OPENDATABASEDIALOG_H
#define OPENDATABASEDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class opendatabasedialog;
}

class opendatabasedialog : public QDialog {
    Q_OBJECT

public:
    explicit opendatabasedialog(QWidget *parent = nullptr);
    ~opendatabasedialog();

signals:
    void sendInfo(QString DBpath, QString DBpass, int auth);

private slots:

    void on_AnotherDBButton_clicked();

    void on_OKButton_clicked();

    void on_ExitButton_clicked();

    void on_openPasswordEdit_textChanged(const QString &arg1);

private:
    Ui::opendatabasedialog *ui;

    QString openPath;
    QString openPassword;
};

#endif // OPENDATABASEDIALOG_H
