/**
* @file��cards.cpp
* @brief����Ϸ���Ƴ�ʼ��
* @date: 2024.5.3
*/

#include <stdio.h> // ����sprintf_s
#include <graphics.h>

#include "img_processing.h" // ����ͼ��
#include "characters.h" // ����
#include "cardInfo.h" // ������Ϣ
#include "cards.h" // �Ѳ���defineŲ��ͷ�ļ���
#include "gameInit.h" // ���ڻ�ô��ڴ�С
#include "resource.h" // ���ڼ���ͼƬ


#define PLANTTOCARDBIAS_X 4    // ֲ����ȿ��Ƶ�ɫ��ƫ��
#define PLANTTOCARDBIAS_Y 10

#define BARDESCEND_SLEEPTIME 1 // ���������µ�����sleeptime
#define BARDESCEND_STRIDE 10   // ���������µ����Ĳ���
#define PRICETOCARDBIAS_X 12   // ��ȵ�һ���ƣ���һ��price�����Ƴ̶�
#define PRICETOCARDBIAS_Y 48
#define TWOBITSPACE 5 // ��λ���۸�ȫ

/*ȫ�ֱ���*/
static int plantChooseNum; // ѡ�˼�����
int get_plantChooseNum(){
	return plantChooseNum;
}

static int plantChoose[10]; // ѡ���ļ���ֲ�����˳��Ϊ����˳������ֵΪ���ţ�
int get_plantChoose(int _i) 
{
	if (_i < 10) {
		return plantChoose[_i];
	}

	else
	{
		HWND hwnd = GetForegroundWindow();
		MessageBox(hwnd, "get_plantChoose��������Խ��", "ERROR", MB_ICONWARNING);
		return NULL;
	}
}


void InitCard()
{
	loadCardInfo(); // ���ؿ�����Ϣ

	/***********************�����ز�ͼƬ***************************/

	IMAGE Bar; // ������
	loadimage(&Bar, "PNG", MAKEINTRESOURCE(bar_png)); // ���ص�����

	IMAGE Seeds; // ���ؿ��Ƶ�ɫͼƬ
	loadimage(&Seeds, "PNG", MAKEINTRESOURCE(seeds_png));

	IMAGE res_img; // ���ؿ���ʱ�Ļָ�ͼ��
	getimage(&res_img, 0, 0, WIN_WIDTH, WIN_HEIGHT);

	/**************************δ���ļٹ���*****************************/
	// �Ժ�϶�Ҫ����ʼ��

	plantChooseNum = plantCount; // ��ʱû��ѡ������
	//plantChoose[0] = _sunflower; // ֻ���ȸ�ֵ���������������
	//plantChoose[1] = _peashootersingle;

	plantChoose[0] = peashootersingle;
	plantChoose[1] = sunflower;

	/***********************��������ͼ*************************/

	SetWorkingImage(&Bar); // ���ù�����Ϊ��ǰ��ͼĿ��

	for (int i = 0; i < plantChooseNum; i++) // ���ƻ���ȥ
	{
		putimage(FIRSTX_CARD + i * (CARD_WIDTH + CARD_SPACE), Y_CARD, CARD_WIDTH, CARD_HEIGHT,
			&Seeds, get_cardsIfo_color(plantChoose[i]) * CARD_WIDTH, 0); // ������
		
		IMAGE* imgtoDraw_p = (IMAGE*)malloc(sizeof(IMAGE)); // ����һ��IMAGE�ĵط�
		if (imgtoDraw_p == NULL) // Ҫ��û�������
		{
			HWND hwnd = GetForegroundWindow();
			MessageBox(hwnd, "��̬�ڴ�imgtoDraw_p�������", "ERROR", MB_ICONERROR);
			return;
		}
		else {
			memset(imgtoDraw_p, 0, sizeof(IMAGE));
		}

		get_CardsImg(plantChoose[i], imgtoDraw_p);
		draw_blue(FIRSTX_CARD + i * (CARD_WIDTH + CARD_SPACE) + PLANTTOCARDBIAS_X, // �����ϵ�ֲ��
			Y_CARD + PLANTTOCARDBIAS_Y, *imgtoDraw_p);

		if (get_cardsIfo_price(plantChoose[i]) < 100){ // ��ӡ�۸���λ�����Ҷ���
			printNum(Pico129, get_cardsIfo_price(plantChoose[i]), FIRSTX_CARD + i * (CARD_WIDTH + CARD_SPACE) + PRICETOCARDBIAS_X + TWOBITSPACE, // ��ӡ�۸�
				Y_CARD + PRICETOCARDBIAS_Y);
		}

		else { // ��λ��������
			printNum(Pico129, get_cardsIfo_price(plantChoose[i]), FIRSTX_CARD + i * (CARD_WIDTH + CARD_SPACE) + PRICETOCARDBIAS_X, // ��ӡ�۸�
				Y_CARD + PRICETOCARDBIAS_Y);
		}
		
		free(imgtoDraw_p); // �ͷ��ڴ�
		imgtoDraw_p = NULL;
	}

	SetWorkingImage(); // ��ǰ��ͼĿ������ͨ��ͼ����

	ImgRiseorDown(FINALX_BAR, -Bar.getheight(), 0, BARDESCEND_SLEEPTIME, BARDESCEND_STRIDE, Bar, res_img); // ����������
}


