#include "ckernel.h"
#include"TcpClientMediator.h"
#include"qDebug"
#include"QMessageBox"

//设置协议映射关系

#define NetPackFunMap( a )  m_NetProtocolMap[ a - _DEF_PROTOCOL_BASE ]

void CKernel::setProtocolMap()
{

    memset( m_NetProtocolMap  , 0 , sizeof(m_NetProtocolMap) );

//    m_NetProtocolMap[ _DEF_PACK_REGISTER_RS - _DEF_PROTOCOL_BASE ]
//            = &CKernel::slot_registerRs;
//    m_NetProtocolMap[ _DEF_PACK_LOGIN_RS - _DEF_PROTOCOL_BASE ]
//            = &CKernel::slot_loginRs;

    NetPackFunMap(_DEF_PACK_REGISTER_RS)    = &CKernel::slot_registerRs;
    NetPackFunMap(_DEF_PACK_LOGIN_RS)       = &CKernel::slot_loginRs;
    NetPackFunMap(_DEF_PACK_FRIEND_INFO)    = &CKernel::slot_FriendInfoRq;
    NetPackFunMap(_DEF_PACK_CHAT_RQ)        = &CKernel::slot_ChatRq;
    NetPackFunMap(_DEF_PACK_CHAT_RS)        = &CKernel::slot_ChatRs;

    NetPackFunMap(_DEF_PACK_ADDFRIEND_RQ)   = &CKernel::slot_AddFriendRq;
    NetPackFunMap(_DEF_PACK_ADDFRIEND_RS)   = &CKernel::slot_AddFriendRs;
    NetPackFunMap(_DEF_PACK_OFFLINE_RQ)     = &CKernel::slot_OfflineRq;
}

CKernel::CKernel(QObject *parent) : QObject(parent)
  ,m_id(0),m_state(0),m_iconid(0)
{
    //构造先来定义协议映射关系
    setProtocolMap();

    m_tcpClient = new TcpClientMediator;

    connect( m_tcpClient , SIGNAL( SIG_ReadyData(long,char*,int)) ,
             this , SLOT(slot_dealData(long,char*,int)) );

    if( !m_tcpClient->OpenNet() )
    {
        qDebug() << "连接服务器失败" ;
        delete m_tcpClient;
        exit(0);
    }

//    STRU_LOGIN_RQ rq;

//    m_tcpClient->SendData( 0 , (char*)&rq , sizeof(rq) );

    m_loginDialog = new LoginDialog;
    connect( m_loginDialog , SIGNAL( SIG_LoginCommit(QString,QString))
             ,this , SLOT(slot_LoginCommit(QString,QString)) );
    connect( m_loginDialog , SIGNAL( SIG_RegisterCommit(QString,QString,QString))
             ,this , SLOT(slot_RegisterCommit(QString,QString,QString)) );

    connect( m_loginDialog , SIGNAL(SIG_Close())
             , this , SLOT(DestroyInstance()) );

    m_loginDialog->showNormal();

    m_mainWnd = new MyChatDialog;
    connect( m_mainWnd , SIGNAL(SIG_addFriend())
             ,this , SLOT(slot_addFriend()) );

    connect( m_mainWnd , SIGNAL(SIG_Close())
             ,this , SLOT( slot_offline() ) );

//    for( int i = 0 ; i< 5 ;++i)
//    {
//        UserItem * item = new UserItem;
//        item->slot_setInfo( i+1 , QString("用户%1").arg(i+1)
//                            ,1, i+1 );
//        m_mainWnd->slot_addFriend( item );
//    }
//    for( int i = 5 ; i< 10 ;++i)
//    {
//        UserItem * item = new UserItem;
//        item->slot_setInfo( i+1 , QString("用户%1").arg(i+1)
//                            ,0, i+1 );
//        m_mainWnd->slot_addFriend( item );
//    }

//    m_mainWnd->show();
}


void CKernel::DestroyInstance()
{
    qDebug() << "DestroyInstance";

    if( m_loginDialog )
    {
        m_loginDialog->hide();
        delete m_loginDialog; m_loginDialog = NULL;
    }
    if( m_mainWnd )
    {
        m_mainWnd->hide();
        delete m_mainWnd; m_mainWnd = NULL;
    }

    //所有聊天窗口回收
    for( auto ite = m_mapIDToChatDialog.begin();
            ite!= m_mapIDToChatDialog.end();  )
    {
        ChatDialog *chat = *ite;
        chat->close();
        ite = m_mapIDToChatDialog.erase( ite );
        delete chat;
    }

    if( m_tcpClient )
    {
        m_tcpClient->CloseNet();
        delete m_tcpClient; m_tcpClient = NULL;
    }
    exit(0);
}

