#pragma once
#include<windows.h>

class CMoTaBackGround
{
public:
	HBITMAP m_back;  // ����С��
	HBITMAP m_backStatus; // ��������
	HBITMAP m_yellowKey; //��Կ��
	HBITMAP m_blueKey; //��Կ��
	HBITMAP m_redKey; //��Կ��

	int		m_nx;
	int		m_ny;
public:
	CMoTaBackGround();
	~CMoTaBackGround();
public:
	void InitBackGround(int x, int y, HINSTANCE hIns); //��ʼ������
	void ShowBackGround(HDC hdc, HDC compHdc); //��ʾ����,�жϽ�����Ȼ����ʾ��Ӧ��
};

