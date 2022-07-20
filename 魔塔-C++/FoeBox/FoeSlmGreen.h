#pragma once
#include "FoeBox.h"
class CFoeSlmGreen :
    public CFoeBox
{
public:
	CFoeSlmGreen();
	~CFoeSlmGreen();
public:
	virtual void InitFoeMonstar(HINSTANCE hIns);
	virtual void ShowFoeMonstar(HDC hdc, HDC compHdc);
	virtual BOOL IsHitPlayer(CPlayer& player);
};

