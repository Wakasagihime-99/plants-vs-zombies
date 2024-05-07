#ifndef MOVECARD_H
#define MOVECARD_H

#include <graphics.h>

#include "cards.h" // 获得工具栏高度

/*宏*/
#define ROWHEIGHT 90 // 土地宽与高
#define COLWIDTH 82
#define MARGIN_UP BAR_HEIGHT // 土地外的页边距
#define MARGIN_LEFT 30

/*获得全局变量*/
void get_ImgtoFollow(IMAGE* _imgtofollow);
bool get_follow_statusFlag();
int get_mousePos_x();
int get_mousePos_y();

void MoveCardModuleInit(); // 初始化，变量清零
void load_MoveCardModule(); // 加载选择植物，放下植物模块

#endif // !MOVECARD_H

