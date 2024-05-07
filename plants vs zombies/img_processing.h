#ifndef IMG_PROCESSING_H
#define IMG_PROCESSING_H

#include <graphics.h>

/* 
* @brief ʹͼƬ�����ƶ�
* 
* @param _x: ���ͼƬ��x���꣨���أ�
* @param _y: ��ʼ�ƶ�ʱ��y����
* @param _final_y�������ƶ�ʱ��y����
* @param _sleepTime��ÿ���ƶ���ȴ�ʱ�䣨ms��
* @param _stride��ͼƬÿ���ƶ��Ĳ�Ƶ�����أ�
* @param _img���ƶ���ͼƬ
* @param _restoreImg: �ָ�ͼƬ
* 
* @attention _isblackbg��Ĭ��Ϊ������
*  
*/
void ImgRiseorDown(int _x, int _y, int _final_y, int _sleepTime, int _stride, IMAGE _img, IMAGE _restoreImg);

/** 
* @brief ͸������������ɫ������ͼƬ
*  
* @param _x: �����ͼƬ��x���꣨pixel��
* @param _y: �����ͼƬ��y���꣨pixel��
* @param _img: �����ͼƬ����ͼƬ����ָ�룬�������Ա����޸�ԭ���棩
*/
void draw_blue(int _x, int _y, IMAGE _img);

/**
* @brief ͸���������ƺ�ɫ������ͼƬ
*
* @param _x: �����ͼƬ��x���꣨pixel��
* @param _y: �����ͼƬ��y���꣨pixel��
* @param _img: �����ͼƬ����ͼƬ����ָ�룬�������Ա����޸�ԭ���棩
*/
void draw_black(int _x, int _y, IMAGE _img);

/**
* @brief ͸���������ư�ɫ������ͼƬ
*
* @param _x: �����ͼƬ��x���꣨pixel��
* @param _y: �����ͼƬ��y���꣨pixel��
* @param _img: �����ͼƬ����ͼƬ����ָ�룬�������Ա����޸�ԭ���棩
*/
void draw_white(int _x, int _y, IMAGE _img);

#endif