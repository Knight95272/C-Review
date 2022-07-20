#pragma once
#include<windows.h>

class CMoTaBackGround
{
public:
	HBITMAP m_back;  // 背景小块
	HBITMAP m_backStatus; // 背景属性
	HBITMAP m_yellowKey; //黄钥匙
	HBITMAP m_blueKey; //绿钥匙
	HBITMAP m_redKey; //红钥匙

	int		m_nx;
	int		m_ny;
public:
	CMoTaBackGround();
	~CMoTaBackGround();
public:
	void InitBackGround(int x, int y, HINSTANCE hIns); //初始化背景
	void ShowBackGround(HDC hdc, HDC compHdc); //显示背景,判断阶数，然后显示对应阶
};

