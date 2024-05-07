/**
* @file img_processing.cpp
* @brief 通用图片处理函数，包括绘图及移动
* @date 2024.5.3
*/

#include <stdlib.h> // 用于计算绝对值
#include <graphics.h>

#include "transparrent.h" // 用于透明化图

void draw_blue(int _x, int _y, IMAGE _img);
void draw_black(int _x, int _y, IMAGE _img);
void draw_white(int _x, int _y, IMAGE _img);

void ImgRiseorDown(int _x, int _y, int _final_y, int _sleepTime, int _stride, IMAGE _img, IMAGE _restoreImg)
{
	int _shift = 0; // 定义一个移动的偏置变量
	if (_final_y == _y) // 始末值相等
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "图像上下移动始末值填写错误", "ERROR", MB_ICONERROR);
		return;
	}

	int _min_y = _final_y - _y > 0 ? _y : _final_y; // 获得一个最小y

	BeginBatchDraw(); // 开始缓存
	while (_shift < abs(_final_y - _y))
	{
		putimage(0, 0, &_restoreImg); // 盖恢复图

		draw_blue(_x, _y + _shift, _img);

		
		FlushBatchDraw(); // 显示
		Sleep(_sleepTime); // 等待

		if (_min_y == _y){ // 若是下降过程
			_shift += _stride; //递增
		}
		
		if (_min_y == _final_y){ // 若是下降过程
			_shift -= _stride; //递减
		}
	}

	// 补上终值位置的，可避免最后一步（stride）时无此值
	putimage(0, 0, &_restoreImg); // 盖恢复图

	draw_blue(_x, _final_y, _img);
	
	EndBatchDraw();
}

// 蓝色背景的绘图函数
void draw_blue(int _x, int _y, IMAGE _img)
{
	IMAGE _img_mask = _img; // 复制一份做掩码图
	getMask_blue(&_img_mask); // 获取掩码图
	putimage(_x, _y, &_img_mask, SRCAND); // 掩码与
	BlueBgToBlackBg(&_img); // 原图转换为黑背景（改变形参，不影响原缓存）
	putimage(_x, _y, &_img, SRCPAINT); // 原图或
}

// 黑色背景的绘图函数
void draw_black(int _x, int _y, IMAGE _img)
{
	IMAGE _img_mask = _img; // 复制一份做掩码图
	getMask_black(&_img_mask); // 获取掩码图
	putimage(_x, _y, &_img_mask, SRCAND); // 掩码与
	putimage(_x, _y, &_img, SRCPAINT); // 原图或
}

// 白色背景的绘图函数
void draw_white(int _x, int _y, IMAGE _img)
{
	IMAGE _img_mask = _img; // 复制一份做掩码图
	getMask_white(&_img_mask); // 获取掩码图
	putimage(_x, _y, &_img_mask, SRCAND); // 掩码与
	WhiteBgToBlackBg(&_img);
	putimage(_x, _y, &_img, SRCPAINT); // 原图或
}