/**
* @file: plantMap.cpp
* @brief: 当前植物分布
* @date: 2024.5.3
*/

#include <string.h> // 用memset

#include "plantMap.h"
#include "moveCard.h" // 将清空拿植物标志放在这里了
#include "cardInfo.h" // 动画组的图片缓存
#include "img_processing.h"
#include "gameInit.h" // 获取恢复背景

/*宏*/
#define PLANTINGBIAS_X 0 // 大植物相比格子左上角的作图偏置
#define PLANTINGBIAS_Y 0
#define SLOWLOOPSCALE 30 // 减慢比例（比如10次才有一次真执行）

/*全局变量*/
plantStat plot_map[5][9];

static int NumtoAdd = 0; // 用于分频
static int loop = 0;

/*函数声明*/
void update_Planting();

void clearPlot() // 土地全空，植物种类不存在
{ 
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 9; j++)
		{
			plot_map[i][j].isPlanted = 0;
			plot_map[i][j].plantType = -1;
			plot_map[i][j].currentFrame = 0;
		}
	}

	loop = 0;
}

void planting()
{
	loop++;
	NumtoAdd = 0;

	if (loop > SLOWLOOPSCALE)  // 分频器
	{
		loop = 0;
		NumtoAdd = 1;
	}

	/*****************************渲染土里的植物********************************/

	update_Planting(); // 更新植物

}

void update_Planting()
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++)
		{
			if (plot_map[i][j].plantType >= 0) // 此处有植物
			{
				int whichPlant = plot_map[i][j].plantType; // 哪种植物
				int frameNum = get_cardsIfo_anImgNum(whichPlant); // 动画总共多少帧

				plot_map[i][j].isPlanted = true; // 标记此处已种有植物

				IMAGE* anImg_p = (IMAGE*)malloc(sizeof(IMAGE)); // 分配一段IMAGE的地方
				if (anImg_p == NULL || whichPlant < 0) // 要是没分配出来或植物错了
				{
					HWND hwnd = GetForegroundWindow();
					MessageBox(hwnd, "动态内存anImg_p分配或植物种类错误", "ERROR", MB_ICONERROR);
					return;
				}
				else {
					memset(anImg_p, 0, sizeof(IMAGE)); // 初始化
				}

				get_anFlame(whichPlant, plot_map[i][j].currentFrame % frameNum, anImg_p); // 获得动画图片
				plot_map[i][j].currentFrame += NumtoAdd;

				static int co_x, co_y; // 该土地的左上角坐标

				co_x = MARGIN_LEFT + j * COLWIDTH;
				co_y = MARGIN_UP + i * ROWHEIGHT;

				draw_blue(co_x + PLANTINGBIAS_X, co_y + PLANTINGBIAS_Y, *anImg_p); //画图

				free(anImg_p);
				anImg_p = NULL;				
			}

		}
	}
}


//bool hasPlant() // 检查全图是否有植物
//{
//	for (int i = 0; i < 5; i++) {
//		for (int j = 0; j < 9; j++) {
//			if (plot_map[i][j].isPlanted) {
//				return true;
//			}
//		}
//	}
//
//	return false;
//}


