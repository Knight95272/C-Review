#include "MoTaApp.h"
#include"../GameConfig/GameConfig.h"
#include"../FoeBox/FoeBox.h"
#include"../FoeBox/FoeBatSmall.h"
#include"../FoeBox/FoeMagePrimary.h"
#include"../FoeBox/FoeSkullMid.h"
#include"../FoeBox/FoeSkullSmall.h"
#include"../FoeBox/FoeSlmGreen.h"


GET_OBJECT(CMoTaApp)
CLASS_CONFIG(MOTA_PARAM_X, MOTA_PARAM_Y, MOTA_PARAM_WIDTH, MOTA_PARAM_HEIGH, (char*)MOTA_PARAM_TITLE)

CMoTaApp::CMoTaApp()
{

}
CMoTaApp::~CMoTaApp()
{

}
//case WM_CREATE: //���ڴ�����Ϣ
void CMoTaApp::OnCreate() {
	//������ʱ��
	SetTimmer();
	//��ʼ������
	m_back.InitBackGround(0, 0, this->m_hInstance);
	//��ʼ�����
	m_player.InitPlayer( MOTA_BACKSTATUS_WIDTH + BLOCK*5,
		MAPSIZE_BACKGROUND_HEIGH - BLOCK, this->m_hInstance);

}

//case WM_PAINT:  //�ػ���Ϣ
void CMoTaApp::OnDraw() {
	//��ȡ����DC
	PAINTSTRUCT ps = { 0 };
	HDC hdc = ::BeginPaint(this->m_hWnd, &ps);

	//���������DC  �൱���Ƚ����е���Ҫ��������һ��DC��
	//���ٽ����DC������ʾ��DC
	HDC cacheDC = ::CreateCompatibleDC(hdc /*���ݵĴ���*/);
	// ����������λͼ��Ҫ���ݵĴ��ڣ���С��������С��
	HBITMAP map = ::CreateCompatibleBitmap(hdc, MAPSIZE_BACKGROUND_WIDTH, MAPSIZE_BACKGROUND_HEIGH);
	::SelectObject(cacheDC, map);  // λͼ���ڼ����Ի���DC��

	//����������DC
	HDC compDC = ::CreateCompatibleDC(cacheDC);
	//-----------------------------------------

	m_back.ShowBackGround(cacheDC, compDC); // ��ʾ����
	m_player.ShowPlayer(cacheDC, compDC); //��ҵ���ʾ
	m_foeBoxlevel.ShowAllFoeLevel(cacheDC, compDC); //��ǰ�����й�����ʾ

	

	//-----------------------------------------
	// �������DC������ʾ��DC��
	BitBlt(hdc, 0, 0, MAPSIZE_BACKGROUND_WIDTH, MAPSIZE_BACKGROUND_HEIGH, cacheDC, 0, 0, SRCCOPY);

	//ɾ����ʾ��DC
	DeleteDC(compDC);
	compDC = NULL;

	::DeleteObject(map);  //ɾ��λͼ
	map = NULL;

	DeleteDC(cacheDC); // ɾ�������Ի����DC
	cacheDC = NULL;

	::EndPaint(this->m_hWnd, &ps);


}
//case WM_TIMER:   //��ʱ������Ҫ�������������ֶ���Ӷ�ʱ�������ô���������Զ�ʱ����Ϣ���д���
void CMoTaApp::OnGameRun(WPARAM wParam) {  //���ݶԵõ��Ķ�ʱ����Ϣ������Ӧ�Ĵ���
	switch (wParam)
	{
	case TIMER_PLAYER_MOVE_TIMERID: // ��ҷɻ��ƶ��Ķ�ʱ�������ƶ��ɻ�
	{
		if (::GetAsyncKeyState(VK_LEFT)) {
			m_player.MovePlayer(VK_LEFT, PLAYERPALNE_MOVE_STEP);
		}

		if (::GetAsyncKeyState(VK_RIGHT)) {
			m_player.MovePlayer(VK_RIGHT, PLAYERPALNE_MOVE_STEP);
		}

		if (::GetAsyncKeyState(VK_UP)) {
			m_player.MovePlayer(VK_UP, PLAYERPALNE_MOVE_STEP);
		}

		if (::GetAsyncKeyState(VK_DOWN)) {
			m_player.MovePlayer(VK_DOWN, PLAYERPALNE_MOVE_STEP);
		}
	}
	break;
	}
	// ����ˢ��
	RECT rect = { 0,0,MAPSIZE_BACKGROUND_WIDTH,MAPSIZE_BACKGROUND_HEIGH };
	::InvalidateRect(this->m_hWnd, &rect, FALSE);
}

//case WM_KEYDOWN:  //���̰��´�����Ϣ
void CMoTaApp::OnKeyDown(WPARAM wParam) {
	switch (wParam)
	{
	case VK_LEFT:
	{

	}
	break;
	}

}
// �Լ����õĶ�ʱ����������һֱ��ʹ�õĶ�ʱ�������米�����ƶ����ɻ��ƶ���⣨�������ֶ���ӵĶ�ʱ����
void CMoTaApp::SetTimmer()
{
	//����ƶ���ⶨʱ��
	::SetTimer(this->m_hWnd, TIMER_PLAYER_MOVE_TIMERID, TIMER_PLAYER_MOVE_INTERVAL, NULL);


}