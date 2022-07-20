#include "FoeSkullMid.h"
#include"../GameConfig/GameConfig.h"
#include"../images/resource.h"

CFoeSkullMid::CFoeSkullMid() {


}
CFoeSkullMid::~CFoeSkullMid() {


}
void CFoeSkullMid::InitFoeMonstar(HINSTANCE hIns) {

	m_Foe = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_SLMGREEN));
	m_nBlood = MID_SKULL_BLOOD;
	m_ATK = MID_SKULL_ACK; // ¹¥»÷Öµ
	m_DEF = MID_SKULL_DEF; //·ÀÓùÖµ
	m_GOLD = MID_SKULL_GOLD; // ½ð±Ò

	m_nx = 0;
	m_ny = -BLOCK;

}
void CFoeSkullMid::ShowFoeMonstar(HDC hdc, HDC compHdc) {
	::SelectObject(compHdc, m_Foe);
	::BitBlt(hdc, m_nx, m_ny, MOTA_BACKSTATUS_WIDTH + BLOCK * 1, BLOCK * 6,
		compHdc, 0, 0, SRCCOPY);


}
BOOL CFoeSkullMid::IsHitPlayer(CPlayer& player) {

	return false;
}
