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
	//case WM_CREATE: //窗口创建消息
	virtual void OnCreate();

	//case WM_PAINT:  //重绘消息
	virtual void OnDraw();

	//case WM_KEYDOWN:  //键盘按下触发消息
	virtual void OnKeyDown(WPARAM wParam);

	//case WM_TIMER:   //定时器，需要我们在子类中手动添加定时器并设置触发间隔，对定时器消息进行处理
	virtual void OnGameRun(WPARAM wParam);
	
	// 自己设置的定时器，玩家移动检测（子类中手动添加的定时器）
	void SetTimmer();
};

