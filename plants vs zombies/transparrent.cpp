/**
* @file: transparrent.cpp
* @brief: ���ͼƬ����汾
* @date: 2024.4.12 
*/

#include <graphics.h>

#define color_bias 100

void getMask_black(IMAGE* Img_Mask)
{
	int width = Img_Mask->getwidth(); // ָ������������ȡͼƬ����
	int height = Img_Mask->getheight();

	int n = 0; // ���Դ����n������
	DWORD* src = GetImageBuffer(Img_Mask); // ��ȡ����ͼƬ���Դ�ָ�루ֱ�Ӷ��ڴ������

	while (n < width * height) // ������������
	{
		int sr = ((src[n] & 0xff0000) >> 16); // ��ȡRGB���R
		int sg = ((src[n] & 0xff00) >> 8);    // G
		int sb = src[n] & 0xff;               // B

		if (sr <= color_bias && sg <= color_bias && sb <= color_bias) { // �����Ǻ�ɫ
			src[n] = 0xffffff; // �����Ϊ��ɫ
		}

		else {
			src[n] = 0; // �������Ϊ��ɫ
		}

		n++;
	}

}

void getMask_blue(IMAGE* Img_Mask) // ͸������Ϊ������
{
	int width = Img_Mask->getwidth(); // ָ������������ȡͼƬ����
	int height = Img_Mask->getheight();

	int n = 0; // ���Դ����n������
	DWORD* src = GetImageBuffer(Img_Mask); // ��ȡ����ͼƬ���Դ�ָ��

	while (n < width * height) // ������������
	{
		int sr = ((src[n] & 0xff0000) >> 16); // ��ȡRGB���R
		int sg = ((src[n] & 0xff00) >> 8);    // G
		int sb = src[n] & 0xff;               // B

		if (sr <= color_bias && sg <= color_bias && sb >= 255 - color_bias) { // �Ǵ���ɫ
			src[n] = 0xffffff; // �����Ϊ��ɫ
		}

		else {
			src[n] = 0; // �������Ϊ��ɫ
		}

		n++;
	}

}

void getMask_white(IMAGE* Img_Mask)
{
	int width = Img_Mask->getwidth(); // ָ������������ȡͼƬ����
	int height = Img_Mask->getheight();

	int n = 0; // ���Դ����n������
	DWORD* src = GetImageBuffer(Img_Mask); // ��ȡ����ͼƬ���Դ�ָ�루ֱ�Ӷ��ڴ������

	while (n < width * height) // ������������
	{
		int sr = ((src[n] & 0xff0000) >> 16); // ��ȡRGB���R
		int sg = ((src[n] & 0xff00) >> 8);    // G
		int sb = src[n] & 0xff;               // B

		if (sr >= 255 - color_bias && sg >= 255 - color_bias && sb >= 255 - color_bias) { // ��ɫ
			; // �򲻶�
		}

		else {
			src[n] = 0; // �������Ϊ��ɫ
		}

		n++;
	}

}

void BlueBgToBlackBg(IMAGE* Img) // ���������Ϊ�ڱ���
{
	int width = Img->getwidth(); // ָ������������ȡͼƬ����
	int height = Img->getheight();

	int n = 0; // ���Դ����n������
	DWORD* src = GetImageBuffer(Img); // ��ȡ����ͼƬ���Դ�ָ��

	while (n < width * height)
	{
		int sr = ((src[n] & 0xff0000) >> 16); // ��ȡRGB���R
		int sg = ((src[n] & 0xff00) >> 8);    // G
		int sb = src[n] & 0xff;               // B

		if (sr <= color_bias && sg <= color_bias && sb >= 255 - color_bias) { // ��������ɫ
			src[n] = 0; // �����Ϊ��ɫ
		}

		else {
			; // ���򲻶�
		}

		n++;
	}

}

void WhiteBgToBlackBg(IMAGE* Img) // ���������Ϊ�ڱ���
{
	int width = Img->getwidth(); // ָ������������ȡͼƬ����
	int height = Img->getheight();

	int n = 0; // ���Դ����n������
	DWORD* src = GetImageBuffer(Img); // ��ȡ����ͼƬ���Դ�ָ��

	while (n < width * height)
	{
		int sr = ((src[n] & 0xff0000) >> 16); // ��ȡRGB���R
		int sg = ((src[n] & 0xff00) >> 8);    // G
		int sb = src[n] & 0xff;               // B

		if (sr >= 255 - color_bias && sg >= 255 - color_bias && sb >= 255 - color_bias) { // �����ǰ�ɫ
			src[n] = 0; // �����Ϊ��ɫ
		}

		else {
			; // ����
		}

		n++;
	}

}