void CKernel::slot_dealData( long lSendIP , char* buf , int nlen )
{
    qDebug()<< __func__;
    //服务器发送的数据都会走到这里
    int type = *(int*)buf;
//    switch(type)
//    {
//        case _DEF_PACK_LOGIN_RS:
//        break;
//        //....
//    }

    //每一个协议头都会对应一个处理函数  映射 --> 数组
    //协议映射 表
    if( type >= _DEF_PROTOCOL_BASE &&
            type < _DEF_PROTOCOL_BASE + _DEF_PROTOCOL_COUNT )
    {//在映射数组范围内
//        PFUN pf = m_NetProtocolMap[ type - _DEF_PROTOCOL_BASE ];
        PFUN pf = NetPackFunMap( type );
        //typedef void (CKernel::*PFUN)( char* buf , int nlen );
        if( pf )
        {
           (this->*pf)( buf , nlen);
        }
    }
    delete [] buf;
}


//登录回复
void CKernel::slot_loginRs(char* buf , int nlen)
{
    qDebug()<<__func__;
    STRU_LOGIN_RS * rs = ( STRU_LOGIN_RS * )buf;
    switch( rs->result )
    {
        case user_not_exist:
            QMessageBox::about( this->m_loginDialog , "提示",
                                "登录失败,用户不存在");
        break;
        case password_error:
            QMessageBox::about( this->m_loginDialog , "提示",
                            "登录失败,密码错误");
        break;
        case login_success:
//            QMessageBox::about( this->m_loginDialog , "提示",
//                            "登录成功");
            // 页面跳转 写入id
        {
            m_loginDialog->hide();
            m_mainWnd->showNormal();
            //写入id
            m_id = rs->userid;
        }
        break;
        default:break;
    }
}

//注册回复
void CKernel::slot_registerRs(char* buf , int nlen)
{
    qDebug()<<__func__;
    STRU_REGISTER_RS * rs = ( STRU_REGISTER_RS * )buf;
    switch( rs->result )
    {
        case user_is_exist:
            QMessageBox::about( this->m_loginDialog , "提示",
                                "注册失败,用户已经存在");
        break;
        case register_success:
            QMessageBox::about( this->m_loginDialog , "提示",
                            "注册成功");
        break;
        default:break;
    }
}

//好友信息请求
void CKernel::slot_FriendInfoRq(char* buf , int nlen)
{
    //拆包
    STRU_FRIEND_INFO *info =(STRU_FRIEND_INFO *)buf;

    QString tmpName = GB2312ToUtf8(info->name);
    QString tmpFeeling = GB2312ToUtf8(info->feeling );

    //看是不是自己  看id 是不是自己  如果自己处理完是要return
    if( m_id == info->userid )
    {
        //更新界面
        m_mainWnd->slot_setInfo( tmpName , info->iconid , tmpFeeling);
        //更新成员
        m_name = tmpName;
        m_iconid = info->iconid;
        m_state = info->state;
        m_feeling = tmpFeeling;
        return;
    }
    //看之前窗口上有没有   窗口有一个映射关系 id -> UserItem
    if( m_mapIDToUserItem.find( info->userid ) == m_mapIDToUserItem.end() )
    {//没有 添加到控件上 , 添加到映射上
        UserItem * item = new UserItem;
        item->slot_setInfo( info->userid , tmpName ,
                            info->state ,info->iconid , tmpFeeling );
        // connect
        connect( item , SIGNAL(SIG_userItemClicked(int)) ,
                 this , SLOT( slot_userItemClicked(int)) );

        // 创建聊天创建
        ChatDialog * chat = new ChatDialog;
        chat->slot_setInfo( info->userid , tmpName );
        //  聊天窗口 connect
        connect( chat , SIGNAL(SIG_SendChatMsg(int,QString)) ,
                 this , SLOT( slot_SendChatMsg(int,QString)) );
        //connect()
        m_mapIDToChatDialog[  info->userid ] = chat;

        m_mainWnd->slot_addFriend( item );
        m_mapIDToUserItem[ info->userid ] = item;
    }else{
    //有 更新 查看如果以前是离线, 现在是上线的 , 就提示
        UserItem * item =  m_mapIDToUserItem[ info->userid ];
        if( item && item->m_state == 0 && info->state == 1)
        {
            //表示这个人上线
//            QMessageBox::about( m_mainWnd , "上线提示" ,
//                                QString("用户[%1]上线了").arg( tmpName ) );
            qDebug()<< QString("用户[%1]上线了").arg( tmpName );

        }
        item->slot_setInfo( info->userid , tmpName ,
                            info->state ,info->iconid , tmpFeeling );
    }
}

