/**
* @file：moveCard.cpp
* @brief：移动植物相关的鼠标信息
*/

#include <graphics.h>

#include "cards.h" // 要用牌的位置
#include "img_processing.h" // 要移动牌
#include "cardInfo.h"
#include "moveCard.h"
#include "updateWindow.h"
#include "plantMap.h"


/*全局变量*/
static bool follow_statusFlag; // 是否进入跟随状态
bool get_follow_statusFlag() {
	return follow_statusFlag;
}

static int mousePos_x, mousePos_y;
int get_mousePos_x() {
	return mousePos_x;
}
int get_mousePos_y() {
	return mousePos_y;
}

static IMAGE ImgtoFollow;
void get_ImgtoFollow(IMAGE* _imgtofollow) {
	*_imgtofollow = ImgtoFollow;
}


/*全局变量（但是确实只这个文件用）*/
static int whichPlant; // 哪个植物
static int loopNum = 0; // 循环次数

// 清一清乱七八糟的
void MoveCardModuleInit()
{
	/*清空变量*/
	follow_statusFlag = false;
	mousePos_x = 0;
	mousePos_y = 0;
	whichPlant = -1;
	loopNum = 0;
	memset(&ImgtoFollow, 0, sizeof(IMAGE));
	flushmessage(); // 清空鼠标消息缓存区
}


void load_MoveCardModule()
{
	ExMessage mouseMeg; // 鼠标按键信息

	if (peekmessage(&mouseMeg, EX_MOUSE)) // 如果获取到消息
	{
		/*************************如果左键按下且之前没拿植物*******************************/

		if (mouseMeg.message == WM_LBUTTONDOWN && !follow_statusFlag) // 如果左键按下，且没有拿植物
		{
			int cardList_n; // 是点的第几张卡
			int plantChooseNum = get_plantChooseNum(); // 总共选了几张卡

			for (cardList_n = 0; cardList_n < plantChooseNum; cardList_n++) // 判断鼠标点击位置
			{
				if (mouseMeg.x >= FINALX_BAR + FIRSTX_CARD + (CARD_WIDTH + CARD_SPACE) * cardList_n  // 在卡牌范围内
					&& mouseMeg.x <= FINALX_BAR + FIRSTX_CARD + (CARD_WIDTH + CARD_SPACE) * cardList_n + CARD_WIDTH
					&& mouseMeg.y >= Y_CARD && mouseMeg.y <= Y_CARD + CARD_HEIGHT)
				{
					follow_statusFlag = true; // 进入植物跟随鼠标状态

					/*********************判断选择的植物，赋值跟随的图片************************/

					whichPlant = get_plantChoose(cardList_n); // 这个位置的卡是什么植物
					get_CardsImg_L(whichPlant, &ImgtoFollow);


					break; // 跳出循环，不必再判断了
				}
			}

			peekmessage(&mouseMeg, EX_MOUSE);
			while (mouseMeg.message != WM_RBUTTONDOWN && mouseMeg.message != WM_MOUSEMOVE) {
				peekmessage(&mouseMeg, EX_MOUSE); // 忽略非新消息
			}
		}

		/*************************如果左键按下且之前拿到植物*******************************/

		if (mouseMeg.message == WM_LBUTTONDOWN && follow_statusFlag) // 如果左键按下，且拿了植物
		{
			int row = (mouseMeg.y - MARGIN_UP) / ROWHEIGHT; // 计算植物行列（从0开始！）
			int col = (mouseMeg.x - MARGIN_LEFT) / COLWIDTH;

			if (row >= 0 && row < 5 && col >= 0 && col < 9
				&& !plot_map[row][col].isPlanted) // 点击区域在草坪中且点的地方没有植物
			{
				follow_statusFlag = false; // 植物跟随鼠标状态结束
				plot_map[row][col].plantType = whichPlant; // 对土地map进行赋值
			}

			if (row >= 0 && row < 5 && col >= 0 && col < 9
				&& plot_map[row][col].isPlanted) // 点的地方已经有植物自动放弃这次拿的卡
			{
				follow_statusFlag = false;
				whichPlant = -1;
			}
			
			peekmessage(&mouseMeg, EX_MOUSE);
			while (mouseMeg.message != WM_RBUTTONDOWN && mouseMeg.message != WM_MOUSEMOVE) {
				peekmessage(&mouseMeg, EX_MOUSE); // 忽略非新消息
			}

		}

		/****************************如果右键按下***********************************/

		if (mouseMeg.message == WM_RBUTTONDOWN && follow_statusFlag) // 取消选择植物
		{ 
			follow_statusFlag = false;

			peekmessage(&mouseMeg, EX_MOUSE);
			while (mouseMeg.message != WM_LBUTTONDOWN && mouseMeg.message != WM_MOUSEMOVE) {
				peekmessage(&mouseMeg, EX_MOUSE); // 忽略非新消息
			}
		}

		/****************************如果移动鼠标***********************************/

		if (mouseMeg.message == WM_MOUSEMOVE) // 鼠标移动
		{
			mousePos_x = mouseMeg.x;
			mousePos_y = mouseMeg.y;

			peekmessage(&mouseMeg, EX_MOUSE);
			while (mouseMeg.message != WM_LBUTTONDOWN && mouseMeg.message != WM_RBUTTONDOWN
				&& mouseMeg.message != WM_MOUSEMOVE) {
				peekmessage(&mouseMeg, EX_MOUSE); // 这个需要保留WM_MOUSEMOVE
			}
		}

		/****************************其他情况***********************************/
		else
		{
			while (mouseMeg.message != WM_LBUTTONDOWN && mouseMeg.message != WM_RBUTTONDOWN
				&& mouseMeg.message != WM_MOUSEMOVE) {
				peekmessage(&mouseMeg, EX_MOUSE); // 忽略非以上消息
			}
		}
	}
}