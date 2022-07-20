#include "FoeSlmGreen.h"
#include"../GameConfig/GameConfig.h"
#include"../images/resource.h"

CFoeSlmGreen::CFoeSlmGreen() {


}
CFoeSlmGreen::~CFoeSlmGreen() {


}

void CFoeSlmGreen::InitFoeMonstar(HINSTANCE hIns) {

	m_Foe = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_SLMGREEN));
	m_nBlood = GREEM_SLM_BLOOD;
	m_ATK = GREEM_SLM_ACK; // ¹¥»÷Öµ
	m_DEF = GREEM_SLM_DEF; //·ÀÓùÖµ
	m_GOLD = GREEM_SLM_GOLD; // ½ð±Ò

	m_nx = 0;
	m_ny = -BLOCK;

}
void CFoeSlmGreen::ShowFoeMonstar(HDC hdc, HDC compHdc) {
	::SelectObject(compHdc, m_Foe);
	::BitBlt(hdc, m_nx, m_ny, MOTA_BACKSTATUS_WIDTH + BLOCK * 8, BLOCK * 10,
		compHdc, 0, 0, SRCCOPY);
	::BitBlt(hdc, m_nx, m_ny, MOTA_BACKSTATUS_WIDTH + BLOCK * 10, BLOCK * 10,
		compHdc, 0, 0, SRCCOPY);


}
BOOL CFoeSlmGreen::IsHitPlayer(CPlayer& player) {

	return false;
}
