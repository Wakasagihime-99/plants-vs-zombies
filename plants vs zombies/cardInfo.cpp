/**
* @file: cardInfo.cpp
* @brief: 1、所有植物卡牌图片预加载。
*         2、卡牌信息初始化（使用了自定义的Card结构体，在头文件中）
*         3、卡牌动画初始化
*/


#include <windows.h> 
#include <stdio.h>
#include <graphics.h>

#include "cardInfo.h"
#include "resource.h"

// 找到了缩放方法，但是不太清晰，还是ps处理吧
/*****************************全局变量******************************************/

static IMAGE CardsImg[plantCount]; // 存放植物卡牌，plants=0即Cards[0]
void get_CardsImg(int _i, IMAGE* _saveimg)
{
	if (_i < plantCount) {
		memcpy_s(_saveimg, sizeof(IMAGE), &CardsImg[_i], sizeof(IMAGE));
	}

	else
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "get_CardsImg函数参数越界", "ERROR", MB_ICONERROR);
		return;
	}
}

static IMAGE CardsImg_L[plantCount]; // 80xp的植物图
void get_CardsImg_L(int _i, IMAGE* _saveimg)
{
	if (_i < plantCount) {
		memcpy_s(_saveimg, sizeof(IMAGE), &CardsImg_L[_i], sizeof(IMAGE));
	}

	else
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "get_CardsImg_L函数参数越界", "ERROR", MB_ICONERROR);
		return;
	}
}

static Card cardsIfo[plantCount]; //信息数组
int get_cardsIfo_price(int _i)
{
	if (_i < plantCount) {
		return cardsIfo[_i].cardPrice;
	}

	else
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "get_cardsIfo_price函数参数越界", "ERROR", MB_ICONERROR);
		return NULL;
	}
}

int get_cardsIfo_color(int _i)
{
	if (_i < plantCount) {
		return cardsIfo[_i].cardColor;
	}

	else
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "get_cardsIfo_color函数参数越界", "ERROR", MB_ICONERROR);
		return NULL;
	}
}

int get_cardsIfo_anImgNum(int _i)
{
	if (_i < plantCount) {
		return cardsIfo[_i].anImgNum;
	}

	else
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "get_cardsIfo_anImgNum函数参数越界", "ERROR", MB_ICONERROR);
		return NULL;
	}
}

static IMAGE animateGroup[plantCount][MAXANIMATENUM_IN_GROUP]; // 动画组
void get_anFlame(int _plant, int _frame, IMAGE* _saveimg) // 获得某种植物中的某一帧
{
	if (_plant < plantCount && _frame < get_cardsIfo_anImgNum(_plant)) { // 如果访问的不越界
		memcpy_s(_saveimg, sizeof(IMAGE), &animateGroup[_plant][_frame], sizeof(IMAGE));
	}

	else
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "get_animateGroup_forOnePlant函数的参数越界", "ERROR", MB_ICONERROR);
		return;
	}
}


void loadCardInfo()
{
	/***********************卡牌图片加载***************************/

	for (int i = 0; i < plantCount; i++){ // 加载所有植物图片
		loadimage(&CardsImg[i], "PNG", MAKEINTRESOURCE(cards_0_png + i));
	}

	for (int i = 0; i < plantCount; i++){ // 加载所有植物图片_大
		loadimage(&CardsImg_L[i], "PNG", MAKEINTRESOURCE(cards_0_L_png + i));
	}


	/***********************卡牌初始化***************************/
	/*peashootersingle*/
	cardsIfo[peashootersingle].cardColor = green;
	cardsIfo[peashootersingle].cardPrice = 100;
	cardsIfo[peashootersingle].anImgNum = 25;
	cardsIfo[peashootersingle].anBeginImgNum = IDB_PNG1;

	/*sunflower*/
	cardsIfo[sunflower].cardColor = green;
	cardsIfo[sunflower].cardPrice = 50;
	cardsIfo[sunflower].anImgNum = 25;
	cardsIfo[sunflower].anBeginImgNum = IDB_PNG26;

	/************************卡牌动画组加载****************************/

	for (int i = 0; i < plantCount; i++) { // 换植物
		for (int j = 0; j < cardsIfo[i].anImgNum; j++) // 加载牌
		{ 
			if (cardsIfo[i].anImgNum > MAXANIMATENUM_IN_GROUP) // 若动画图片数量大于设定的宏
			{
				HWND hwnd = GetForegroundWindow();
				MessageBox(hwnd, "动画组存储访问越界", "ERROR", MB_ICONERROR);
				return;
			}
			
			// 加载图片到数组
			loadimage(&animateGroup[i][j], "PNG", MAKEINTRESOURCE(cardsIfo[i].anBeginImgNum + j)); 
		}
	}


}