//聊天的请求
void CKernel::slot_ChatRq(char *buf, int nlen)
{
    //拆包
    STRU_CHAT_RQ * rq = (STRU_CHAT_RQ *)buf;
    //取内容 id 和聊天信息 根据id 得到窗口 , 粘贴聊天信息
    if( m_mapIDToChatDialog.count( rq->userid ) > 0 )
    {
        ChatDialog * chat =  m_mapIDToChatDialog[rq->userid];
        chat->slot_setChatMsg( QString::fromStdString( rq->content ) );
        chat->show();
    }
}

//聊天的回复
void CKernel::slot_ChatRs(char *buf, int nlen)
{
    //拆包
    STRU_CHAT_RS * rq = (STRU_CHAT_RS *)buf;
    //取内容 id 和聊天信息 根据id 得到窗口 , 显示该人不在线
    if( m_mapIDToChatDialog.count( rq->friendid ) > 0 )
    {
        ChatDialog * chat =  m_mapIDToChatDialog[rq->friendid];
        chat->slot_setUserOffline();
    }
}

//添加好友请求
void CKernel::slot_AddFriendRq(char* buf , int nlen)
{
    //QMessageBox::question  Yes No

    //拆包
    STRU_ADD_FRIEND_RQ * rq = (STRU_ADD_FRIEND_RQ *) buf;

    STRU_ADD_FRIEND_RS rs;
    //弹窗  选择 yes no
    if( QMessageBox::question(m_mainWnd , "添加好友" ,
    QString("用户[%1]请求添加你为好友 , 是否同意?").arg(rq->userName))
            == QMessageBox::Yes )
    {
        rs.result = add_success;
    }else
    {
        rs.result = user_refuse;
    }
    strcpy( rs.friendName , rq->friendName );
    rs.friendid = m_id;
    rs.userid = rq->userid ;
    //返回结果
    m_tcpClient->SendData( 0 , (char*)&rs , sizeof(rs));

}

//添加好友回复
void CKernel::slot_AddFriendRs(char* buf , int nlen)
{
    STRU_ADD_FRIEND_RS * rs = (STRU_ADD_FRIEND_RS * )buf;
    QString strAddName = GB2312ToUtf8( rs->friendName );
    switch( rs ->result )
    {
        case no_this_user:
            QMessageBox::about(  m_mainWnd , "提示"
                         ,QString("没有用户[%1],添加好友失败").arg(strAddName) );
        break;
        case user_offline:
            QMessageBox::about( m_mainWnd , "提示"
                         ,QString("用户[%1]不在线,添加好友失败").arg(strAddName) );
        break;
        case add_success:
            QMessageBox::about( m_mainWnd , "提示"
                         ,QString("添加用户[%1]为好友成功").arg(strAddName) );
        break;
        case user_refuse:
            QMessageBox::about( m_mainWnd , "提示"
                         ,QString("用户[%1]拒绝添加好友").arg(strAddName) );
        break;
    }
}

//离线处理
void CKernel::slot_OfflineRq(char *buf, int nlen)
{
    //拆包
    STRU_OFFLINE * rq = (STRU_OFFLINE *)buf;
    //根据id 获取 UserItem 然后设置离线
    if( m_mapIDToUserItem.count(rq->userid) > 0 )
    {
        UserItem * item = m_mapIDToUserItem[rq->userid];
        item->slot_setOffline();
    }
}

