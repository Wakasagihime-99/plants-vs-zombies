/**
* @file: cardInfo.cpp
* @brief: 1������ֲ�￨��ͼƬԤ���ء�
*         2��������Ϣ��ʼ����ʹ�����Զ����Card�ṹ�壬��ͷ�ļ��У�
*         3�����ƶ�����ʼ��
*/


#include <windows.h> 
#include <stdio.h>
#include <graphics.h>

#include "cardInfo.h"
#include "resource.h"

// �ҵ������ŷ��������ǲ�̫����������ps�����
/*****************************ȫ�ֱ���******************************************/

static IMAGE CardsImg[plantCount]; // ���ֲ�￨�ƣ�plants=0��Cards[0]
void get_CardsImg(int _i, IMAGE* _saveimg)
{
	if (_i < plantCount) {
		memcpy_s(_saveimg, sizeof(IMAGE), &CardsImg[_i], sizeof(IMAGE));
	}

	else
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "get_CardsImg��������Խ��", "ERROR", MB_ICONERROR);
		return;
	}
}

static IMAGE CardsImg_L[plantCount]; // 80xp��ֲ��ͼ
void get_CardsImg_L(int _i, IMAGE* _saveimg)
{
	if (_i < plantCount) {
		memcpy_s(_saveimg, sizeof(IMAGE), &CardsImg_L[_i], sizeof(IMAGE));
	}

	else
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "get_CardsImg_L��������Խ��", "ERROR", MB_ICONERROR);
		return;
	}
}

static Card cardsIfo[plantCount]; //��Ϣ����
int get_cardsIfo_price(int _i)
{
	if (_i < plantCount) {
		return cardsIfo[_i].cardPrice;
	}

	else
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "get_cardsIfo_price��������Խ��", "ERROR", MB_ICONERROR);
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
		MessageBox(hwnd, "get_cardsIfo_color��������Խ��", "ERROR", MB_ICONERROR);
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
		MessageBox(hwnd, "get_cardsIfo_anImgNum��������Խ��", "ERROR", MB_ICONERROR);
		return NULL;
	}
}

static IMAGE animateGroup[plantCount][MAXANIMATENUM_IN_GROUP]; // ������
void get_anFlame(int _plant, int _frame, IMAGE* _saveimg) // ���ĳ��ֲ���е�ĳһ֡
{
	if (_plant < plantCount && _frame < get_cardsIfo_anImgNum(_plant)) { // ������ʵĲ�Խ��
		memcpy_s(_saveimg, sizeof(IMAGE), &animateGroup[_plant][_frame], sizeof(IMAGE));
	}

	else
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "get_animateGroup_forOnePlant�����Ĳ���Խ��", "ERROR", MB_ICONERROR);
		return;
	}
}


void loadCardInfo()
{
	/***********************����ͼƬ����***************************/

	for (int i = 0; i < plantCount; i++){ // ��������ֲ��ͼƬ
		loadimage(&CardsImg[i], "PNG", MAKEINTRESOURCE(cards_0_png + i));
	}

	for (int i = 0; i < plantCount; i++){ // ��������ֲ��ͼƬ_��
		loadimage(&CardsImg_L[i], "PNG", MAKEINTRESOURCE(cards_0_L_png + i));
	}


	/***********************���Ƴ�ʼ��***************************/
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

	/************************���ƶ��������****************************/

	for (int i = 0; i < plantCount; i++) { // ��ֲ��
		for (int j = 0; j < cardsIfo[i].anImgNum; j++) // ������
		{ 
			if (cardsIfo[i].anImgNum > MAXANIMATENUM_IN_GROUP) // ������ͼƬ���������趨�ĺ�
			{
				HWND hwnd = GetForegroundWindow();
				MessageBox(hwnd, "������洢����Խ��", "ERROR", MB_ICONERROR);
				return;
			}
			
			// ����ͼƬ������
			loadimage(&animateGroup[i][j], "PNG", MAKEINTRESOURCE(cardsIfo[i].anBeginImgNum + j)); 
		}
	}


}