#pragma once
#include<windows.h>

class CPlayer
{
public:
	HBITMAP m_playerDown;
	HBITMAP m_playerUp;
	HBITMAP m_playerLeft;
	HBITMAP m_playerRight;
	HBITMAP m_playerShow;

	int		m_nx;
	int		m_ny;
	int		m_layer; //��������λ�ã��ټ�һ���ײ�
public:
	CPlayer();
	~CPlayer();
public:
	void InitPlayer(int x, int y, HINSTANCE hIns);  //�������,��ʼ����Ϊ��
	void ShowPlayer(HDC hdc, HDC compHdc); //��ʾ���
	void MovePlayer(int direct, int step); //�ƶ���ң����ݰ�������ı�ͼ

};

