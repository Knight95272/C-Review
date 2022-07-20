#pragma once
#include<windows.h>
#include"../Player/Player.h"

class CFoeBox
{
public:
	// Ѫ�� ����ֵ ����ֵ ��� 
	HBITMAP m_Foe;  // ����λͼ
	int		m_nx; // λ��
	int		m_ny;
	int		m_nBlood; // Ѫ��
	int		m_ATK; // ����ֵ
	int		m_DEF; //����ֵ
	int		m_GOLD; // ���
	int		m_LOSSBLOOD; //ս����ʧȥѪ��

public:
	CFoeBox();
	virtual ~CFoeBox();
public:

	virtual void InitFoeMonstar(HINSTANCE hIns) = 0;  //���ݹ�����Զ��岻ͬ�Ĺ���
	virtual void ShowFoeMonstar(HDC hdc, HDC compHdc) = 0; //������ʾ����ͬ���͵Ĺ�����ʾ��ͬ
	virtual BOOL IsHitPlayer(CPlayer& player) = 0; //�Ƿ�Ӵ������
};

