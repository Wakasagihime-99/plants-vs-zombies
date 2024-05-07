/**
* @file��moveCard.cpp
* @brief���ƶ�ֲ����ص������Ϣ
*/

#include <graphics.h>

#include "cards.h" // Ҫ���Ƶ�λ��
#include "img_processing.h" // Ҫ�ƶ���
#include "cardInfo.h"
#include "moveCard.h"
#include "updateWindow.h"
#include "plantMap.h"


/*ȫ�ֱ���*/
static bool follow_statusFlag; // �Ƿ�������״̬
bool get_follow_statusFlag() {
	return follow_statusFlag;
}

static int mousePos_x, mousePos_y;
int get_mousePos_x() {
	return mousePos_x;
}
int get_mousePos_y() {
	return mousePos_y;
}

static IMAGE ImgtoFollow;
void get_ImgtoFollow(IMAGE* _imgtofollow) {
	*_imgtofollow = ImgtoFollow;
}


/*ȫ�ֱ���������ȷʵֻ����ļ��ã�*/
static int whichPlant; // �ĸ�ֲ��
static int loopNum = 0; // ѭ������

// ��һ�����߰����
void MoveCardModuleInit()
{
	/*��ձ���*/
	follow_statusFlag = false;
	mousePos_x = 0;
	mousePos_y = 0;
	whichPlant = -1;
	loopNum = 0;
	memset(&ImgtoFollow, 0, sizeof(IMAGE));
	flushmessage(); // ��������Ϣ������
}


void load_MoveCardModule()
{
	ExMessage mouseMeg; // ��갴����Ϣ

	if (peekmessage(&mouseMeg, EX_MOUSE)) // �����ȡ����Ϣ
	{
		/*************************������������֮ǰû��ֲ��*******************************/

		if (mouseMeg.message == WM_LBUTTONDOWN && !follow_statusFlag) // ���������£���û����ֲ��
		{
			int cardList_n; // �ǵ�ĵڼ��ſ�
			int plantChooseNum = get_plantChooseNum(); // �ܹ�ѡ�˼��ſ�

			for (cardList_n = 0; cardList_n < plantChooseNum; cardList_n++) // �ж������λ��
			{
				if (mouseMeg.x >= FINALX_BAR + FIRSTX_CARD + (CARD_WIDTH + CARD_SPACE) * cardList_n  // �ڿ��Ʒ�Χ��
					&& mouseMeg.x <= FINALX_BAR + FIRSTX_CARD + (CARD_WIDTH + CARD_SPACE) * cardList_n + CARD_WIDTH
					&& mouseMeg.y >= Y_CARD && mouseMeg.y <= Y_CARD + CARD_HEIGHT)
				{
					follow_statusFlag = true; // ����ֲ��������״̬

					/*********************�ж�ѡ���ֲ���ֵ�����ͼƬ************************/

					whichPlant = get_plantChoose(cardList_n); // ���λ�õĿ���ʲôֲ��
					get_CardsImg_L(whichPlant, &ImgtoFollow);


					break; // ����ѭ�����������ж���
				}
			}

			peekmessage(&mouseMeg, EX_MOUSE);
			while (mouseMeg.message != WM_RBUTTONDOWN && mouseMeg.message != WM_MOUSEMOVE) {
				peekmessage(&mouseMeg, EX_MOUSE); // ���Է�����Ϣ
			}
		}

		/*************************������������֮ǰ�õ�ֲ��*******************************/

		if (mouseMeg.message == WM_LBUTTONDOWN && follow_statusFlag) // ���������£�������ֲ��
		{
			int row = (mouseMeg.y - MARGIN_UP) / ROWHEIGHT; // ����ֲ�����У���0��ʼ����
			int col = (mouseMeg.x - MARGIN_LEFT) / COLWIDTH;

			if (row >= 0 && row < 5 && col >= 0 && col < 9
				&& !plot_map[row][col].isPlanted) // ��������ڲ�ƺ���ҵ�ĵط�û��ֲ��
			{
				follow_statusFlag = false; // ֲ��������״̬����
				plot_map[row][col].plantType = whichPlant; // ������map���и�ֵ
			}

			if (row >= 0 && row < 5 && col >= 0 && col < 9
				&& plot_map[row][col].isPlanted) // ��ĵط��Ѿ���ֲ���Զ���������õĿ�
			{
				follow_statusFlag = false;
				whichPlant = -1;
			}
			
			peekmessage(&mouseMeg, EX_MOUSE);
			while (mouseMeg.message != WM_RBUTTONDOWN && mouseMeg.message != WM_MOUSEMOVE) {
				peekmessage(&mouseMeg, EX_MOUSE); // ���Է�����Ϣ
			}

		}

		/****************************����Ҽ�����***********************************/

		if (mouseMeg.message == WM_RBUTTONDOWN && follow_statusFlag) // ȡ��ѡ��ֲ��
		{ 
			follow_statusFlag = false;

			peekmessage(&mouseMeg, EX_MOUSE);
			while (mouseMeg.message != WM_LBUTTONDOWN && mouseMeg.message != WM_MOUSEMOVE) {
				peekmessage(&mouseMeg, EX_MOUSE); // ���Է�����Ϣ
			}
		}

		/****************************����ƶ����***********************************/

		if (mouseMeg.message == WM_MOUSEMOVE) // ����ƶ�
		{
			mousePos_x = mouseMeg.x;
			mousePos_y = mouseMeg.y;

			peekmessage(&mouseMeg, EX_MOUSE);
			while (mouseMeg.message != WM_LBUTTONDOWN && mouseMeg.message != WM_RBUTTONDOWN
				&& mouseMeg.message != WM_MOUSEMOVE) {
				peekmessage(&mouseMeg, EX_MOUSE); // �����Ҫ����WM_MOUSEMOVE
			}
		}

		/****************************�������***********************************/
		else
		{
			while (mouseMeg.message != WM_LBUTTONDOWN && mouseMeg.message != WM_RBUTTONDOWN
				&& mouseMeg.message != WM_MOUSEMOVE) {
				peekmessage(&mouseMeg, EX_MOUSE); // ���Է�������Ϣ
			}
		}
	}
}