#ifndef TRANSPARRENT_H
#define TRANSPARRENT_H

#include <graphics.h>

/* ��������ȡ͸��ͼƬ�زģ�ԭͼƬ����͸�����֣���easyx�л��Զ���Ϊ��ɫ����Ϊ���ȥ����ɫ���֣�
*  ע�⣺ʹ��ǰһ��Ҫ������ȫ��ͬ��image��mask��������ͼƬ
*  ������copyԭͼƬ�����IMAGEָ��
*  ʹ��ʾ����
*       putimage(x, y + shift, img_mask, SRCAND); // ����ȷ����ЧͼƬ��Χ
		putimage(x, y + shift, img, SRCPAINT); // ���ͼƬ����
*/
void getMask_black(IMAGE* Img_Mask);


/* ��������ͼ���кڱߣ�����Ч����ҲΪ��ɫ������Ч�ڱ�Ҳȥ�����ʴ˺���Ϊ������Ϊ����ɫ��mask����
*  ע�⣺ʹ��ǰһ��Ҫ������ȫ��ͬ��image��mask��������ͼƬ
*  ������copyԭͼƬ�����IMAGEָ��
*  ʹ��ʾ����
*       putimage(x, y, &CardsImg_mask, SRCAND); // �Ⱥ�ԭͼ�룬������ͼ�ĵط��ٳ���
		BlueBgToBlackBg(&CardsImg[i]); // ԭͼ���Ϊ�ڱ�������Ч��������ԭͼ��ʱ�Ų���Ӱ��ԭͼ
		putimage(x, y, &CardsImg, SRCPAINT); // �ٻ򣬰���ͼ����
*  ע��: ����ô���½���mask֮�󲻸�ֵ�أ��������µĺ�����
*/
void getMask_blue(IMAGE* Img_Mask);

/*��ɫ����mask*/
void getMask_white(IMAGE* Img_Mask);

/* ��������ԭ����ͼƬ͸�����ֱ�Ϊ��ɫ����
*  ע�⣺ʹ�ú�ԭͼ��
*  ������ԭͼָ��
*/
void BlueBgToBlackBg(IMAGE* Img);

/*��ɫ�������ɫ*/
void WhiteBgToBlackBg(IMAGE* Img);

#endif 

