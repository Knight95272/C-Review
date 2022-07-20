#include "FoeBatSmall.h"
#include"../GameConfig/GameConfig.h"
#include"../images/resource.h"

CFoeBatSmall::CFoeBatSmall() {


}
CFoeBatSmall::~CFoeBatSmall() {


}
void CFoeBatSmall::InitFoeMonstar(HINSTANCE hIns) {

	m_Foe = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_SLMGREEN));
	m_nBlood = SMALL_BAT_BLOOD;
	m_ATK = SMALL_BAT_ACK; // ¹¥»÷Öµ
	m_DEF = SMALL_BAT_DEF; //·ÀÓùÖµ
	m_GOLD = SMALL_BAT_GOLD; // ½ð±Ò

	m_nx = 0 ;
	m_ny = -BLOCK;

}
void CFoeBatSmall::ShowFoeMonstar(HDC hdc, HDC compHdc) {
	::SelectObject(compHdc, m_Foe);
	::BitBlt(hdc, m_nx, m_ny, MOTA_BACKSTATUS_WIDTH + BLOCK*9,BLOCK*9,
		compHdc, 0,0, SRCCOPY);
	::BitBlt(hdc, m_nx, m_ny, MOTA_BACKSTATUS_WIDTH + BLOCK * 6, BLOCK * 5,
		compHdc, 0, 0, SRCCOPY);
	::BitBlt(hdc, m_nx, m_ny, MOTA_BACKSTATUS_WIDTH + BLOCK * 8, BLOCK * 5,
		compHdc, 0, 0, SRCCOPY);
}
BOOL CFoeBatSmall::IsHitPlayer(CPlayer& player) {

	return FALSE;
}