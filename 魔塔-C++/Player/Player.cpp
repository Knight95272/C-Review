#include "Player.h"
#include"../images/resource.h"
#include"../GameConfig/GameConfig.h"


CPlayer::CPlayer() {
	m_playerDown = NULL;
	m_playerUp = NULL;
	m_playerLeft = NULL;
	m_playerRight = NULL;
	m_playerShow = NULL;

	m_nx = 0;
	m_ny = 0;
	m_layer = 0;
}
CPlayer::~CPlayer() {  // 析构注意要删除位图

	::DeleteObject(m_playerDown);
	::DeleteObject(m_playerUp);
	::DeleteObject(m_playerLeft);
	::DeleteObject(m_playerRight);

	m_playerShow = NULL;
	m_playerDown = NULL;
	m_playerUp = NULL;
	m_playerLeft = NULL;
	m_playerRight = NULL;

	m_nx = 0;
	m_ny = 0;
	m_layer = 0;
}

void CPlayer::InitPlayer(int x, int y, HINSTANCE hIns) {  //初始化玩家，选择哪个位图，所初始在背景上的位置
	m_nx = x;
	m_ny = y;

	m_playerDown = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_PLAYERDOWN));
	m_playerUp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_PLAYERUP));
	m_playerLeft = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_PLAYERLEFT));
	m_playerRight = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_PLAYERRIGHT));
	m_playerShow = m_playerDown;

}

void CPlayer::ShowPlayer(HDC hdc, HDC compHdc) {  //显示玩家飞机,贴图
	::SelectObject(compHdc, m_playerShow);
	::BitBlt(hdc, m_nx, m_ny,BLOCK, BLOCK,
		compHdc, 0, 0, SRCCOPY);
}

void CPlayer::MovePlayer(int direct, int step) {  //移动玩家飞机，通过参数direct判断，改变m_nx,m_ny的位置，即改变玩家飞机的位置飞机

	switch (direct)
	{
	case VK_LEFT:  //左 -    左上为（0，0）
	{
		if (m_nx - step <= MOTA_BACKSTATUS_WIDTH)
			m_nx = MOTA_BACKSTATUS_WIDTH;
		else
			m_nx -= step;
		m_playerShow = m_playerLeft;
	}
	break;

	case  VK_RIGHT: //右 +
	{
		if (m_nx + step >= (MAPSIZE_BACKGROUND_WIDTH - BLOCK))
			m_nx = (MAPSIZE_BACKGROUND_WIDTH - BLOCK);
		else
			m_nx += step;
		m_playerShow = m_playerRight;
	}
	break;
	case  VK_UP: // 上 -
	{
		if (m_ny - step <= 0)
			m_ny = 0;
		else
			m_ny -= step;
		m_playerShow = m_playerUp;
	}
	break;
	case  VK_DOWN:  // 下 +
	{
		if (m_ny + step >= (MAPSIZE_BACKGROUND_HEIGH - BLOCK))
			m_ny = (MAPSIZE_BACKGROUND_HEIGH - BLOCK);
		else
			m_ny += step;
		m_playerShow = m_playerDown;
	}
	break;
	}


}

