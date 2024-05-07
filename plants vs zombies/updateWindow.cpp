/**
* @file：updateWindow.cpp
* @brief：窗口更新，主要用于将植物跟随进入主循环
* @version：施工中
*/

#include <graphics.h>

#include "gameInit.h" // 获取静态背景
#include "moveCard.h" // 获取是否在跟随状态flag
#include "img_processing.h" // 绘图
#include "plantMap.h" // 画已经种下的植物
#include "cardInfo.h" // 获取植物信息

/*宏*/
#define HOLDPLANTBIAS_X -35    // 拿植物的时候大概抓的是叶子部位
#define HOLDPLANTBIAS_Y -68


// 窗口更新
void updateWindow()
{
	/**************************如果是植物跟随状态***********************************/
	IMAGE imgtofollow;
	get_ImgtoFollow(&imgtofollow);
	if (get_follow_statusFlag()){
		draw_blue(get_mousePos_x() + HOLDPLANTBIAS_X, get_mousePos_y() + HOLDPLANTBIAS_Y, imgtofollow);
	}
}