#include "FoeSkullSmall.h"
#include"../GameConfig/GameConfig.h"
#include"../images/resource.h"

CFoeSkullSmall::CFoeSkullSmall() {


}
CFoeSkullSmall::~CFoeSkullSmall() {


}
void CFoeSkullSmall::InitFoeMonstar(HINSTANCE hIns) {

	m_Foe = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_SLMGREEN));
	m_nBlood = SMALL_SKULL_BLOOD;
	m_ATK = SMALL_SKULL_ACK; // ¹¥»÷Öµ
	m_DEF = SMALL_SKULL_DEF; //·ÀÓùÖµ
	m_GOLD = SMALL_SKULL_GOLD; // ½ð±Ò

	m_nx = 0;
	m_ny = -BLOCK;

}
void CFoeSkullSmall::ShowFoeMonstar(HDC hdc, HDC compHdc) {
	::SelectObject(compHdc, m_Foe);
	::BitBlt(hdc, m_nx, m_ny, MOTA_BACKSTATUS_WIDTH + BLOCK * 1, BLOCK * 3,
		compHdc, 0, 0, SRCCOPY);


}
BOOL CFoeSkullSmall::IsHitPlayer(CPlayer& player) {

	return false;
}
