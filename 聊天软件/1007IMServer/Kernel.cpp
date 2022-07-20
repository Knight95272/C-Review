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
	//������Դ�Ļ��� todo

	m_sql.DisConnect();
	
	if(  m_pServer )
		m_pServer->CloseNet();
}


void CKernel::DealData( long lSendIP , char* buf , int nlen )
{
	std::cout<< lSendIP << ":" << buf <<std::endl;
	//SendData( lSendIP , buf , nlen );

	//Э��ӳ���ϵ 
	int type = *(int*) buf; // �����ĸ��ֽ�ȡ Э��ͷ

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


//�����¼����
void CKernel::dealLoginRq( long lSendIP , char* buf , int nlen )
{
	//��� ��ȡ tel password
	STRU_LOGIN_RQ * rq = (STRU_LOGIN_RQ *) buf;

	//����tel �� ��û������� 
	list<string> lstRes;
	char sqlbuf[1024] = "";
	sprintf( sqlbuf, "select id , password from t_user where tel = '%s';" , rq->tel);
	if( !m_sql.SelectMySql(sqlbuf , 2 , lstRes ) )
	{
		cout << "select error:"<<sqlbuf <<endl;
	}
	STRU_LOGIN_RS rs;
	if( lstRes.size() == 0 )
	{//û������� ����ǲ��޴���
		rs.result = user_not_exist;
	}else
	{//�������  ��ȡ id password
		int nID = atoi( lstRes.front().c_str() );
		lstRes.pop_front();

		string strPass = lstRes.front().c_str();
		lstRes.pop_front();

		//�� ���� �Ƿ�һ�� 
		if( strcmp( strPass.c_str() , rq->password ) != 0 )
		{//��һ�� ������� 
			rs.result = password_error;
		}else
		{//һ�� ��¼�ɹ� ����id �Լ����
			rs.result = login_success;
			rs.userid = nID;

			m_pServer ->SendData( lSendIP , (char*)&rs , sizeof(rs) );

			//id -> sock ÿ���˵�id ���׽���ӳ�� , Ȼ�����ͨѶ�����ҵ��Է�
			m_mapIDToSock[nID] = lSendIP;

			//��ȡ�����б� ���ڻظ���¼֮����
			GetUserList( nID );

			return;
		}		
	}
	m_pServer ->SendData( lSendIP , (char*)&rs , sizeof(rs) );
}
//����ע������
void CKernel::dealRegisterRq( long lSendIP , char* buf , int nlen )
{
	//���
	STRU_REGISTER_RQ * rq = ( STRU_REGISTER_RQ * )buf;

	//�õ� tel ���� name
	//��� tel����  �� ��û������� û�п���ע��  
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
	{ //�������
		rs.result = user_is_exist ;
	}else
	{//����ע��
		//дĬ����Ϣ -- ( ��������й��ڴ��ļ� , �����ȴ�������˵��ļ��� )
		rs.result = register_success ;

		//����ж� ע��ʱ����ҪΨһ
		sprintf(  sqlbuf , "insert into t_user(tel ,password , name ,icon , feeling) values('%s' ,'%s', '%s' , 1 ,'�Ƚ���,ʲôҲûд')" 
			, rq->tel , rq->password , rq->name );
		if( !m_sql.UpdateMySql( sqlbuf ) )
		{
			cout << "UpdateMySql error: "<< sqlbuf <<endl;
		}
	}
	//���ؽ�� 
	m_pServer->SendData( lSendIP , (char*)&rs , sizeof(rs));

}


//��������
void CKernel::dealChatRq(long lSendIP , char* buf , int nlen)
{
	//���
	STRU_CHAT_RQ* rq = (STRU_CHAT_RQ*) buf;
	//���Է��Ƿ����� 
	if( m_mapIDToSock.find( rq->friendid ) == m_mapIDToSock.end() )
	{  //������ �ظ� ���ڽ��
		STRU_CHAT_RS rs;
		rs.userid = rq->userid;
		rs.friendid = rq->friendid;
		rs.result = user_offline;
		m_pServer->SendData( lSendIP , (char*)&rs ,sizeof(rs) );

	}else{//���� ת�� ��ȡ���׽��� Ȼ��ת��
		SOCKET sockFriend = m_mapIDToSock[ rq->friendid ];
		m_pServer->SendData( sockFriend , buf , nlen );
	}

}


//��ȡ�����б�(��Ϣ) : �����Լ� id �ǵ�¼�˵�id
void CKernel::GetUserList( int id) 
{
	//���� �����Լ���Ϣ 
	STRU_FRIEND_INFO loginrq;
	GetUserInfoFromSql( id , &loginrq );

	//��ȡ�Լ��׽��� ����id��map��ȡ��
	if( m_mapIDToSock.find( id ) == m_mapIDToSock.end() ) return; //�Ҳ�������� �˳�
	SOCKET sockLoginer = m_mapIDToSock[id ];

	//����
	m_pServer->SendData( sockLoginer , (char*)&loginrq , sizeof(loginrq ) );

	//��ѯ���к��� id  , ����id ���ú��� ��ȡ������Ϣ
	list<string> lstRes;
	char sqlbuf[1024] = "";
	sprintf( sqlbuf , "select idB from t_friend where idA = %d;", id); // ��id����˶�Ӧ���к���id
	if( !m_sql.SelectMySql(sqlbuf , 1 , lstRes ) )
	{
		cout<<"select error:"<<sqlbuf <<endl;
	}
	//ѭ�����������б� 
	while( lstRes.size() > 0 )
	{
		//ȡ������id
		int friendid = atoi( lstRes.front().c_str() );
		lstRes.pop_front();
		//��ȡ������Ϣ
		STRU_FRIEND_INFO friendrq;
		GetUserInfoFromSql( friendid , &friendrq  );

		//����¼���˷������к��ѵ���Ϣ
		m_pServer->SendData( sockLoginer , (char*)&friendrq , sizeof(friendrq)  );

		//�����������, ���͵�¼�˵���Ϣ������  Ҫ���͸����� Ҫ��ȡ���׽���
		if( m_mapIDToSock.find(friendid) == m_mapIDToSock.end() ) continue; //û�� ����һ����
		SOCKET sockFriend =  m_mapIDToSock[friendid];
		m_pServer->SendData( sockFriend , (char*)&loginrq , sizeof(loginrq)  );

	}
}

//�����ݿ��ȡ��Ϣ ��ѯ ���Ϊid�� �û���Ϣ  STRU_FRIEND_INFO
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
	//�Ƿ����� ��map���Ƿ�����һ��
	if( m_mapIDToSock.find( id ) != m_mapIDToSock.end() )
		info->state = 1; //�ҵ�
	else
		info->state = 0; //δ�ҵ�
}

