#ifndef CARDS_H
#define CARDS_H

#define FIRSTX_CARD 80         // ��ȹ������ĵ�һ���Ƶ����Ƴ̶�
#define Y_CARD 7               // ������ȹ�������y��ƫ��
#define CARD_WIDTH 50          // �������ڿ��ƿ�ȸ߶�
#define CARD_HEIGHT 70
#define CARD_SPACE 5           // ���Ƽ�ļ��
#define FINALX_BAR 10          // ��������ȴ��ڵ���������
#define BAR_HEIGHT 87          // �������߶ȣ��ж�ֲ���ڵڼ������ˣ�

extern int get_plantChooseNum(); // ���ѡ�˼���ֲ��ȫ�ֱ���
extern int get_plantChoose(int _i); // ���ѡ��ֲ����ʲô˳��_iΪ�ڼ��ſ�������ֵΪֲ��ţ�

/* ��������ʼ������������ѡ����
*  ע�⣺Ŀǰû��ѡ����
*/
void InitCard();

#endif
