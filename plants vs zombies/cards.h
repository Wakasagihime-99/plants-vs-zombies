#ifndef CARDS_H
#define CARDS_H

#define FIRSTX_CARD 80         // 相比工具栏的第一张牌的右移程度
#define Y_CARD 7               // 底牌相比工具栏的y轴偏移
#define CARD_WIDTH 50          // 工具栏内卡牌宽度高度
#define CARD_HEIGHT 70
#define CARD_SPACE 5           // 卡牌间的间距
#define FINALX_BAR 10          // 工具栏相比窗口的最终右移
#define BAR_HEIGHT 87          // 工具栏高度（判断植物在第几行用了）

extern int get_plantChooseNum(); // 获得选了几个植物全局变量
extern int get_plantChoose(int _i); // 获得选的植物是什么顺序（_i为第几张卡，返回值为植物号）

/* 描述：初始化导航栏及所选卡牌
*  注意：目前没有选择功能
*/
void InitCard();

#endif
