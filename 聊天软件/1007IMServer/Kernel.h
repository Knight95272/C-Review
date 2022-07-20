#pragma once



#include"CMySql.h"
#include"INetMediator.h"


#include"packdef.h"
#include<map>

class CKernel;

typedef void (CKernel::*PFUN)(long lSendIP , char* buf , int nlen);

class CKernel
{
public:
	CKernel(void);
	~CKernel(void);

	bool startServer();
	void closeServer();
	void DealData( long lSendIP , char* buf , int nlen );

	static CKernel * pKernel ;

	//处理登录请求
	void dealLoginRq( long lSendIP , char* buf , int nlen );
	//处理注册请求
	void dealRegisterRq( long lSendIP , char* buf , int nlen );
	//聊天请求
	void dealChatRq(long lSendIP , char* buf , int nlen);
	//添加好友请求
	void dealAddFriendRq(long lSendIP , char* buf , int nlen);
	//添加好友回复
	void dealAddFriendRs(long lSendIP , char* buf , int nlen);
	//离线请求
	void dealOfflinedRq(long lSendIP , char* buf , int nlen);

	//获取好友列表 : 包括自己
	void GetUserList( int id);
	//从数据库获取信息 查询 身份为id的 用户信息  STRU_FRIEND_INFO
	void GetUserInfoFromSql( int id , STRU_FRIEND_INFO*  info );

private:
	void setProtocolMap();

	CMySql m_sql;
	INetMediator * m_pServer;

	//协议映射表
	PFUN m_NetProtocolMap[_DEF_PROTOCOL_COUNT];

	map<int , int> m_mapIDToSock;
};

