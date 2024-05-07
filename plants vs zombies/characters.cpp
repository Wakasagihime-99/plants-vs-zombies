/**
* @file：characters.cpp
* @brief：打印字体相关操作
* @attention：老函数没有使用draw_blue等
* @version：0.1.6
*/

#include <graphics.h>
#include <string.h> // 用strlen，做字符查找
#include <stdio.h> // 用sprintf

#include "characters.h" // 自己的头文件
#include "resource.h" // 加载字体图片
#include "charInfo.h"
#include "transparrent.h"


/*宏*/
#define SPACELEN 15 // 空格的像素长度

/*函数声明*/
int getcurrentx(int _n, const int* width_group);
void printchar_Num(char c, TypeChoose tp, int n, int _x, int _y, IMAGE* Img);
void printchar(char c, TypeChoose tp, int n, int _x, int _y, IMAGE* Img, IMAGE* Img_Mask);

// 用于加载字体库
void switchCharType(enum TypeChoose _type, IMAGE* _CharMap_p)
{
	switch (_type)  // 选择什么字体就load什么图片
	{
		case HouseofTerror28:
			loadimage(_CharMap_p, "PNG", MAKEINTRESOURCE(char_HouseofTerror28_png));
			break;

		case Pico129:
			loadimage(_CharMap_p, "PNG", MAKEINTRESOURCE(char_Pico129_png));
			break;

		default:
			HWND hwnd = GetForegroundWindow();
			MessageBox(hwnd, "字体选择出错", "ERROR", MB_ICONERROR);
			return;
	}
}


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
void printStr(enum TypeChoose _type, char* _str, int _x, int _y)
{
	IMAGE CharMap; // 字体库map
	switchCharType(_type, &CharMap); // 是什么字体就load什么字体库

	IMAGE CharMap_Mask = CharMap; // 复制一个mask
	getMask_blue(&CharMap_Mask);
	BlueBgToBlackBg(&CharMap); // 已经将图片变回为黑背景！
	
	for (int i = 0; i < strlen(_str); i++) // 打印字体
	{
		char c = _str[i];
		printchar(c, _type, i, _x, _y, &CharMap, &CharMap_Mask);
	}
}

/**
* @brief：打印数字
*
* @param _type：选择的字体
* @param _num：要打的数字
* @param _x：打印起始位置x
* @param _y：打印起始位置y
* @attention: 黑色数字白色背景，因打印植物价格故最长只有5个数字！
*/
void printNum(enum TypeChoose _type, int _num, int _x, int _y)
{
	IMAGE CharMap; // 字体库map
	switchCharType(_type, &CharMap); // 是什么字体就load什么字体库

	char str[5] = { 0 }; //用于存放整数转字符串
	sprintf_s(str, sizeof(str), "%d", _num);

	for (int i = 0; i < strlen(str); i++) // 打印字体
	{
		char c = str[i];
		printchar_Num(c, _type, i, _x, _y, &CharMap);
	}
}


static int width_already; // 已经积累的长度

/** 
* @brief：逐个打印字
* 
* @param _c：打印的字符
* @param _tp：选择的字体
* @param _n：是本字符串中第几个字（从0开始）
* @param _x：第一个字符的起始位置x
* @param _y：第一个字符的起始位置y
* @param Img：传入的字符map（黑背景）
* @param Img_Mask：传入的字符mask
* 
* @attention：传入时已经是黑背景了！
*/
void printchar(char _c, TypeChoose _tp, int _n, int _x, int _y, IMAGE* Img, IMAGE* Img_Mask) 
{
	const char* chartype = p[_tp];               // 选择的字体库
	const int* charwidth = p_width[_tp];         // 选择相应的字体宽度库
	const int* charspacebias = p_spacebias[_tp]; // 选择相应的字体间距偏置库
	
	if (strchr(chartype, _c) == NULL && _c != ' ') // 没找到则报错
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "剩下的字还没实装(...)", "ERROR", MB_ICONWARNING);
		return;
	}

	if (_n == 0) { // 第一个字符则重置
		width_already = 0;
	}

	if (_c == ' '){ // 其实从来没测试过空格
		width_already += SPACELEN;
	}

	if (_c != ' ')
	{
		int list_n = strchr(chartype, _c) - chartype; // 通过指针计算出是map中第几个字（从0开始）
		int current_x = getcurrentx(list_n, charwidth); // 当前字在图片上的x位置
		int current_Width = charwidth[list_n]; // 当前字的宽度

		// x坐标为初始位置加已经走过的距离
		putimage(_x + width_already, _y, current_Width, Img->getheight(), Img_Mask, current_x, 0, SRCAND);
		putimage(_x + width_already, _y, current_Width, Img->getheight(), Img, current_x, 0, SRCPAINT);

		// 更新字符串已经打出了多长了：当前字的宽度加当前字的宽度偏置
		width_already += current_Width + charspacebias[list_n];
	}
	
}


/**
* @brief：逐个打印字
*
* @param _c：打印的字符
* @param _tp：选择的字体
* @param _n：是本字符串中第几个字（从0开始）
* @param _x：第一个字符的起始位置x
* @param _y：第一个字符的起始位置y
* @param Img：传入的字符map（黑字白背景）
*
* @attention：传入时已经是黑字白背景了！
*/
void printchar_Num(char _c, TypeChoose _tp, int _n, int _x, int _y, IMAGE* Img)
{
	const char* chartype = p[_tp];               // 选择的字体库
	const int* charwidth = p_width[_tp];         // 选择相应的字体宽度库
	const int* charspacebias = p_spacebias[_tp]; // 选择相应的字体间距偏置库

	if (strchr(chartype, _c) == NULL && _c != ' ') // 没找到则报错
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "剩下的字还没实装(...)", "ERROR", MB_ICONWARNING);
		return;
	}

	if (_n == 0) { // 第一个字符则重置
		width_already = 0;
	}

	int list_n = strchr(chartype, _c) - chartype; // 通过指针计算出是map中第几个字（从0开始）
	int current_x = getcurrentx(list_n, charwidth); // 当前字在图片上的x位置
	int current_Width = charwidth[list_n]; // 当前字的宽度

	// x坐标为初始位置加已经走过的距离
	putimage(_x + width_already, _y, current_Width, Img->getheight(), Img, current_x, 0, SRCAND);

	// 更新字符串已经打出了多长了：当前字的宽度加当前字的宽度偏置
	width_already += current_Width + charspacebias[list_n];
}


/**
* @brief：获得当前字在图片上的x坐标
* 
* @param _n：当前字是map里的第几个字
* @param width_group：宽度map地址
* 
*/
int getcurrentx(int _n, const int* width_group)
{
	int sum_x = 0; // x坐标计算结果

	if (_n == 0){ // 首字不累计距离
		return 0;
	}

	else
	{
		for (int i = 0; i < _n; i++){
			sum_x += width_group[i];
		}
		return sum_x;
	}
}