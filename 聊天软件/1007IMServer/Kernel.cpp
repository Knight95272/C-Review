#include "Kernel.h"

#include"TcpServerMediator.h"
#include<iostream>

#define NetPackFunMap( a )  m_NetProtocolMap[ a - _DEF_PROTOCOL_BASE ]
void CKernel::setProtocolMap()
{
	memset( m_NetProtocolMap  , 0 , sizeof(m_NetProtocolMap) );

	NetPackFunMap( _DEF_PACK_LOGIN_RQ ) = &CKernel::dealLoginRq;
	NetPackFunMap( _DEF_PACK_REGISTER_RQ ) = &CKernel::dealRegisterRq;
	NetPackFunMap( _DEF_PACK_CHAT_RQ ) = &CKernel::dealChatRq;

	NetPackFunMap( _DEF_PACK_ADDFRIEND_RQ ) = &CKernel::dealAddFriendRq;
	NetPackFunMap( _DEF_PACK_ADDFRIEND_RS ) = &CKernel::dealAddFriendRs;

	NetPackFunMap( _DEF_PACK_OFFLINE_RQ ) = &CKernel::dealOfflinedRq;
}


CKernel * CKernel::pKernel = NULL;
CKernel::CKernel(void)
{
	pKernel = this;
	setProtocolMap();
}


CKernel::~CKernel(void)
{
	closeServer();
}

bool CKernel::startServer()
{
	//ip user pass db port
	if( !m_sql.ConnectMySql( "127.0.0.1" ,"root" ,"colin123" , "1008im" ) )
		return false;

	m_pServer = new TcpServerMediator;

	if(  !m_pServer -> OpenNet() )
		return false;

	return true;
}

void CKernel::closeServer()
{
	//其他资源的回收 todo

	m_sql.DisConnect();
	
	if(  m_pServer )
		m_pServer->CloseNet();
}


void CKernel::DealData( long lSendIP , char* buf , int nlen )
{
	std::cout<< lSendIP << ":" << buf <<std::endl;
	//SendData( lSendIP , buf , nlen );

	//协议映射关系 
	int type = *(int*) buf; // 按照四个字节取 协议头

	if( type >= _DEF_PROTOCOL_BASE && type < _DEF_PROTOCOL_BASE + _DEF_PROTOCOL_COUNT)
	{
		PFUN pf = NetPackFunMap(type);
		if( pf )
		{
			(this->*pf)( lSendIP , buf , nlen );
		}
	}
	delete[] buf;
} 


//处理登录请求
void CKernel::dealLoginRq( long lSendIP , char* buf , int nlen )
{
	//拆包 获取 tel password
	STRU_LOGIN_RQ * rq = (STRU_LOGIN_RQ *) buf;

	//根据tel 查 有没有这个人 
	list<string> lstRes;
	char sqlbuf[1024] = "";
	sprintf( sqlbuf, "select id , password from t_user where tel = '%s';" , rq->tel);
	if( !m_sql.SelectMySql(sqlbuf , 2 , lstRes ) )
	{
		cout << "select error:"<<sqlbuf <<endl;
	}
	STRU_LOGIN_RS rs;
	if( lstRes.size() == 0 )
	{//没有这个人 结果是查无此人
		rs.result = user_not_exist;
	}else
	{//有这个人  获取 id password
		int nID = atoi( lstRes.front().c_str() );
		lstRes.pop_front();

		string strPass = lstRes.front().c_str();
		lstRes.pop_front();

		//看 密码 是否一致 
		if( strcmp( strPass.c_str() , rq->password ) != 0 )
		{//不一致 密码错误 
			rs.result = password_error;
		}else
		{//一致 登录成功 返回id 以及结果
			rs.result = login_success;
			rs.userid = nID;

			m_pServer ->SendData( lSendIP , (char*)&rs , sizeof(rs) );

			//id -> sock 每个人的id 和套接字映射 , 然后后面通讯可以找到对方
			m_mapIDToSock[nID] = lSendIP;

			//获取好友列表 是在回复登录之后发生
			GetUserList( nID );

			return;
		}		
	}
	m_pServer ->SendData( lSendIP , (char*)&rs , sizeof(rs) );
}
//处理注册请求
void CKernel::dealRegisterRq( long lSendIP , char* buf , int nlen )
{
	//拆包
	STRU_REGISTER_RQ * rq = ( STRU_REGISTER_RQ * )buf;

	//拿到 tel 密码 name
	//查表 tel条件  查 有没有这个人 没有可以注册  
	list<string> resLst;
	char sqlbuf[1024] ="";
	sprintf(  sqlbuf , "select tel from t_user where tel = '%s';" , rq->tel );
	if( !m_sql.SelectMySql( sqlbuf , 1 , resLst ) )
	{
		cout << "SelectMySql error: "<<sqlbuf <<endl;
		return;
	}
	STRU_REGISTER_RS rs;
	
	if( resLst.size() > 0  )
	{ //有这个人
		rs.result = user_is_exist ;
	}else
	{//可以注册
		//写默认信息 -- ( 如果后面有关于传文件 , 可以先创建这个人的文件夹 )
		rs.result = register_success ;

		//添加判断 注册时姓名要唯一
		sprintf(  sqlbuf , "insert into t_user(tel ,password , name ,icon , feeling) values('%s' ,'%s', '%s' , 1 ,'比较懒,什么也没写')" 
			, rq->tel , rq->password , rq->name );
		if( !m_sql.UpdateMySql( sqlbuf ) )
		{
			cout << "UpdateMySql error: "<< sqlbuf <<endl;
		}
	}
	//返回结果 
	m_pServer->SendData( lSendIP , (char*)&rs , sizeof(rs));

}


