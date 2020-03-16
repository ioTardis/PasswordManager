#ifndef HELLODIALOG_H
#define HELLODIALOG_H

#include <QDialog>

namespace Ui {
class HelloDialog;
}

class HelloDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelloDialog(QWidget *parent = nullptr);
    ~HelloDialog();

private slots:

    void on_ExitButton_clicked();

    void on_NextButton_clicked();

private:
    Ui::HelloDialog *ui;
};

#endif // HELLODIALOG_H
