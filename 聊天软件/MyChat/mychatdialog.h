#ifndef MYCHATDIALOG_H
#define MYCHATDIALOG_H

#include <QDialog>
#include<QVBoxLayout>
#include"useritem.h"
#include<QMenu>
#include<QCloseEvent>

namespace Ui {
class MyChatDialog;
}

class MyChatDialog : public QDialog
{
    Q_OBJECT
signals:
    void SIG_addFriend();
    void SIG_Close();

public:
    explicit MyChatDialog(QWidget *parent = 0);
    ~MyChatDialog();

    void closeEvent(QCloseEvent * event);

public slots:
    void slot_addFriend( UserItem* item );
    //设置ui成员属性
    void slot_setInfo( QString name , int iconid ,QString feeling);


private slots:
    void on_pb_menu_clicked();

    void slot_dealMenu(QAction* action);
private:
    Ui::MyChatDialog *ui;

    QVBoxLayout * m_layout;

    QMenu * m_menu;
};

#endif // MYCHATDIALOG_H
