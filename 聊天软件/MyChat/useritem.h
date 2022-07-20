#ifndef USERITEM_H
#define USERITEM_H

#include <QWidget>

#include<QMouseEvent>

namespace Ui {
class UserItem;
}

class UserItem : public QWidget
{
    Q_OBJECT
signals:
    void SIG_userItemClicked( int id );
public:
    explicit UserItem(QWidget *parent = 0);
    ~UserItem();

    void mouseDoubleClickEvent(QMouseEvent *event);

public slots:
    void slot_setInfo( int id , QString name , int state = 1
                       ,int iconid = 1 , QString feeling ="比较懒,啥也没写");

    void slot_setOffline();
private:
    Ui::UserItem *ui;
public:
    int m_id;
    QString m_name;
    int m_state;
    int m_iconid;
    QString m_feeling;
private slots:
    void on_pb_icon_clicked();
};

#endif // USERITEM_H
