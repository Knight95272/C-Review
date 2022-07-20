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
//case WM_CREATE: //窗口创建消息
void CMoTaApp::OnCreate() {
	//创建定时器
	SetTimmer();
	//初始化背景
	m_back.InitBackGround(0, 0, this->m_hInstance);
	//初始化玩家
	m_player.InitPlayer( MOTA_BACKSTATUS_WIDTH + BLOCK*5,
		MAPSIZE_BACKGROUND_HEIGH - BLOCK, this->m_hInstance);

}

//case WM_PAINT:  //重绘消息
void CMoTaApp::OnDraw() {
	//获取窗口DC
	PAINTSTRUCT ps = { 0 };
	HDC hdc = ::BeginPaint(this->m_hWnd, &ps);

	//创建缓冲的DC  相当于先将所有的需要的先贴在一个DC上
	//，再将这个DC贴到显示的DC
	HDC cacheDC = ::CreateCompatibleDC(hdc /*兼容的窗口*/);
	// 创建兼容性位图（要兼容的窗口，大小即背景大小）
	HBITMAP map = ::CreateCompatibleBitmap(hdc, MAPSIZE_BACKGROUND_WIDTH, MAPSIZE_BACKGROUND_HEIGH);
	::SelectObject(cacheDC, map);  // 位图放在兼容性缓冲DC上

	//创建兼容性DC
	HDC compDC = ::CreateCompatibleDC(cacheDC);
	//-----------------------------------------

	m_back.ShowBackGround(cacheDC, compDC); // 显示背景
	m_player.ShowPlayer(cacheDC, compDC); //玩家的显示
	m_foeBoxlevel.ShowAllFoeLevel(cacheDC, compDC); //当前层所有怪物显示

	

	//-----------------------------------------
	// 将缓冲的DC贴到显示的DC上
	BitBlt(hdc, 0, 0, MAPSIZE_BACKGROUND_WIDTH, MAPSIZE_BACKGROUND_HEIGH, cacheDC, 0, 0, SRCCOPY);

	//删除显示的DC
	DeleteDC(compDC);
	compDC = NULL;

	::DeleteObject(map);  //删除位图
	map = NULL;

	DeleteDC(cacheDC); // 删除兼容性缓冲的DC
	cacheDC = NULL;

	::EndPaint(this->m_hWnd, &ps);


}
//case WM_TIMER:   //定时器，需要我们在子类中手动添加定时器并设置触发间隔，对定时器消息进行处理
void CMoTaApp::OnGameRun(WPARAM wParam) {  //根据对得到的定时器消息进行响应的处理
	switch (wParam)
	{
	case TIMER_PLAYER_MOVE_TIMERID: // 玩家飞机移动的定时器处理，移动飞机
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
	// 重新刷新
	RECT rect = { 0,0,MAPSIZE_BACKGROUND_WIDTH,MAPSIZE_BACKGROUND_HEIGH };
	::InvalidateRect(this->m_hWnd, &rect, FALSE);
}

//case WM_KEYDOWN:  //键盘按下触发消息
void CMoTaApp::OnKeyDown(WPARAM wParam) {
	switch (wParam)
	{
	case VK_LEFT:
	{

	}
	break;
	}

}
// 自己设置的定时器，，而是一直在使用的定时器，比如背景的移动，飞机移动检测（子类中手动添加的定时器）
void CMoTaApp::SetTimmer()
{
	//玩家移动监测定时器
	::SetTimer(this->m_hWnd, TIMER_PLAYER_MOVE_TIMERID, TIMER_PLAYER_MOVE_INTERVAL, NULL);


}