#include "mychatdialog.h"
#include "ui_mychatdialog.h"

#include<QMessageBox>

MyChatDialog::MyChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyChatDialog)
{
    ui->setupUi(this);

    setWindowTitle( "通讯软件v1.0");

    m_layout = new QVBoxLayout; // 垂直布局的层
    m_layout->setContentsMargins( 0 , 0, 0 ,0 ); //左下右上距离外边框多远
    m_layout->setSpacing( 3 );//每个控件彼此的距离

    ui->wdg_lst->setLayout( m_layout );

    m_menu = new QMenu(this); //指定父控件, 父控件负责子控件回收

    //添加菜单项
    m_menu->addAction( "添加好友");
    m_menu->addAction( "系统设置");
    //菜单项 的处理函数
    connect( m_menu , SIGNAL(triggered(QAction*))
             , this , SLOT(slot_dealMenu(QAction*)) );
}

MyChatDialog::~MyChatDialog()
{
    delete ui;
}

//关闭事件
void MyChatDialog::closeEvent(QCloseEvent *event)
{
    event -> ignore(); // 忽略事件 在控制类控制

    if( QMessageBox::question( this , "退出提示" , "是否要退出?" )
            == QMessageBox::Yes )
    {
         Q_EMIT SIG_Close();
    }
}

void MyChatDialog::slot_addFriend( UserItem* item )
{
    m_layout->addWidget( item );
}

#include<QIcon>
void MyChatDialog::slot_setInfo(QString name, int iconid, QString feeling)
{
    //设置ui
    ui->lb_name->setText( name );
    ui->le_feeling->setText(feeling);
    ui->pb_icon->setIcon( QIcon( QString(":/tx/%1.png").arg( iconid ) ));

}

//点击 弹出菜单
void MyChatDialog::on_pb_menu_clicked()
{
    //显示菜单 在哪显示 按照鼠标位置
    QPoint p = QCursor::pos();
    QSize size = m_menu->sizeHint(); //菜单的绝对高度 -- 所有的项都弹出之后的高

    m_menu->exec( QPoint( p.x() , p.y() - size.height() )  );
}
//处理菜单的函数
void MyChatDialog::slot_dealMenu(QAction *action)
{
    if( action->text() == "添加好友" )
    {
        Q_EMIT SIG_addFriend();
    }else if( action->text() == "系统设置" )
    {
        //
    }
}
