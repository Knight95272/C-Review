#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT
//
signals:
    void SIG_SendChatMsg( int id , QString content);
public :
    explicit ChatDialog(QWidget *parent = 0);
    ~ChatDialog();
public slots:
    void slot_setInfo(int id, const QString &name);
    void slot_setChatMsg( QString content);
    void slot_setUserOffline();

private slots:
    void on_pb_send_clicked();

private:
    Ui::ChatDialog *ui;
    int m_id;
    QString m_name;
};

#endif // CHATDIALOG_H
