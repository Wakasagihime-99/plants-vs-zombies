#ifndef GAMEINIT_H
#define GAMEINIT_H

#include <graphics.h> // 为下方要用的IMAGE

/*全局宏定义*/
#define WIN_WIDTH 800   // 游戏窗口大小
#define WIN_HEIGHT 600

/*获取全局变量*/
IMAGE get_BgafterInit(); // 用于获得所有静态的组成的背景是什么，用以刷新动态的东西前维护静态的背景

// 详见gameInit.cpp
void gameInit();

#endif // !GAMEINIT_H

