/**
* @file: plantMap.cpp
* @brief: ��ǰֲ��ֲ�
* @date: 2024.5.3
*/

#include <string.h> // ��memset

#include "plantMap.h"
#include "moveCard.h" // �������ֲ���־����������
#include "cardInfo.h" // �������ͼƬ����
#include "img_processing.h"
#include "gameInit.h" // ��ȡ�ָ�����

/*��*/
#define PLANTINGBIAS_X 0 // ��ֲ����ȸ������Ͻǵ���ͼƫ��
#define PLANTINGBIAS_Y 0
#define SLOWLOOPSCALE 30 // ��������������10�β���һ����ִ�У�

/*ȫ�ֱ���*/
plantStat plot_map[5][9];

static int NumtoAdd = 0; // ���ڷ�Ƶ
static int loop = 0;

/*��������*/
void update_Planting();

void clearPlot() // ����ȫ�գ�ֲ�����಻����
{ 
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 9; j++)
		{
			plot_map[i][j].isPlanted = 0;
			plot_map[i][j].plantType = -1;
			plot_map[i][j].currentFrame = 0;
		}
	}

	loop = 0;
}

void planting()
{
	loop++;
	NumtoAdd = 0;

	if (loop > SLOWLOOPSCALE)  // ��Ƶ��
	{
		loop = 0;
		NumtoAdd = 1;
	}

	/*****************************��Ⱦ�����ֲ��********************************/

	update_Planting(); // ����ֲ��

}

void update_Planting()
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++)
		{
			if (plot_map[i][j].plantType >= 0) // �˴���ֲ��
			{
				int whichPlant = plot_map[i][j].plantType; // ����ֲ��
				int frameNum = get_cardsIfo_anImgNum(whichPlant); // �����ܹ�����֡

				plot_map[i][j].isPlanted = true; // ��Ǵ˴�������ֲ��

				IMAGE* anImg_p = (IMAGE*)malloc(sizeof(IMAGE)); // ����һ��IMAGE�ĵط�
				if (anImg_p == NULL || whichPlant < 0) // Ҫ��û���������ֲ�����
				{
					HWND hwnd = GetForegroundWindow();
					MessageBox(hwnd, "��̬�ڴ�anImg_p�����ֲ���������", "ERROR", MB_ICONERROR);
					return;
				}
				else {
					memset(anImg_p, 0, sizeof(IMAGE)); // ��ʼ��
				}

				get_anFlame(whichPlant, plot_map[i][j].currentFrame % frameNum, anImg_p); // ��ö���ͼƬ
				plot_map[i][j].currentFrame += NumtoAdd;

				static int co_x, co_y; // �����ص����Ͻ�����

				co_x = MARGIN_LEFT + j * COLWIDTH;
				co_y = MARGIN_UP + i * ROWHEIGHT;

				draw_blue(co_x + PLANTINGBIAS_X, co_y + PLANTINGBIAS_Y, *anImg_p); //��ͼ

				free(anImg_p);
				anImg_p = NULL;				
			}

		}
	}
}


//bool hasPlant() // ���ȫͼ�Ƿ���ֲ��
//{
//	for (int i = 0; i < 5; i++) {
//		for (int j = 0; j < 9; j++) {
//			if (plot_map[i][j].isPlanted) {
//				return true;
//			}
//		}
//	}
//
//	return false;
//}


