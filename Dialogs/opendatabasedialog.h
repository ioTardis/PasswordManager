#ifndef OPENDATABASEDIALOG_H
#define OPENDATABASEDIALOG_H

#include <QDialog>

namespace Ui {
class opendatabasedialog;
}

class opendatabasedialog : public QDialog
{
    Q_OBJECT

public:
    explicit opendatabasedialog(QWidget *parent = nullptr);
    ~opendatabasedialog();

signals:
    void sendPath(QString DBPath, int auth);

private slots:

    void on_AnotherDBButton_clicked();

    void on_OKButton_clicked();

    void on_ExitButton_clicked();

private:
    Ui::opendatabasedialog *ui;
};

#endif // OPENDATABASEDIALOG_H
