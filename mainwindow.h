#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_9_clicked();

    void on_NameEdit_textChanged(const QString);

    void on_SourceEdit_textChanged(const QString);

    void on_LoginEdit_textChanged(const QString);

    void on_NoteEdit_textChanged(const QString);

    void on_SaveButton_clicked();

    void on_CleanButton_clicked();

    void on_PasswordEdit_textChanged(const QString);

    void on_CopySourceButton_clicked();

    void on_CopyLoginButton_clicked();

    void on_CopyPasswordButton_clicked();

    void on_TagEdit_textChanged(const QString);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
