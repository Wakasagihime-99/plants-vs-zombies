#ifndef CHARACTERS_H
#define CHARACTERS_H

//��������ö��
enum TypeChoose {
	HouseofTerror28,
	Pico129
}; 

/**
* @brief����ӡ�ַ���
*
* @param _type��ѡ�������
* @param _str��Ҫ����ַ���
* @param _x����ӡ��ʼλ��x
* @param _y����ӡ��ʼλ��y
*
* @attention: Ĭ������Ϊ��ɫ����
*
*/
void printStr(enum TypeChoose _type, char* _str, int _x, int _y);

/**
* @brief����ӡ����
*
* @param _type��ѡ�������
* @param _num��Ҫ�������
* @param _x����ӡ��ʼλ��x
* @param _y����ӡ��ʼλ��y
* @attention: ��ɫ���ְ�ɫ���������ӡֲ��۸���ֻ��5�����֣�
*/
void printNum(enum TypeChoose _type, int _num, int _x, int _y);


#endif