//聊天请求
void CKernel::dealChatRq(long lSendIP , char* buf , int nlen)
{
	//拆包
	STRU_CHAT_RQ* rq = (STRU_CHAT_RQ*) buf;
	//看对方是否在线 
	if( m_mapIDToSock.find( rq->friendid ) == m_mapIDToSock.end() )
	{  //不在线 回复 不在结果
		STRU_CHAT_RS rs;
		rs.userid = rq->userid;
		rs.friendid = rq->friendid;
		rs.result = user_offline;
		m_pServer->SendData( lSendIP , (char*)&rs ,sizeof(rs) );

	}else{//在线 转发 先取到套接字 然后转发
		SOCKET sockFriend = m_mapIDToSock[ rq->friendid ];
		m_pServer->SendData( sockFriend , buf , nlen );
	}

}


//获取好友列表(信息) : 包括自己 id 是登录人的id
void CKernel::GetUserList( int id) 
{
	//首先 发给自己信息 
	STRU_FRIEND_INFO loginrq;
	GetUserInfoFromSql( id , &loginrq );

	//获取自己套接字 根据id从map中取出
	if( m_mapIDToSock.find( id ) == m_mapIDToSock.end() ) return; //找不到这个人 退出
	SOCKET sockLoginer = m_mapIDToSock[id ];

	//发送
	m_pServer->SendData( sockLoginer , (char*)&loginrq , sizeof(loginrq ) );

	//查询所有好友 id  , 根据id 调用函数 获取好友信息
	list<string> lstRes;
	char sqlbuf[1024] = "";
	sprintf( sqlbuf , "select idB from t_friend where idA = %d;", id); // 找id这个人对应所有好友id
	if( !m_sql.SelectMySql(sqlbuf , 1 , lstRes ) )
	{
		cout<<"select error:"<<sqlbuf <<endl;
	}
	//循环遍历好友列表 
	while( lstRes.size() > 0 )
	{
		//取出好友id
		int friendid = atoi( lstRes.front().c_str() );
		lstRes.pop_front();
		//获取好友信息
		STRU_FRIEND_INFO friendrq;
		GetUserInfoFromSql( friendid , &friendrq  );

		//给登录的人发送所有好友的信息
		m_pServer->SendData( sockLoginer , (char*)&friendrq , sizeof(friendrq)  );

		//好友如果在线, 发送登录人的信息给好友  要发送给好友 要先取出套接字
		if( m_mapIDToSock.find(friendid) == m_mapIDToSock.end() ) continue; //没有 就下一个人
		SOCKET sockFriend =  m_mapIDToSock[friendid];
		m_pServer->SendData( sockFriend , (char*)&loginrq , sizeof(loginrq)  );

	}
}

//从数据库获取信息 查询 身份为id的 用户信息  STRU_FRIEND_INFO
void CKernel::GetUserInfoFromSql( int id , STRU_FRIEND_INFO*  info )
{
	info->userid = id;
	// name iconid feeling state 
	list<string> lstRes;
	char sqlbuf[1024] = "";
	sprintf( sqlbuf , "select name ,icon , feeling from t_user where id = %d;", id);
	if( !m_sql.SelectMySql(sqlbuf , 3 , lstRes ) )
	{
		cout<< "select error:"<<sqlbuf<<endl;
	}
	if( lstRes.size() == 3  )
	{
		strcpy( info->name  , lstRes.front().c_str() );
		lstRes.pop_front();

		info->iconid = atoi( lstRes.front().c_str() );
		lstRes.pop_front();

		strcpy( info->feeling  , lstRes.front().c_str() );
		lstRes.pop_front();
	}
	//是否在线 看map里是否有这一项
	if( m_mapIDToSock.find( id ) != m_mapIDToSock.end() )
		info->state = 1; //找到
	else
		info->state = 0; //未找到
}

