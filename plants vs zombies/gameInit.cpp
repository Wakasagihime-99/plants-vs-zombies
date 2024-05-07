/**
*  @file：gameInit.cpp
*  @brief：初始化游戏界面，目前包括：
*          1、载入背景，左右晃一下（暂无僵尸预览）
*          2、打印用户名的房子（暂未有输入用户名方式，只能直接在这里赋值）
*          3、初始化卡牌（详见cards.cpp注释）
*          4、初始化土地（详见plantMap.cpp）
*  @version:0.1.6
*/

#include <graphics.h> // 调用easyX
#include <windows.h> // 调用sleep，调整窗口图标、位置等

#include "gameInit.h" // 自己的头文件
#include "characters.h" // 打印user's house
#include "transparrent.h"
#include "cards.h"
#include "img_processing.h"
#include "plantMap.h"
#include "resource.h"

/************************宏定义*****************************/

#define WIN_X 500       // 游戏窗口初始位置
#define WIN_Y 250
#define TEXT_X 250      // 谁谁的房子的文字起始位置
#define TEXT_Y 480
#define FINALX_BG 220   // 背景图片最终x位置（最终游戏定格画面位置）
#define BG_SLEEPTIME 5  // 背景左右移动时的sleeptime（ms）
#define BG_STRIDE 8     // 背景左右移动时的步幅（pixel）
#define HOUSEANDZOMBIE_SLEEPTIME 1500 // 看房子和预览僵尸时的等待时间


/************************全局变量****************************/

static IMAGE BgafterInit; // 用于获得所有静态的组成的背景是什么，用以刷新动态的东西前维护静态的背景
                          // static用于方便编译器优化。和不extern出去效果是一模一样的

IMAGE get_BgafterInit(){ // 获取全局变量
	return BgafterInit;
}


/**************************函数******************************/

void gameInit() // gameInit包含所有不在main循环中执行的部分
{
	/*********************窗口初始化及载入背景图片***********************/

	/*初始化窗口*/
	initgraph(WIN_WIDTH, WIN_HEIGHT); // 初始化一个窗口
	HWND hwnd = GetHWnd(); // 获取窗口句柄
	SetWindowPos(hwnd, NULL, WIN_X, WIN_Y, 0, 0, 
		SWP_NOSIZE | SWP_NOZORDER); // 用window API把窗口放中间点

	/*加载图标文件*/
	HINSTANCE hInstance = GetModuleHandle(NULL); // 获取应用实例句柄
	HICON hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icon), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);

	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon); // 设置大小图标
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

	/*加载背景图片*/
	IMAGE BgImg; //背景图片（这里是白天5条草坪）
	loadimage(&BgImg, "JPG", MAKEINTRESOURCE(background1_jpg)); // 使用了从资源读取图像
	                                                            // MAKEINTRESOURCE若未正确加载编译时会直接报错
	putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &BgImg, 0, 0); // 输入背景图片


	/**************************&{用户名}的房子***************************/

	char user[] = "Yoitu's house"; // 目前直接赋值

	printStr(HouseofTerror28, user, TEXT_X, TEXT_Y); // 打印字符串
	Sleep(HOUSEANDZOMBIE_SLEEPTIME); // 等待一段时间


	/**************************背景图片左右移动过程***************************/

	int leftShift = 0; // 定义移动数值
	int Bgimg_width = BgImg.getwidth(); // 获取背景长宽
	int Bgimg_height = BgImg.getheight();

	BeginBatchDraw(); // 开始批量绘图，可解决闪烁问题
	while (leftShift < (Bgimg_width - WIN_WIDTH)/2)	// 游戏开始时的展现房子到文字信息结束
	{
		cleardevice(); // 清除残留
		putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &BgImg, leftShift, 0); // 图片移动
		printStr(HouseofTerror28, user, TEXT_X, TEXT_Y); // 打印字符串
		FlushBatchDraw(); // 绘图

		Sleep(BG_SLEEPTIME); // 等待

		leftShift += BG_STRIDE;
	}
	EndBatchDraw();

	BeginBatchDraw();
	while (leftShift < Bgimg_width - WIN_WIDTH)	// 文字信息结束到移动到最右侧看僵尸
	{
		cleardevice();
		putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &BgImg, leftShift, 0);
		FlushBatchDraw();

		Sleep(BG_SLEEPTIME);

		leftShift += BG_STRIDE;
	}
	putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &BgImg, Bgimg_width - WIN_WIDTH, 0); // 最后一次的（防遗漏）
	EndBatchDraw(); // 结束批量绘图，统一绘制

	Sleep(HOUSEANDZOMBIE_SLEEPTIME); // 等待一段时间

	BeginBatchDraw(); // 开始批量绘图，可解决闪烁问题
	while (leftShift > FINALX_BG)	// 展现僵尸到最终定格准备开始游戏
	{
		cleardevice();
		putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &BgImg, leftShift, 0);
		FlushBatchDraw();

		Sleep(BG_SLEEPTIME);

		leftShift -= BG_STRIDE;
	}

    putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &BgImg, FINALX_BG, 0); // 最后一次的（防遗漏）

	EndBatchDraw(); // 结束批量绘图，统一绘制

	/**********************初始化卡牌***********************/

	InitCard();

	/**********************初始化土地***********************/

	clearPlot();

	// 初始化结束后获取静态图像
	getimage(&BgafterInit, 0, 0, WIN_WIDTH, WIN_HEIGHT); 
}
