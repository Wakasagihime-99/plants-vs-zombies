#ifndef IMG_PROCESSING_H
#define IMG_PROCESSING_H

#include <graphics.h>

/* 
* @brief 使图片上下移动
* 
* @param _x: 输出图片的x坐标（像素）
* @param _y: 开始移动时的y坐标
* @param _final_y：结束移动时的y坐标
* @param _sleepTime：每次移动后等待时间（ms）
* @param _stride：图片每次移动的步频（像素）
* @param _img：移动的图片
* @param _restoreImg: 恢复图片
* 
* @attention _isblackbg：默认为蓝背景
*  
*/
void ImgRiseorDown(int _x, int _y, int _final_y, int _sleepTime, int _stride, IMAGE _img, IMAGE _restoreImg);

/** 
* @brief 透明化并绘制蓝色背景的图片
*  
* @param _x: 待输出图片的x坐标（pixel）
* @param _y: 待输出图片的y坐标（pixel）
* @param _img: 待输出图片（是图片不是指针，这样可以避免修改原缓存）
*/
void draw_blue(int _x, int _y, IMAGE _img);

/**
* @brief 透明化并绘制黑色背景的图片
*
* @param _x: 待输出图片的x坐标（pixel）
* @param _y: 待输出图片的y坐标（pixel）
* @param _img: 待输出图片（是图片不是指针，这样可以避免修改原缓存）
*/
void draw_black(int _x, int _y, IMAGE _img);

/**
* @brief 透明化并绘制白色背景的图片
*
* @param _x: 待输出图片的x坐标（pixel）
* @param _y: 待输出图片的y坐标（pixel）
* @param _img: 待输出图片（是图片不是指针，这样可以避免修改原缓存）
*/
void draw_white(int _x, int _y, IMAGE _img);

#endif