//��Ӻ�������
void CKernel::dealAddFriendRq(long lSendIP , char* buf , int nlen)
{
	//��� 
	STRU_ADD_FRIEND_RQ * rq = (STRU_ADD_FRIEND_RQ *) buf;
	// �ȿ��Ƿ�������� 
	
	 // �Է�id ��֪�� �Ȳ����ݿ�
	list<string> lstRes;
	char sqlbuf[1024]="";
	sprintf( sqlbuf , "select id from t_user where name = '%s';", rq->friendName );
	if( !m_sql.SelectMySql( sqlbuf , 1 , lstRes ) )
	{
		cout << "select error:" << sqlbuf <<endl;
	}

	if( lstRes.size() > 0 )
	{
		//�������
		int friendid = atoi( lstRes.front().c_str() );
		lstRes.pop_front();

		//���Ƿ����� 
		if( m_mapIDToSock.count( friendid ) > 0 )
		{//����ת�� �����׽��� Ȼ����
			SOCKET sockFriend =  m_mapIDToSock[ friendid ];
			m_pServer->SendData( sockFriend , buf , nlen ); 
		}else
		{//������ �ظ�������
			STRU_ADD_FRIEND_RS rs;
			rs.result = user_offline;
			rs.friendid = friendid;
			strcpy(  rs.friendName , rq->friendName );
			rs.userid = rq->userid ;
		
			m_pServer->SendData( lSendIP , (char*)&rs ,sizeof(rs)); 
		}

	}else{//û�������
		STRU_ADD_FRIEND_RS rs;
		rs.result = no_this_user;
		rs.friendid = 0;
		strcpy(  rs.friendName , rq->friendName );
		rs.userid = rq->userid ;
		
		m_pServer->SendData( lSendIP , (char*)&rs ,sizeof(rs)); 
	}
}
//��Ӻ��ѻظ�
void CKernel::dealAddFriendRs(long lSendIP , char* buf , int nlen)
{
	// ��� 
	STRU_ADD_FRIEND_RS * rs = (STRU_ADD_FRIEND_RS * ) buf;
	// �Է�ͬ���ܾ� ��Ϣ�ߵ���λ��  ����ͬ�⻹�Ǿܾ� ��Ҫת��
	if( rs->result == add_success )
	{// ͬ�� ��Ӻ��ѹ�ϵ
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

		//���º����б�
		GetUserList( rs->friendid );

	}
	//����ͬ�⻹�Ǿܾ� ��Ҫת��
	if( m_mapIDToSock.count( rs->userid ) > 0 )
	{//����ת�� �����׽��� Ȼ����
		SOCKET sock =  m_mapIDToSock[ rs->userid ];
		m_pServer->SendData( sock , buf , nlen ); 
	}
}

//��������
void CKernel::dealOfflinedRq(long lSendIP , char* buf , int nlen)
{
	// ���
	STRU_OFFLINE * rq = (STRU_OFFLINE *) buf;
	int userid = rq->userid;
	// �õ�id  �� ���к��ѵ�id
	list<string> lstRes;
	char sqlbuf[1024] = "";
	sprintf( sqlbuf , "select idB from t_friend where idA = %d;", userid); // ��id����˶�Ӧ���к���id
	if( !m_sql.SelectMySql(sqlbuf , 1 , lstRes ) )
	{
		cout<<"select error:"<<sqlbuf <<endl;
	}
	while( lstRes.size() > 0 )
	{
		// ���� ÿ���� ����id �� sock ת�� 
		int friendid = atoi( lstRes.front().c_str());
		lstRes.pop_front();

		if( m_mapIDToSock.count( friendid ) == 0 ) continue ;
		SOCKET sock = m_mapIDToSock[ friendid ];
		m_pServer->SendData( sock , buf , nlen );
	}
	// ������� ��map�� �Ƴ�
	if( m_mapIDToSock.count( userid ) > 0  )
	{
		m_mapIDToSock.erase( userid );
	}
}