#include "chatdialog.h"
#include "ui_chatdialog.h"

ChatDialog::ChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}
//点击发送
#include<QTime>
void ChatDialog::on_pb_send_clicked()
{
    //取string  判断是不是 空
    QString content = ui->te_chat->toPlainText(); // 不带格式纯文本
    if( content.isEmpty() ) return;

    //取string 清空编辑
    content = ui->te_chat->toHtml(); // 附带文本格式
    ui->te_chat->clear();

    //浏览添加聊天  [我] 18:32:23 ....
    ui->tb_chat->append( QString("[我] %1")
                         .arg(QTime::currentTime().toString("hh:mm:ss")) ); //换行追加
    ui->tb_chat->append( content );
    //发送信号
    Q_EMIT SIG_SendChatMsg( m_id , content);
}

void ChatDialog::slot_setInfo(int id , const QString &name)
{

    m_id = id;
    m_name = name;

    //ui 窗口标题栏 写与谁的聊天
    setWindowTitle( QString("与[%1]的聊天").arg(name) );
}

//接收的数据 添加到界面
void ChatDialog::slot_setChatMsg(QString content)
{
    // [ name ] 18:46:34 ....
    ui->tb_chat->append( QString("[%1] %2").arg( m_name )
                         .arg(QTime::currentTime().toString("hh:mm:ss")) ); //换行追加
    ui->tb_chat->append( content );
}

//添加该人不在线
void ChatDialog::slot_setUserOffline()
{
    // [ name ] 18:46:34 ....
    ui->tb_chat->append( QString("[%1] %2 该用户不在线").arg( m_name )
                         .arg(QTime::currentTime().toString("hh:mm:ss")) ); //换行追加
}



