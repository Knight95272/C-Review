#pragma once
#include "FoeBox.h"
class CFoeSkullSmall :
    public CFoeBox
{
public:
	CFoeSkullSmall();
	~CFoeSkullSmall();
public:
	virtual void InitFoeMonstar(HINSTANCE hIns);
	virtual void ShowFoeMonstar(HDC hdc, HDC compHdc);
	virtual BOOL IsHitPlayer(CPlayer& player);
};