//提交登录
void CKernel::slot_LoginCommit( QString tel , QString password)
{
    //内容取出来封成包发送
    std::string strTel = tel.toStdString();
    std::string strPass = password.toStdString();

    STRU_LOGIN_RQ rq;
    strcpy( rq.tel , strTel.c_str() );
    strcpy( rq.password , strPass.c_str() );

    m_tcpClient ->SendData( 0 , (char*)&rq , sizeof(rq));
}
//提交注册
void CKernel::slot_RegisterCommit( QString tel , QString password , QString name )
{
    //内容取出来封成包发送
    std::string strTel = tel.toStdString();
    std::string strPass = password.toStdString();
    std::string strName = name.toStdString();

    //添加对于 utf8 到 gb2312的转换


    STRU_REGISTER_RQ rq;
    strcpy( rq.tel , strTel.c_str() );
    strcpy( rq.password , strPass.c_str() );
    //strcpy( rq.name , strName.c_str() );
    Utf8ToGB2312(  rq.name  , sizeof(rq.name) , name  );

    m_tcpClient ->SendData( 0 , (char*)&rq , sizeof(rq));
}

//用户被点击, 弹出聊天窗口
void CKernel::slot_userItemClicked(int id)
{
    //根据id 去map中查找
    if( m_mapIDToChatDialog.find( id ) != m_mapIDToChatDialog.end() )
    {
        ChatDialog * chat =  m_mapIDToChatDialog[id];
        chat->showNormal();
    }
}

//用户发送聊天
void CKernel::slot_SendChatMsg( int id , QString content)
{
    //拿相应的内容 填充到结构体
    STRU_CHAT_RQ rq;
    //发送的聊天内容 , 不需要转码, 原因是两个客户端使用 都是utf8
    rq.userid = m_id;
    rq.friendid = id;

    //兼容中文
    std::string strContent = content.toStdString();
    strcpy( rq.content , strContent.c_str() );

    m_tcpClient->SendData( 0 , (char*)&rq , sizeof(rq));
}

#include<QInputDialog>
//添加好友槽函数
void CKernel::slot_addFriend()
{
    //qDebug() << __func__;
    //输入对方名字  QInputDialog 输入的对话框
    QString strName = QInputDialog::getText( m_mainWnd , "添加好友"
                                             ,"输入好友名字");
    //加校验
    if( strName.length() > 20 )
    {
        QMessageBox::about( m_mainWnd , "提示" , "输入名字过长");
        return;
    }
    //判断 如果是自己 不可以
    if( m_name == strName )
    {
        QMessageBox::about( m_mainWnd , "提示" , "不可以添加自己为好友");
        return;
    }
    //判断 是不是已经是好友 已经是 不可以
    for( auto ite = m_mapIDToUserItem.begin() ; ite !=m_mapIDToUserItem.end();++ite )
    {
        UserItem * item = *ite;
        if( item->m_name == strName )
        {
            QMessageBox::about( m_mainWnd , "提示" , "已经是好友无需添加");
            return;
        }
    }
    //写数据包发送
    STRU_ADD_FRIEND_RQ rq;

    rq.userid = m_id;
    // ui显示 不涉及数据库 utf8就可以
    std::string userName = m_name.toStdString();
    strcpy( rq.userName , userName.c_str() );

//    std::string friendName = strName.toStdString();
//    strcpy( rq.friendName , friendName.c_str() );
    // 名字要查数据库 是gb2312
    Utf8ToGB2312( rq.friendName , sizeof(rq.friendName) , strName );

    m_tcpClient->SendData( 0 , (char*)&rq , sizeof(rq));

}

//主窗口退出 处理离线
void CKernel::slot_offline()
{
    //发离线请求 -- 服务器会转发给所有好友
    STRU_OFFLINE rq;
    rq.userid = m_id;
    m_tcpClient->SendData( 0 , (char*)&rq , sizeof(rq));

    //删除实例
    DestroyInstance();
}

#include<QTextCodec>

// QString -> char* gb2312
void CKernel::Utf8ToGB2312( char* gbbuf , int nlen ,QString& utf8)
{
    //转码的对象
    QTextCodec * gb2312code = QTextCodec::codecForName( "gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    QByteArray ba = gb2312code->fromUnicode( utf8 );// Unicode -> 转码对象的字符集

    strcpy_s ( gbbuf , nlen , ba.data() );
}

// char* gb2312 --> QString utf8
QString CKernel::GB2312ToUtf8( char* gbbuf )
{
    //转码的对象
    QTextCodec * gb2312code = QTextCodec::codecForName( "gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    return gb2312code->toUnicode( gbbuf );// 转码对象的字符集 -> Unicode
}
