#ifndef CHOOSEDATABASEDIALOG_H
#define CHOOSEDATABASEDIALOG_H

#include <QDialog>

namespace Ui {
class ChooseDatabaseDialog;
}

class ChooseDatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseDatabaseDialog(QWidget *parent = nullptr);
    ~ChooseDatabaseDialog();

private slots:
    void on_NextButton_clicked();

    void on_ExitButton_clicked();

private:
    Ui::ChooseDatabaseDialog *ui;
};

#endif // CHOOSEDATABASEDIALOG_H
