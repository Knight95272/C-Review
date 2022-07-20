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

	//�����¼����
	void dealLoginRq( long lSendIP , char* buf , int nlen );
	//����ע������
	void dealRegisterRq( long lSendIP , char* buf , int nlen );
	//��������
	void dealChatRq(long lSendIP , char* buf , int nlen);
	//��Ӻ�������
	void dealAddFriendRq(long lSendIP , char* buf , int nlen);
	//��Ӻ��ѻظ�
	void dealAddFriendRs(long lSendIP , char* buf , int nlen);
	//��������
	void dealOfflinedRq(long lSendIP , char* buf , int nlen);

	//��ȡ�����б� : �����Լ�
	void GetUserList( int id);
	//�����ݿ��ȡ��Ϣ ��ѯ ���Ϊid�� �û���Ϣ  STRU_FRIEND_INFO
	void GetUserInfoFromSql( int id , STRU_FRIEND_INFO*  info );

private:
	void setProtocolMap();

	CMySql m_sql;
	INetMediator * m_pServer;

	//Э��ӳ���
	PFUN m_NetProtocolMap[_DEF_PROTOCOL_COUNT];

	map<int , int> m_mapIDToSock;
};

