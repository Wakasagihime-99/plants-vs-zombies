/**
* @file img_processing.cpp
* @brief ͨ��ͼƬ��������������ͼ���ƶ�
* @date 2024.5.3
*/

#include <stdlib.h> // ���ڼ������ֵ
#include <graphics.h>

#include "transparrent.h" // ����͸����ͼ

void draw_blue(int _x, int _y, IMAGE _img);
void draw_black(int _x, int _y, IMAGE _img);
void draw_white(int _x, int _y, IMAGE _img);

void ImgRiseorDown(int _x, int _y, int _final_y, int _sleepTime, int _stride, IMAGE _img, IMAGE _restoreImg)
{
	int _shift = 0; // ����һ���ƶ���ƫ�ñ���
	if (_final_y == _y) // ʼĩֵ���
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "ͼ�������ƶ�ʼĩֵ��д����", "ERROR", MB_ICONERROR);
		return;
	}

	int _min_y = _final_y - _y > 0 ? _y : _final_y; // ���һ����Сy

	BeginBatchDraw(); // ��ʼ����
	while (_shift < abs(_final_y - _y))
	{
		putimage(0, 0, &_restoreImg); // �ǻָ�ͼ

		draw_blue(_x, _y + _shift, _img);

		
		FlushBatchDraw(); // ��ʾ
		Sleep(_sleepTime); // �ȴ�

		if (_min_y == _y){ // �����½�����
			_shift += _stride; //����
		}
		
		if (_min_y == _final_y){ // �����½�����
			_shift -= _stride; //�ݼ�
		}
	}

	// ������ֵλ�õģ��ɱ������һ����stride��ʱ�޴�ֵ
	putimage(0, 0, &_restoreImg); // �ǻָ�ͼ

	draw_blue(_x, _final_y, _img);
	
	EndBatchDraw();
}

// ��ɫ�����Ļ�ͼ����
void draw_blue(int _x, int _y, IMAGE _img)
{
	IMAGE _img_mask = _img; // ����һ��������ͼ
	getMask_blue(&_img_mask); // ��ȡ����ͼ
	putimage(_x, _y, &_img_mask, SRCAND); // ������
	BlueBgToBlackBg(&_img); // ԭͼת��Ϊ�ڱ������ı��βΣ���Ӱ��ԭ���棩
	putimage(_x, _y, &_img, SRCPAINT); // ԭͼ��
}

// ��ɫ�����Ļ�ͼ����
void draw_black(int _x, int _y, IMAGE _img)
{
	IMAGE _img_mask = _img; // ����һ��������ͼ
	getMask_black(&_img_mask); // ��ȡ����ͼ
	putimage(_x, _y, &_img_mask, SRCAND); // ������
	putimage(_x, _y, &_img, SRCPAINT); // ԭͼ��
}

// ��ɫ�����Ļ�ͼ����
void draw_white(int _x, int _y, IMAGE _img)
{
	IMAGE _img_mask = _img; // ����һ��������ͼ
	getMask_white(&_img_mask); // ��ȡ����ͼ
	putimage(_x, _y, &_img_mask, SRCAND); // ������
	WhiteBgToBlackBg(&_img);
	putimage(_x, _y, &_img, SRCPAINT); // ԭͼ��
}