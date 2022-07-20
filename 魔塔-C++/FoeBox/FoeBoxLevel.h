#pragma once
#include<windows.h>
#include<list>
using namespace std;

#include"FoeBox.h"

class CFoeBoxLevel
{
public:
	list<CFoeBox*> m_lstFoe; // 阶层 --to 设置多个列表，对多个阶层进行管理
public:
	CFoeBoxLevel();
	~CFoeBoxLevel();
public:
	void ShowAllFoeLevel(HDC hdc, HDC compHdc);
};

