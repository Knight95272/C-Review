#include "MoTaBackGround.h"
#include"../images/resource.h"
#include"../GameConfig/GameConfig.h"

CMoTaBackGround::CMoTaBackGround()
{
	m_back = NULL;
	m_backStatus = NULL;
	m_yellowKey = NULL; //»ÆÔ¿³×
	m_blueKey = NULL; //ÂÌÔ¿³×
	m_redKey = NULL; //ºìÔ¿³×

	m_nx = 0;
	m_ny = 0;
}
CMoTaBackGround::~CMoTaBackGround()
{
	m_nx = 0;
	m_ny = 0;

	::DeleteObject(m_back);
	::DeleteObject(m_backStatus);
	::DeleteObject(m_yellowKey);
	::DeleteObject(m_blueKey);
	::DeleteObject(m_redKey);

	m_backStatus = NULL;
	m_back = NULL;
	m_yellowKey = NULL; 
	m_blueKey = NULL;
	m_redKey = NULL; 
}

void CMoTaBackGround::InitBackGround(int x, int y, HINSTANCE hIns) {
	m_nx = x;
	m_ny = y;

	m_back = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BACK));
	m_backStatus = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BACKSTATUS));
	m_yellowKey = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_YELLOWKEY));
	m_blueKey = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BLUEKEY));
	m_redKey = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_REDKEY));

}
//ÏÔÊ¾±³¾°,ÅÐ¶Ï½×Êý£¬È»ºóÏÔÊ¾¶ÔÓ¦½×
void CMoTaBackGround::ShowBackGround(HDC hdc, HDC compHdc)
{
	for (int i = 0;i<11;i++)
	{
		for (int j = 0; j < 11; j++)
		{
			::SelectObject(compHdc, m_back);
			::BitBlt(hdc, m_nx + MOTA_BACKSTATUS_WIDTH + BLOCK*i, m_ny+ BLOCK*j, BLOCK, BLOCK,
				compHdc, 0, 0, SRCCOPY);
		}
	}

	::SelectObject(compHdc, m_backStatus);
	::BitBlt(hdc, m_nx, m_ny , MAPSIZE_BACKGROUND_WIDTH, MAPSIZE_BACKGROUND_HEIGH,
		compHdc, 0, 0, SRCCOPY);

	::SelectObject(compHdc, m_yellowKey);
	::BitBlt(hdc, m_nx, m_ny , BLOCK, BLOCK,
		compHdc, 0, 0, SRCCOPY);
	::SelectObject(compHdc, m_blueKey);
	::BitBlt(hdc, m_nx, m_ny + BLOCK, BLOCK, BLOCK,
		compHdc, 0, 0, SRCCOPY);
	::SelectObject(compHdc, m_redKey);
	::BitBlt(hdc, m_nx, m_ny + BLOCK*2, BLOCK, BLOCK,
		compHdc, 0, 0, SRCCOPY);
}