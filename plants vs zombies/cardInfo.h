#ifndef CARDINFO_H
#define CARDINFO_H

/*****************************type����*******************************/

// ö�������Զ�count�ж���ֲ�￨�ƣ�plantsΪ��������
enum PLANT
{
	peashootersingle,
	sunflower,
	plantCount
}; 

// ���忨��ɫ��ö��
enum
{
	gray,
	purple,
	green
}; 

// ��¼ÿ�ſ�����ɫ�ͼ۸����Ϣ
typedef struct CARD
{
	int cardColor;
	int cardPrice;
	int anImgNum; // ����������ͼ�м���
	int anBeginImgNum; // ��һ�ŵĺ궨���ַ
} Card; 

/************************��****************************/

#define MAXANIMATENUM_IN_GROUP 40 // ÿ��ֲ��Ķ���������ж���


/***********************��ȡȫ�ֱ�������******************************/

void get_CardsImg(int _i, IMAGE* _saveimg); // ����һ������
void get_CardsImg_L(int _i, IMAGE* _saveimg); // ����һ������
int get_cardsIfo_price(int _i);
int get_cardsIfo_color(int _i);
int get_cardsIfo_anImgNum(int _i);

/** 
* @brief: ��ö������е�ĳһ֡
* 
* @param _plant: ����ֲ��
* @param _frame: ��һ֡
* @param _saveimg: ���ڴ洢��IMAGE�ĵ�ַ
*/
void get_anFlame(int _plant, int _frame, IMAGE* _saveimg);

/*************************����************************************/

void loadCardInfo(); // ������Ϣ����

#endif
