#pragma once
//#include<vector>
//using namespace std;


//int Layer = 0; // ȫ�ֽ�����һ�׶����
// ÿһ��һ��13*13�Ķ�ά����
//vector<int> Coverage0;   // �����һ���Ǳ���  0 ������ʧ
//vector<int> Coverage1;   // �����ڶ�����ǽ 1 ������ʧ��������ǽ ��������ʧ
//vector<int> Coverage2;   // �������������� 2 ����Կ���ж��Ƿ��Ӧ��ʧ�������ܹ�
//vector<int> Coverage3;   // �������Ĳ��ǵ��� 3 ������Ӧ��������ԣ�������ʧ
//vector<int> Coverage4;   // ����������ǹ��� 4 �ж��Ƿ��ù�����ù���ʧ


// ��Ϸ�������ʼλ��
#define MOTA_PARAM_X     500
#define MOTA_PARAM_Y     500

// ���ϱ��ϵ��ܴ�С
#define MOTA_PARAM_WIDTH     468
#define MOTA_PARAM_HEIGH     391
// ����
#define MOTA_PARAM_TITLE    "ħ��"
// ��ռͼƬ�ܴ�С
#define MAPSIZE_BACKGROUND_WIDTH   452
#define MAPSIZE_BACKGROUND_HEIGH   352
// ����ͼ����
#define MOTA_BACKSTATUS_WIDTH 100
// һ��С�鳤��
#define BLOCK 32

// ��Ҷ�ʱ��  id���Լ�����ʱ�� ���ƶ�����
#define TIMER_PLAYER_MOVE_TIMERID          1
#define TIMER_PLAYER_MOVE_INTERVAL         200
#define PLAYERPALNE_MOVE_STEP              32


// ��ʷ��ķ λͼ��С����32BLOCK �����ú�
#define GREEM_SLM_BLOOD					   35
#define GREEM_SLM_ACK					   18
#define GREEM_SLM_DEF					   1
#define GREEM_SLM_GOLD					   1

// ������ʦ
#define PRIMARY_MAGE_BLOOD				   60
#define PRIMARY_MAGE_ACK				   32
#define PRIMARY_MAGE_DEF				   8
#define PRIMARY_MAGE_GOLD				   5

// С����
#define SMALL_BAT_BLOOD				   35
#define SMALL_BAT_ACK				   38
#define SMALL_BAT_DEF				   3
#define SMALL_BAT_GOLD				   3

// ������
#define SMALL_SKULL_BLOOD				   35
#define SMALL_SKULL_ACK				       38
#define SMALL_SKULL_DEF				       3
#define SMALL_SKULL_GOLD				   3

// ����ʿ��
#define MID_SKULL_BLOOD				   55
#define MID_SKULL_ACK				   52
#define MID_SKULL_DEF				   12
#define MID_SKULL_GOLD				   8