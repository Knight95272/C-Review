#include "FoeBox.h"

CFoeBox::CFoeBox()
{
	m_Foe = NULL;  // ����λͼ
	m_nx = 0; // λ��
	m_ny = 0;
	m_nBlood = 0; // Ѫ��
	m_ATK = 0; // ����ֵ
	m_DEF = 0; //����ֵ
	m_GOLD = 0; // ���
	m_LOSSBLOOD = 0; //ս����ʧȥѪ��
}
CFoeBox::~CFoeBox()
{
	::DeleteObject(m_Foe);

	m_Foe = NULL;  // ����λͼ
	m_nx = 0; // λ��
	m_ny = 0;
	m_nBlood = 0; // Ѫ��
	m_ATK = 0; // ����ֵ
	m_DEF = 0; //����ֵ
	m_GOLD = 0; // ���
	m_LOSSBLOOD = 0; //ս����ʧȥѪ��
}