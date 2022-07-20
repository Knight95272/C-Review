#include "FoeMagePrimary.h"
#include"../GameConfig/GameConfig.h"
#include"../images/resource.h"

CFoeMagePrimary::CFoeMagePrimary() {


}
CFoeMagePrimary::~CFoeMagePrimary() {


}
void CFoeMagePrimary::InitFoeMonstar(HINSTANCE hIns) {

	m_Foe = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_SLMGREEN));
	m_nBlood = PRIMARY_MAGE_BLOOD;
	m_ATK = PRIMARY_MAGE_ACK; // ¹¥»÷Öµ
	m_DEF = PRIMARY_MAGE_DEF; //·ÀÓùÖµ
	m_GOLD = PRIMARY_MAGE_GOLD; // ½ð±Ò

	m_nx = 0;
	m_ny = -BLOCK;

}
void CFoeMagePrimary::ShowFoeMonstar(HDC hdc, HDC compHdc) {
	::SelectObject(compHdc, m_Foe);
	::BitBlt(hdc, m_nx, m_ny, MOTA_BACKSTATUS_WIDTH + BLOCK * 7, BLOCK * 5,
		compHdc, 0, 0, SRCCOPY);
}
BOOL CFoeMagePrimary::IsHitPlayer(CPlayer& player) {

	return false;
}
