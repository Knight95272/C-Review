#pragma once

#include"../GameFrame/GameApp.h"
#include"../MoTaBackGround/MoTaBackGround.h"
#include"../Player/Player.h"
#include"../FoeBox/FoeBoxLevel.h"

class CMoTaApp :
    public CGameApp
{
public:
    CMoTaBackGround m_back;
	CPlayer m_player;
	CFoeBoxLevel m_foeBoxlevel;

public:
    CMoTaApp();
    ~CMoTaApp();
public:
	//case WM_CREATE: //���ڴ�����Ϣ
	virtual void OnCreate();

	//case WM_PAINT:  //�ػ���Ϣ
	virtual void OnDraw();

	//case WM_KEYDOWN:  //���̰��´�����Ϣ
	virtual void OnKeyDown(WPARAM wParam);

	//case WM_TIMER:   //��ʱ������Ҫ�������������ֶ���Ӷ�ʱ�������ô���������Զ�ʱ����Ϣ���д���
	virtual void OnGameRun(WPARAM wParam);
	
	// �Լ����õĶ�ʱ��������ƶ���⣨�������ֶ���ӵĶ�ʱ����
	void SetTimmer();
};

