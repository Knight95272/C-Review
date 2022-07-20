#pragma once
#include<windows.h>
#include"../Player/Player.h"

class CFoeBox
{
public:
	// 血量 攻击值 防御值 金币 
	HBITMAP m_Foe;  // 敌人位图
	int		m_nx; // 位置
	int		m_ny;
	int		m_nBlood; // 血量
	int		m_ATK; // 攻击值
	int		m_DEF; //防御值
	int		m_GOLD; // 金币
	int		m_LOSSBLOOD; //战斗所失去血量

public:
	CFoeBox();
	virtual ~CFoeBox();
public:

	virtual void InitFoeMonstar(HINSTANCE hIns) = 0;  //根据怪物的自定义不同的怪物
	virtual void ShowFoeMonstar(HDC hdc, HDC compHdc) = 0; //怪物显示，不同类型的怪物显示不同
	virtual BOOL IsHitPlayer(CPlayer& player) = 0; //是否接触到玩家
};

