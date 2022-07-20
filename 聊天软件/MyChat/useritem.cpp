#include "useritem.h"
#include "ui_useritem.h"

UserItem::UserItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItem)
{
    ui->setupUi(this);
}

UserItem::~UserItem()
{
    delete ui;
}

//鼠标双击用户  --> 发送信号
void UserItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_EMIT SIG_userItemClicked( m_id );
}
#include<QIcon>
#include<QBitmap>
//设置
void UserItem::slot_setInfo(int id, QString name, int state, int iconid, QString feeling)
{
    //设置变量
    m_id        = id;
    m_name      = name;
    m_state     = state;
    m_iconid    = iconid;
    m_feeling   = feeling;
     //设置ui
    ui->lb_name->setText( m_name );
    ui->lb_feeling->setText( m_feeling );
     //引入资源文件 以:起始
    QString path = QString(":/tx/%1.png").arg(m_iconid);
    //根据状态 不在为灰色
    //ui->pb_icon
    if( m_state )
    {
        ui->pb_icon->setIcon( QIcon( path ) );
    }else{
        QBitmap bmp;
        bmp.load( path );
        ui->pb_icon->setIcon( bmp ); // 添加位图是黑白的
    }
    this-> repaint(); // 立即重绘
}

//设置好友为离线
void UserItem::slot_setOffline()
{
    m_state = 0;

    QString path = QString(":/tx/%1.png").arg(m_iconid);
    QBitmap bmp;
    bmp.load( path );
    ui->pb_icon->setIcon( bmp ); // 添加位图是黑白的

    this-> repaint(); // 立即重绘
}

//点击头像 弹出聊天窗口
void UserItem::on_pb_icon_clicked()
{
    Q_EMIT SIG_userItemClicked( m_id );
}
