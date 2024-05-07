/**
* @file��updateWindow.cpp
* @brief�����ڸ��£���Ҫ���ڽ�ֲ����������ѭ��
* @version��ʩ����
*/

#include <graphics.h>

#include "gameInit.h" // ��ȡ��̬����
#include "moveCard.h" // ��ȡ�Ƿ��ڸ���״̬flag
#include "img_processing.h" // ��ͼ
#include "plantMap.h" // ���Ѿ����µ�ֲ��
#include "cardInfo.h" // ��ȡֲ����Ϣ

/*��*/
#define HOLDPLANTBIAS_X -35    // ��ֲ���ʱ����ץ����Ҷ�Ӳ�λ
#define HOLDPLANTBIAS_Y -68


// ���ڸ���
void updateWindow()
{
	/**************************�����ֲ�����״̬***********************************/
	IMAGE imgtofollow;
	get_ImgtoFollow(&imgtofollow);
	if (get_follow_statusFlag()){
		draw_blue(get_mousePos_x() + HOLDPLANTBIAS_X, get_mousePos_y() + HOLDPLANTBIAS_Y, imgtofollow);
	}
}