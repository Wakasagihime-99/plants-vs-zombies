/* 
*  @date：2024.4.12
*  @version：
*		0.0.1 安装好EasyX并使用。真好玩，嘿嘿嘿。
*       0.1.0 完成了背景左右平移，并完成了导航栏和卡牌。明天该实装导航栏向下平移了。
*       0.1.1 在移动导航栏前，因cards函数报使用栈过多，正在查看如何动态分配内存
*             呃，不是很成功...感觉好麻烦，干脆还是数组了，你受着吧.jpg
*       0.1.2 先把图片加载到导航栏，再绘制到背景上
*             把图片移动的模块独立出来，背景那个移动图片显示部位而不是移动图片本身就不动了
*       0.1.3 实现导航栏向下移动。解决了移动时删除上一次轨迹的问题（把收到影响的区域截图下来，每次盖一下）
*             该实装字体了。重新整理了注释...
*             字体倒是有一些能用了，但是感觉可能计算不过来了。明天还得改善（比如统一再mask），而且现在字做的比较水（
*       0.1.4 谁谁的房子完成了。愿世界再无不等宽字体。卡牌的价格也打好了，de一晚上（
*             开始开发选择植物。
*       0.1.5 植物拿起来了。卡牌加载还没有做。
*       0.1.6 可以放下植物了。之前不清空消息区响应太慢了。试了白色底色来抠图，比蓝色更差（）
*             做到加载植物动画组了。希望把cardInfo两个文件注释再修改一下。
*             在捣鼓怎么做release。把图片文件放进整个项目中。
*/





#include "gameInit.h"
#include "moveCard.h"
#include "updateWindow.h"
#include "plantMap.h"


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	gameInit(); // 游戏初始化
	MoveCardModuleInit(); // 模块初始化
	clearPlot(); // 清除土地植物

	while (!GetAsyncKeyState(VK_ESCAPE)) // 按下esc之前循环
	{
		/******************************开始绘图***********************************/

		BeginBatchDraw(); // 开始缓存绘图

		IMAGE BgafterInit = get_BgafterInit(); // 获取原背景
		putimage(0, 0, &BgafterInit); // 铺底，&要求左值，不能直接赋一个表达式

		/***************************待渲染的动态画面*********************************/

		load_MoveCardModule(); // 加载卡牌模块
		updateWindow(); // 更新拿卡牌的动态画面
		planting(); // 更新种下的植物

		/******************************结束绘图***********************************/

		EndBatchDraw(); // 统一输出
	}
	
	closegraph(); // 关闭窗口，结束程序
	return 0;
	
}
