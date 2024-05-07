#ifndef PLANTMAP_H
#define PLANTMAP_H

// 变量类型定义
typedef struct PLANTSTATUS
{
	bool isPlanted; // 是否已经有植物了
	int plantType;
	int currentFrame; // 当前帧
}plantStat;

/*全局变量*/
extern plantStat plot_map[5][9]; // 这个是真的许多文件可能都要改的全局变量


void clearPlot(); // 初始化
void planting(); // 渲染种下的植物

#endif // !PLANTMAP_H



