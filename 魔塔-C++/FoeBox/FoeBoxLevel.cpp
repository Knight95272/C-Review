#include "FoeBoxLevel.h"
#include<typeinfo>


CFoeBoxLevel::CFoeBoxLevel() {
	m_lstFoe.clear();
}

#define RANGE_DELETE_FOEPLANE(FOEPLANE_LIST)\
	list<CFoeBox*>::iterator ite##FOEPLANE_LIST = FOEPLANE_LIST.begin();\
	while( ite##FOEPLANE_LIST != FOEPLANE_LIST.end()){\
		delete *(ite##FOEPLANE_LIST);\
		*(ite##FOEPLANE_LIST) = NULL;\
		ite##FOEPLANE_LIST++;\
	}\
	FOEPLANE_LIST.clear();


CFoeBoxLevel::~CFoeBoxLevel() {

	RANGE_DELETE_FOEPLANE(m_lstFoe)

}

void CFoeBoxLevel::ShowAllFoeLevel(HDC hdc, HDC compHdc) {
	list<CFoeBox*>::iterator ite = m_lstFoe.begin();
	while (ite != m_lstFoe.end()) {

		//显示所有敌人飞机
		(*ite)->ShowFoeMonstar(hdc, compHdc);
		ite++;
	}
}


