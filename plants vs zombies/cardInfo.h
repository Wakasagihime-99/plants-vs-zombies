#ifndef CARDINFO_H
#define CARDINFO_H

/*****************************type类型*******************************/

// 枚举类型自动count有多少植物卡牌，plants为变量名称
enum PLANT
{
	peashootersingle,
	sunflower,
	plantCount
}; 

// 定义卡颜色的枚举
enum
{
	gray,
	purple,
	green
}; 

// 记录每张卡的颜色和价格等信息
typedef struct CARD
{
	int cardColor;
	int cardPrice;
	int anImgNum; // 用作动画的图有几张
	int anBeginImgNum; // 第一张的宏定义地址
} Card; 

/************************宏****************************/

#define MAXANIMATENUM_IN_GROUP 40 // 每个植物的动画数最多有多少


/***********************获取全局变量函数******************************/

void get_CardsImg(int _i, IMAGE* _saveimg); // 拷贝一份数组
void get_CardsImg_L(int _i, IMAGE* _saveimg); // 拷贝一份数组
int get_cardsIfo_price(int _i);
int get_cardsIfo_color(int _i);
int get_cardsIfo_anImgNum(int _i);

/** 
* @brief: 获得动画组中的某一帧
* 
* @param _plant: 哪种植物
* @param _frame: 哪一帧
* @param _saveimg: 用于存储该IMAGE的地址
*/
void get_anFlame(int _plant, int _frame, IMAGE* _saveimg);

/*************************函数************************************/

void loadCardInfo(); // 加载信息函数

#endif
