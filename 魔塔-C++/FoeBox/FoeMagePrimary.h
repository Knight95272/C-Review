#pragma once
#include "FoeBox.h"

class CFoeMagePrimary :
    public CFoeBox
{
public:
	CFoeMagePrimary();
	~CFoeMagePrimary();
public:
	virtual void InitFoeMonstar(HINSTANCE hIns);
	virtual void ShowFoeMonstar(HDC hdc, HDC compHdc);
	virtual BOOL IsHitPlayer(CPlayer& player);

};

