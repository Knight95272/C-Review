#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

#include<QCloseEvent>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
signals:
    void SIG_LoginCommit( QString tel , QString password);
    void SIG_RegisterCommit( QString tel , QString password , QString name );
    void SIG_Close();
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();


    void closeEvent(QCloseEvent * event );
private slots:
    void on_pb_clear_clicked();

    void on_pb_commit_clicked();

    void on_pb_clear_register_clicked();

    void on_pb_commit_register_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
