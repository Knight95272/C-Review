#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include "mychatdialog.h"
#include "INetMediator.h"
#include "packdef.h"

#include"logindialog.h"
#include<QMap>
#include"chatdialog.h"

class CKernel;
//函数指针
typedef void (CKernel::*PFUN)( char* buf , int nlen );

class CKernel : public QObject
{
    Q_OBJECT
public:
    explicit CKernel(QObject *parent = 0);

signals:

public slots:
    void DestroyInstance();
    void slot_dealData( long lSendIP , char* buf , int nlen );

    void setProtocolMap();
    //登录回复
    void slot_loginRs(char* buf , int nlen);
    //注册回复
    void slot_registerRs(char* buf , int nlen);
    //好友信息请求
    void slot_FriendInfoRq(char* buf , int nlen);
    //聊天的请求
    void slot_ChatRq(char* buf , int nlen);
    //聊天的回复
    void slot_ChatRs(char* buf , int nlen);
    //添加好友请求
    void slot_AddFriendRq(char* buf , int nlen);
    //添加好友回复
    void slot_AddFriendRs(char* buf , int nlen);
    //离线处理
    void slot_OfflineRq(char* buf , int nlen);

    void slot_LoginCommit( QString tel , QString password);
    void slot_RegisterCommit( QString tel , QString password , QString name );

    void slot_userItemClicked(int id);
    void slot_SendChatMsg( int id , QString content);
    void slot_addFriend();
    void slot_offline();

public:
    // QString -> char* gb2312
    static void Utf8ToGB2312(char* gbbuf , int nlen , QString &utf8);

    // char* gb2312 --> QString
    static QString GB2312ToUtf8( char* gbbuf );

private:
    MyChatDialog * m_mainWnd;
    INetMediator * m_tcpClient;
    LoginDialog *m_loginDialog;

    //协议映射表(函数指针数组) 协议头-->函数指针
    PFUN m_NetProtocolMap[ _DEF_PROTOCOL_COUNT ];

    // id -> 用户项
    QMap< int , UserItem* > m_mapIDToUserItem;
    //每一个用户一个聊天窗口  id -> chatdlg 对应
    QMap< int , ChatDialog* > m_mapIDToChatDialog;

    //个人的信息
    int m_id;
    QString m_name;
    int m_state;
    int m_iconid;
    QString m_feeling;


};

#endif // CKERNEL_H
