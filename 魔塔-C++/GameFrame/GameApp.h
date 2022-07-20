#pragma once
#include<windows.h>

class CGameApp{ 
public:
	HINSTANCE m_hInstance;
	HWND      m_hWnd;
public:
	CGameApp() {}
	virtual ~CGameApp() {}
public:
	void SetHandle(HINSTANCE hIns, HWND hWnd) {
		m_hInstance = hIns;
		m_hWnd = hWnd;
	}
public:
	//case WM_CREATE: //窗口创建消息
	virtual void OnCreate() {}

	//case WM_PAINT:  //重绘消息
	virtual void OnDraw() {}

	//case WM_TIMER:   //定时器，需要我们在子类中手动添加定时器并设置触发间隔
	virtual void OnGameRun(WPARAM wParam) {}

	//case WM_KEYDOWN:  //键盘按下触发消息
	virtual void OnKeyDown(WPARAM wParam) {}

	//case WM_KEYUP:  //键盘抬起触发消息
	virtual void OnKeyUp(WPARAM wParam) {}


	//case WM_LBUTTONDOWN: //鼠标左键按下触发消息
	virtual void OnLButtonDown(POINT& po) {}



	//case WM_LBUTTONUP: //鼠标左键抬起触发消息
	virtual void OnLButtonUp(POINT& po) {}


	//case WM_MOUSEMOVE:  //鼠标移动
	virtual void OnMouseMove(POINT& po) {}

};

CGameApp* GetChildObject();

#define GET_OBJECT(CHILD_CLASS)\
	CGameApp * GetChildObject(){\
		return new CHILD_CLASS;\
	}


#define CLASS_CONFIG(PARAM_X,PARAM_Y,PARAM_WIDTH,PARAM_HEIGH,PARAM_TITLE)\
	int nx = PARAM_X;\
	int ny=PARAM_Y;\
	int nwidth =PARAM_WIDTH;\
	int nheigh = PARAM_HEIGH;\
	CHAR * strTitle=PARAM_TITLE;