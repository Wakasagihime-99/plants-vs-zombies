/**
*  @file��gameInit.cpp
*  @brief����ʼ����Ϸ���棬Ŀǰ������
*          1�����뱳�������һ�һ�£����޽�ʬԤ����
*          2����ӡ�û����ķ��ӣ���δ�������û�����ʽ��ֻ��ֱ�������︳ֵ��
*          3����ʼ�����ƣ����cards.cppע�ͣ�
*          4����ʼ�����أ����plantMap.cpp��
*  @version:0.1.6
*/

#include <graphics.h> // ����easyX
#include <windows.h> // ����sleep����������ͼ�ꡢλ�õ�

#include "gameInit.h" // �Լ���ͷ�ļ�
#include "characters.h" // ��ӡuser's house
#include "transparrent.h"
#include "cards.h"
#include "img_processing.h"
#include "plantMap.h"
#include "resource.h"

/************************�궨��*****************************/

#define WIN_X 500       // ��Ϸ���ڳ�ʼλ��
#define WIN_Y 250
#define TEXT_X 250      // ˭˭�ķ��ӵ�������ʼλ��
#define TEXT_Y 480
#define FINALX_BG 220   // ����ͼƬ����xλ�ã�������Ϸ������λ�ã�
#define BG_SLEEPTIME 5  // ���������ƶ�ʱ��sleeptime��ms��
#define BG_STRIDE 8     // ���������ƶ�ʱ�Ĳ�����pixel��
#define HOUSEANDZOMBIE_SLEEPTIME 1500 // �����Ӻ�Ԥ����ʬʱ�ĵȴ�ʱ��


/************************ȫ�ֱ���****************************/

static IMAGE BgafterInit; // ���ڻ�����о�̬����ɵı�����ʲô������ˢ�¶�̬�Ķ���ǰά����̬�ı���
                          // static���ڷ���������Ż����Ͳ�extern��ȥЧ����һģһ����

IMAGE get_BgafterInit(){ // ��ȡȫ�ֱ���
	return BgafterInit;
}


/**************************����******************************/

void gameInit() // gameInit�������в���mainѭ����ִ�еĲ���
{
	/*********************���ڳ�ʼ�������뱳��ͼƬ***********************/

	/*��ʼ������*/
	initgraph(WIN_WIDTH, WIN_HEIGHT); // ��ʼ��һ������
	HWND hwnd = GetHWnd(); // ��ȡ���ھ��
	SetWindowPos(hwnd, NULL, WIN_X, WIN_Y, 0, 0, 
		SWP_NOSIZE | SWP_NOZORDER); // ��window API�Ѵ��ڷ��м��

	/*����ͼ���ļ�*/
	HINSTANCE hInstance = GetModuleHandle(NULL); // ��ȡӦ��ʵ�����
	HICON hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(icon), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);

	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon); // ���ô�Сͼ��
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

	/*���ر���ͼƬ*/
	IMAGE BgImg; //����ͼƬ�������ǰ���5����ƺ��
	loadimage(&BgImg, "JPG", MAKEINTRESOURCE(background1_jpg)); // ʹ���˴���Դ��ȡͼ��
	                                                            // MAKEINTRESOURCE��δ��ȷ���ر���ʱ��ֱ�ӱ���
	putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &BgImg, 0, 0); // ���뱳��ͼƬ


	/**************************&{�û���}�ķ���***************************/

	char user[] = "Yoitu's house"; // Ŀǰֱ�Ӹ�ֵ

	printStr(HouseofTerror28, user, TEXT_X, TEXT_Y); // ��ӡ�ַ���
	Sleep(HOUSEANDZOMBIE_SLEEPTIME); // �ȴ�һ��ʱ��


	/**************************����ͼƬ�����ƶ�����***************************/

	int leftShift = 0; // �����ƶ���ֵ
	int Bgimg_width = BgImg.getwidth(); // ��ȡ��������
	int Bgimg_height = BgImg.getheight();

	BeginBatchDraw(); // ��ʼ������ͼ���ɽ����˸����
	while (leftShift < (Bgimg_width - WIN_WIDTH)/2)	// ��Ϸ��ʼʱ��չ�ַ��ӵ�������Ϣ����
	{
		cleardevice(); // �������
		putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &BgImg, leftShift, 0); // ͼƬ�ƶ�
		printStr(HouseofTerror28, user, TEXT_X, TEXT_Y); // ��ӡ�ַ���
		FlushBatchDraw(); // ��ͼ

		Sleep(BG_SLEEPTIME); // �ȴ�

		leftShift += BG_STRIDE;
	}
	EndBatchDraw();

	BeginBatchDraw();
	while (leftShift < Bgimg_width - WIN_WIDTH)	// ������Ϣ�������ƶ������Ҳ࿴��ʬ
	{
		cleardevice();
		putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &BgImg, leftShift, 0);
		FlushBatchDraw();

		Sleep(BG_SLEEPTIME);

		leftShift += BG_STRIDE;
	}
	putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &BgImg, Bgimg_width - WIN_WIDTH, 0); // ���һ�εģ�����©��
	EndBatchDraw(); // ����������ͼ��ͳһ����

	Sleep(HOUSEANDZOMBIE_SLEEPTIME); // �ȴ�һ��ʱ��

	BeginBatchDraw(); // ��ʼ������ͼ���ɽ����˸����
	while (leftShift > FINALX_BG)	// չ�ֽ�ʬ�����ն���׼����ʼ��Ϸ
	{
		cleardevice();
		putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &BgImg, leftShift, 0);
		FlushBatchDraw();

		Sleep(BG_SLEEPTIME);

		leftShift -= BG_STRIDE;
	}

    putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &BgImg, FINALX_BG, 0); // ���һ�εģ�����©��

	EndBatchDraw(); // ����������ͼ��ͳһ����

	/**********************��ʼ������***********************/

	InitCard();

	/**********************��ʼ������***********************/

	clearPlot();

	// ��ʼ���������ȡ��̬ͼ��
	getimage(&BgafterInit, 0, 0, WIN_WIDTH, WIN_HEIGHT); 
}
