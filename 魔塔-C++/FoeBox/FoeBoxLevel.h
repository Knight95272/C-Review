#pragma once
#include<windows.h>
#include<list>
using namespace std;

#include"FoeBox.h"

class CFoeBoxLevel
{
public:
	list<CFoeBox*> m_lstFoe; // �ײ� --to ���ö���б��Զ���ײ���й���
public:
	CFoeBoxLevel();
	~CFoeBoxLevel();
public:
	void ShowAllFoeLevel(HDC hdc, HDC compHdc);
};

