#pragma once
#include "FoeBox.h"
class CFoeBatSmall :
    public CFoeBox
{
public:
	CFoeBatSmall();
	~CFoeBatSmall();
public:
	virtual void InitFoeMonstar(HINSTANCE hIns);
	virtual void ShowFoeMonstar(HDC hdc, HDC compHdc);
	virtual BOOL IsHitPlayer(CPlayer& player);

};

