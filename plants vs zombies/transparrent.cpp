/**
* @file: transparrent.cpp
* @brief: 获得图片掩码版本
* @date: 2024.4.12 
*/

#include <graphics.h>

#define color_bias 100

void getMask_black(IMAGE* Img_Mask)
{
	int width = Img_Mask->getwidth(); // 指针调用类变量获取图片长宽
	int height = Img_Mask->getheight();

	int n = 0; // 在显存里第n个像素
	DWORD* src = GetImageBuffer(Img_Mask); // 获取掩码图片的显存指针（直接对内存操作）

	while (n < width * height) // 遍历所有像素
	{
		int sr = ((src[n] & 0xff0000) >> 16); // 获取RGB里的R
		int sg = ((src[n] & 0xff00) >> 8);    // G
		int sb = src[n] & 0xff;               // B

		if (sr <= color_bias && sg <= color_bias && sb <= color_bias) { // 几乎是黑色
			src[n] = 0xffffff; // 则填充为白色
		}

		else {
			src[n] = 0; // 否则填充为黑色
		}

		n++;
	}

}

void getMask_blue(IMAGE* Img_Mask) // 透明部分为蓝背景
{
	int width = Img_Mask->getwidth(); // 指针调用类变量获取图片长宽
	int height = Img_Mask->getheight();

	int n = 0; // 在显存里第n个像素
	DWORD* src = GetImageBuffer(Img_Mask); // 获取掩码图片的显存指针

	while (n < width * height) // 遍历所有像素
	{
		int sr = ((src[n] & 0xff0000) >> 16); // 获取RGB里的R
		int sg = ((src[n] & 0xff00) >> 8);    // G
		int sb = src[n] & 0xff;               // B

		if (sr <= color_bias && sg <= color_bias && sb >= 255 - color_bias) { // 是纯蓝色
			src[n] = 0xffffff; // 则填充为白色
		}

		else {
			src[n] = 0; // 否则填充为黑色
		}

		n++;
	}

}

void getMask_white(IMAGE* Img_Mask)
{
	int width = Img_Mask->getwidth(); // 指针调用类变量获取图片长宽
	int height = Img_Mask->getheight();

	int n = 0; // 在显存里第n个像素
	DWORD* src = GetImageBuffer(Img_Mask); // 获取掩码图片的显存指针（直接对内存操作）

	while (n < width * height) // 遍历所有像素
	{
		int sr = ((src[n] & 0xff0000) >> 16); // 获取RGB里的R
		int sg = ((src[n] & 0xff00) >> 8);    // G
		int sb = src[n] & 0xff;               // B

		if (sr >= 255 - color_bias && sg >= 255 - color_bias && sb >= 255 - color_bias) { // 白色
			; // 则不动
		}

		else {
			src[n] = 0; // 否则填充为黑色
		}

		n++;
	}

}

void BlueBgToBlackBg(IMAGE* Img) // 蓝背景变回为黑背景
{
	int width = Img->getwidth(); // 指针调用类变量获取图片长宽
	int height = Img->getheight();

	int n = 0; // 在显存里第n个像素
	DWORD* src = GetImageBuffer(Img); // 获取掩码图片的显存指针

	while (n < width * height)
	{
		int sr = ((src[n] & 0xff0000) >> 16); // 获取RGB里的R
		int sg = ((src[n] & 0xff00) >> 8);    // G
		int sb = src[n] & 0xff;               // B

		if (sr <= color_bias && sg <= color_bias && sb >= 255 - color_bias) { // 几乎是蓝色
			src[n] = 0; // 则填充为黑色
		}

		else {
			; // 否则不动
		}

		n++;
	}

}

void WhiteBgToBlackBg(IMAGE* Img) // 蓝背景变回为黑背景
{
	int width = Img->getwidth(); // 指针调用类变量获取图片长宽
	int height = Img->getheight();

	int n = 0; // 在显存里第n个像素
	DWORD* src = GetImageBuffer(Img); // 获取掩码图片的显存指针

	while (n < width * height)
	{
		int sr = ((src[n] & 0xff0000) >> 16); // 获取RGB里的R
		int sg = ((src[n] & 0xff00) >> 8);    // G
		int sb = src[n] & 0xff;               // B

		if (sr >= 255 - color_bias && sg >= 255 - color_bias && sb >= 255 - color_bias) { // 几乎是白色
			src[n] = 0; // 则填充为黑色
		}

		else {
			; // 不动
		}

		n++;
	}

}
