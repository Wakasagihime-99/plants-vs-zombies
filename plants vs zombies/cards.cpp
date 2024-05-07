/**
* @file：cards.cpp
* @brief：游戏卡牌初始化
* @date: 2024.5.3
*/

#include <stdio.h> // 用于sprintf_s
#include <graphics.h>

#include "img_processing.h" // 处理图像
#include "characters.h" // 打字
#include "cardInfo.h" // 卡牌信息
#include "cards.h" // 把部分define挪到头文件了
#include "gameInit.h" // 用于获得窗口大小
#include "resource.h" // 用于加载图片


#define PLANTTOCARDBIAS_X 4    // 植物相比卡牌底色的偏置
#define PLANTTOCARDBIAS_Y 10

#define BARDESCEND_SLEEPTIME 1 // 工具栏向下弹出的sleeptime
#define BARDESCEND_STRIDE 10   // 工具栏向下弹出的步幅
#define PRICETOCARDBIAS_X 12   // 相比第一张牌，第一个price的右移程度
#define PRICETOCARDBIAS_Y 48
#define TWOBITSPACE 5 // 两位数价格补全

/*全局变量*/
static int plantChooseNum; // 选了几张牌
int get_plantChooseNum(){
	return plantChooseNum;
}

static int plantChoose[10]; // 选了哪几个植物（数组顺序为卡牌顺序，所存值为卡号）
int get_plantChoose(int _i) 
{
	if (_i < 10) {
		return plantChoose[_i];
	}

	else
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "get_plantChoose函数参数越界", "ERROR", MB_ICONWARNING);
		return NULL;
	}
}


void InitCard()
{
	loadCardInfo(); // 加载卡牌信息

	/***********************加载素材图片***************************/

	IMAGE Bar; // 工具栏
	loadimage(&Bar, "PNG", MAKEINTRESOURCE(bar_png)); // 加载导航栏

	IMAGE Seeds; // 加载卡牌底色图片
	loadimage(&Seeds, "PNG", MAKEINTRESOURCE(seeds_png));

	IMAGE res_img; // 加载卡牌时的恢复图像
	getimage(&res_img, 0, 0, WIN_WIDTH, WIN_HEIGHT);

	/**************************未做的假功能*****************************/
	// 以后肯定要做初始化

	plantChooseNum = plantCount; // 暂时没有选择功能捏
	//plantChoose[0] = _sunflower; // 只能先赋值，两种情况测试用
	//plantChoose[1] = _peashootersingle;

	plantChoose[0] = peashootersingle;
	plantChoose[1] = sunflower;

	/***********************导航栏作图*************************/

	SetWorkingImage(&Bar); // 设置工具栏为当前绘图目标

	for (int i = 0; i < plantChooseNum; i++) // 把牌画上去
	{
		putimage(FIRSTX_CARD + i * (CARD_WIDTH + CARD_SPACE), Y_CARD, CARD_WIDTH, CARD_HEIGHT,
			&Seeds, get_cardsIfo_color(plantChoose[i]) * CARD_WIDTH, 0); // 画底牌
		
		IMAGE* imgtoDraw_p = (IMAGE*)malloc(sizeof(IMAGE)); // 分配一段IMAGE的地方
		if (imgtoDraw_p == NULL) // 要是没分配出来
		{
			HWND hwnd = GetForegroundWindow();
			MessageBox(hwnd, "动态内存imgtoDraw_p分配错误", "ERROR", MB_ICONERROR);
			return;
		}
		else {
			memset(imgtoDraw_p, 0, sizeof(IMAGE));
		}

		get_CardsImg(plantChoose[i], imgtoDraw_p);
		draw_blue(FIRSTX_CARD + i * (CARD_WIDTH + CARD_SPACE) + PLANTTOCARDBIAS_X, // 画牌上的植物
			Y_CARD + PLANTTOCARDBIAS_Y, *imgtoDraw_p);

		if (get_cardsIfo_price(plantChoose[i]) < 100){ // 打印价格：两位数则右对齐
			printNum(Pico129, get_cardsIfo_price(plantChoose[i]), FIRSTX_CARD + i * (CARD_WIDTH + CARD_SPACE) + PRICETOCARDBIAS_X + TWOBITSPACE, // 打印价格
				Y_CARD + PRICETOCARDBIAS_Y);
		}

		else { // 三位数正常打
			printNum(Pico129, get_cardsIfo_price(plantChoose[i]), FIRSTX_CARD + i * (CARD_WIDTH + CARD_SPACE) + PRICETOCARDBIAS_X, // 打印价格
				Y_CARD + PRICETOCARDBIAS_Y);
		}
		
		free(imgtoDraw_p); // 释放内存
		imgtoDraw_p = NULL;
	}

	SetWorkingImage(); // 当前绘图目标变回普通绘图窗口

	ImgRiseorDown(FINALX_BAR, -Bar.getheight(), 0, BARDESCEND_SLEEPTIME, BARDESCEND_STRIDE, Bar, res_img); // 导航栏弹出
}


