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
CPlayer::~CPlayer() {  // ����ע��Ҫɾ��λͼ

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

void CPlayer::InitPlayer(int x, int y, HINSTANCE hIns) {  //��ʼ����ң�ѡ���ĸ�λͼ������ʼ�ڱ����ϵ�λ��
	m_nx = x;
	m_ny = y;

	m_playerDown = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_PLAYERDOWN));
	m_playerUp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_PLAYERUP));
	m_playerLeft = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_PLAYERLEFT));
	m_playerRight = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_PLAYERRIGHT));
	m_playerShow = m_playerDown;

}

void CPlayer::ShowPlayer(HDC hdc, HDC compHdc) {  //��ʾ��ҷɻ�,��ͼ
	::SelectObject(compHdc, m_playerShow);
	::BitBlt(hdc, m_nx, m_ny,BLOCK, BLOCK,
		compHdc, 0, 0, SRCCOPY);
}

void CPlayer::MovePlayer(int direct, int step) {  //�ƶ���ҷɻ���ͨ������direct�жϣ��ı�m_nx,m_ny��λ�ã����ı���ҷɻ���λ�÷ɻ�

	switch (direct)
	{
	case VK_LEFT:  //�� -    ����Ϊ��0��0��
	{
		if (m_nx - step <= MOTA_BACKSTATUS_WIDTH)
			m_nx = MOTA_BACKSTATUS_WIDTH;
		else
			m_nx -= step;
		m_playerShow = m_playerLeft;
	}
	break;

	case  VK_RIGHT: //�� +
	{
		if (m_nx + step >= (MAPSIZE_BACKGROUND_WIDTH - BLOCK))
			m_nx = (MAPSIZE_BACKGROUND_WIDTH - BLOCK);
		else
			m_nx += step;
		m_playerShow = m_playerRight;
	}
	break;
	case  VK_UP: // �� -
	{
		if (m_ny - step <= 0)
			m_ny = 0;
		else
			m_ny -= step;
		m_playerShow = m_playerUp;
	}
	break;
	case  VK_DOWN:  // �� +
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

