#ifndef CHARACTERS_H
#define CHARACTERS_H

//字体类型枚举
enum TypeChoose {
	HouseofTerror28,
	Pico129
}; 

/**
* @brief：打印字符串
*
* @param _type：选择的字体
* @param _str：要打的字符串
* @param _x：打印起始位置x
* @param _y：打印起始位置y
*
* @attention: 默认字体为蓝色背景
*
*/
void printStr(enum TypeChoose _type, char* _str, int _x, int _y);

/**
* @brief：打印数字
*
* @param _type：选择的字体
* @param _num：要打的数字
* @param _x：打印起始位置x
* @param _y：打印起始位置y
* @attention: 黑色数字白色背景，因打印植物价格故最长只有5个数字！
*/
void printNum(enum TypeChoose _type, int _num, int _x, int _y);


#endif
