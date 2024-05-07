#ifndef MOVECARD_H
#define MOVECARD_H

#include <graphics.h>

#include "cards.h" // ��ù������߶�

/*��*/
#define ROWHEIGHT 90 // ���ؿ����
#define COLWIDTH 82
#define MARGIN_UP BAR_HEIGHT // �������ҳ�߾�
#define MARGIN_LEFT 30

/*���ȫ�ֱ���*/
void get_ImgtoFollow(IMAGE* _imgtofollow);
bool get_follow_statusFlag();
int get_mousePos_x();
int get_mousePos_y();

void MoveCardModuleInit(); // ��ʼ������������
void load_MoveCardModule(); // ����ѡ��ֲ�����ֲ��ģ��

#endif // !MOVECARD_H

