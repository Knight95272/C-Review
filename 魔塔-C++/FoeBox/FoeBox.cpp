#include "FoeBox.h"

CFoeBox::CFoeBox()
{
	m_Foe = NULL;  // 敌人位图
	m_nx = 0; // 位置
	m_ny = 0;
	m_nBlood = 0; // 血量
	m_ATK = 0; // 攻击值
	m_DEF = 0; //防御值
	m_GOLD = 0; // 金币
	m_LOSSBLOOD = 0; //战斗所失去血量
}
CFoeBox::~CFoeBox()
{
	::DeleteObject(m_Foe);

	m_Foe = NULL;  // 敌人位图
	m_nx = 0; // 位置
	m_ny = 0;
	m_nBlood = 0; // 血量
	m_ATK = 0; // 攻击值
	m_DEF = 0; //防御值
	m_GOLD = 0; // 金币
	m_LOSSBLOOD = 0; //战斗所失去血量
}