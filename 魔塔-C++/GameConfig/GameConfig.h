#pragma once
//#include<vector>
//using namespace std;


//int Layer = 0; // 全局阶数，一阶多个层
// 每一层一个13*13的二维数组
//vector<int> Coverage0;   // 最底下一层是背景  0 不会消失
//vector<int> Coverage1;   // 倒数第二层是墙 1 不会消失，除特殊墙 ，碰到消失
//vector<int> Coverage2;   // 倒数第三层是门 2 根据钥匙判断是否对应消失，否则不能过
//vector<int> Coverage3;   // 倒数第四层是道具 3 增长对应的玩家属性，捡到则消失
//vector<int> Coverage4;   // 倒数第五层是怪物 4 判断是否打得过，打得过消失


// 游戏窗体的起始位置
#define MOTA_PARAM_X     500
#define MOTA_PARAM_Y     500

// 加上边上的总大小
#define MOTA_PARAM_WIDTH     468
#define MOTA_PARAM_HEIGH     391
// 标题
#define MOTA_PARAM_TITLE    "魔塔"
// 所占图片总大小
#define MAPSIZE_BACKGROUND_WIDTH   452
#define MAPSIZE_BACKGROUND_HEIGH   352
// 属性图长度
#define MOTA_BACKSTATUS_WIDTH 100
// 一个小块长度
#define BLOCK 32

// 玩家定时器  id，以及其间隔时长 ，移动步符
#define TIMER_PLAYER_MOVE_TIMERID          1
#define TIMER_PLAYER_MOVE_INTERVAL         200
#define PLAYERPALNE_MOVE_STEP              32


// 绿史莱姆 位图大小都是32BLOCK 不设置宏
#define GREEM_SLM_BLOOD					   35
#define GREEM_SLM_ACK					   18
#define GREEM_SLM_DEF					   1
#define GREEM_SLM_GOLD					   1

// 初级法师
#define PRIMARY_MAGE_BLOOD				   60
#define PRIMARY_MAGE_ACK				   32
#define PRIMARY_MAGE_DEF				   8
#define PRIMARY_MAGE_GOLD				   5

// 小蝙蝠
#define SMALL_BAT_BLOOD				   35
#define SMALL_BAT_ACK				   38
#define SMALL_BAT_DEF				   3
#define SMALL_BAT_GOLD				   3

// 骷髅人
#define SMALL_SKULL_BLOOD				   35
#define SMALL_SKULL_ACK				       38
#define SMALL_SKULL_DEF				       3
#define SMALL_SKULL_GOLD				   3

// 骷髅士兵
#define MID_SKULL_BLOOD				   55
#define MID_SKULL_ACK				   52
#define MID_SKULL_DEF				   12
#define MID_SKULL_GOLD				   8