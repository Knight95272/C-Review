#pragma once
#include "FoeBox.h"
class CFoeSkullMid :
    public CFoeBox
{
public:
	CFoeSkullMid();
	~CFoeSkullMid();
public:
	virtual void InitFoeMonstar(HINSTANCE hIns);
	virtual void ShowFoeMonstar(HDC hdc, HDC compHdc);
	virtual BOOL IsHitPlayer(CPlayer& player);
};

