#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void recieveMessage(QString getPath, QString getDBpass, int getAuth);

private slots:

    void on_SaveButton_clicked();

    QByteArray encodeData(QString DBinput);

    QByteArray decodeData(QByteArray DBentry);

    void on_CleanButton_clicked();

    void on_CopySourceButton_clicked();

    void on_CopyLoginButton_clicked();

    void on_CopyPasswordButton_clicked();

    void on_DeleteButton_clicked();

    void on_listWidget_itemActivated(QListWidgetItem *item);

    void updateQListWidget();

    void on_AddButton_clicked();

    void on_ShowPasswordButton_clicked();

    void on_SearchEdit_textChanged(const QString &arg1);

    void on_NewDatabaseAction_triggered();

    void on_ChangeDatabaseAction_triggered();

    void on_ExportDatabaseAction_triggered();

    void clearSettings();

    void on_ExitAction_triggered();

private:
    Ui::MainWindow *ui;
    QString id;
    QString path;
    QString name;
    QString source;
    QString login;
    QString password;
    QString note;
    QString tag;
};
#endif // MAINWINDOW_H
