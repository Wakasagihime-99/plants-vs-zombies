#ifndef PLANTMAP_H
#define PLANTMAP_H

// �������Ͷ���
typedef struct PLANTSTATUS
{
	bool isPlanted; // �Ƿ��Ѿ���ֲ����
	int plantType;
	int currentFrame; // ��ǰ֡
}plantStat;

/*ȫ�ֱ���*/
extern plantStat plot_map[5][9]; // ������������ļ����ܶ�Ҫ�ĵ�ȫ�ֱ���


void clearPlot(); // ��ʼ��
void planting(); // ��Ⱦ���µ�ֲ��

#endif // !PLANTMAP_H



