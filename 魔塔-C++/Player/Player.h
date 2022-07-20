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
	int		m_layer; //除了所在位置，再加一个阶层
public:
	CPlayer();
	~CPlayer();
public:
	void InitPlayer(int x, int y, HINSTANCE hIns);  //定义玩家,初始方向为正
	void ShowPlayer(HDC hdc, HDC compHdc); //显示玩家
	void MovePlayer(int direct, int step); //移动玩家，根据按键方向改变图

};