//添加好友请求
void CKernel::dealAddFriendRq(long lSendIP , char* buf , int nlen)
{
	//拆包 
	STRU_ADD_FRIEND_RQ * rq = (STRU_ADD_FRIEND_RQ *) buf;
	// 先看是否有这个人 
	
	 // 对方id 不知道 先查数据库
	list<string> lstRes;
	char sqlbuf[1024]="";
	sprintf( sqlbuf , "select id from t_user where name = '%s';", rq->friendName );
	if( !m_sql.SelectMySql( sqlbuf , 1 , lstRes ) )
	{
		cout << "select error:" << sqlbuf <<endl;
	}

	if( lstRes.size() > 0 )
	{
		//有这个人
		int friendid = atoi( lstRes.front().c_str() );
		lstRes.pop_front();

		//看是否在线 
		if( m_mapIDToSock.count( friendid ) > 0 )
		{//在线转发 先拿套接字 然后发送
			SOCKET sockFriend =  m_mapIDToSock[ friendid ];
			m_pServer->SendData( sockFriend , buf , nlen ); 
		}else
		{//不在线 回复不在线
			STRU_ADD_FRIEND_RS rs;
			rs.result = user_offline;
			rs.friendid = friendid;
			strcpy(  rs.friendName , rq->friendName );
			rs.userid = rq->userid ;
		
			m_pServer->SendData( lSendIP , (char*)&rs ,sizeof(rs)); 
		}

	}else{//没有这个人
		STRU_ADD_FRIEND_RS rs;
		rs.result = no_this_user;
		rs.friendid = 0;
		strcpy(  rs.friendName , rq->friendName );
		rs.userid = rq->userid ;
		
		m_pServer->SendData( lSendIP , (char*)&rs ,sizeof(rs)); 
	}
}
//添加好友回复
void CKernel::dealAddFriendRs(long lSendIP , char* buf , int nlen)
{
	// 拆包 
	STRU_ADD_FRIEND_RS * rs = (STRU_ADD_FRIEND_RS * ) buf;
	// 对方同意或拒绝 信息走到该位置  无论同意还是拒绝 都要转发
	if( rs->result == add_success )
	{// 同意 添加好友关系
		char sqlbuf[1024] = "";
		sprintf( sqlbuf , "insert into t_friend values( %d , %d);" , rs->userid , rs->friendid );
		if( !m_sql.UpdateMySql(sqlbuf) )
		{
			cout << "UpdateMySql error:"<< sqlbuf<<endl;
		}
		sprintf( sqlbuf , "insert into t_friend values( %d , %d);" ,rs->friendid , rs->userid   );
		if( !m_sql.UpdateMySql(sqlbuf) )
		{
			cout << "UpdateMySql error:"<< sqlbuf<<endl;
		}

		//更新好友列表
		GetUserList( rs->friendid );

	}
	//无论同意还是拒绝 都要转发
	if( m_mapIDToSock.count( rs->userid ) > 0 )
	{//在线转发 先拿套接字 然后发送
		SOCKET sock =  m_mapIDToSock[ rs->userid ];
		m_pServer->SendData( sock , buf , nlen ); 
	}
}

//离线请求
void CKernel::dealOfflinedRq(long lSendIP , char* buf , int nlen)
{
	// 拆包
	STRU_OFFLINE * rq = (STRU_OFFLINE *) buf;
	int userid = rq->userid;
	// 拿到id  查 所有好友的id
	list<string> lstRes;
	char sqlbuf[1024] = "";
	sprintf( sqlbuf , "select idB from t_friend where idA = %d;", userid); // 找id这个人对应所有好友id
	if( !m_sql.SelectMySql(sqlbuf , 1 , lstRes ) )
	{
		cout<<"select error:"<<sqlbuf <<endl;
	}
	while( lstRes.size() > 0 )
	{
		// 遍历 每个人 根据id 找 sock 转发 
		int friendid = atoi( lstRes.front().c_str());
		lstRes.pop_front();

		if( m_mapIDToSock.count( friendid ) == 0 ) continue ;
		SOCKET sock = m_mapIDToSock[ friendid ];
		m_pServer->SendData( sock , buf , nlen );
	}
	// 把这个人 在map中 移除
	if( m_mapIDToSock.count( userid ) > 0  )
	{
		m_mapIDToSock.erase( userid );
	}
}