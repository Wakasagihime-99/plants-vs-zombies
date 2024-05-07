#ifndef TRANSPARRENT_H
#define TRANSPARRENT_H

#include <graphics.h>

/* 描述：获取透明图片素材（原图片若有透明部分，在easyx中会自动变为黑色，此为如何去除黑色部分）
*  注意：使用前一定要复制完全相同的image，mask操作将损坏图片
*  参数：copy原图片后的新IMAGE指针
*  使用示例：
*       putimage(x, y + shift, img_mask, SRCAND); // 先与确定有效图片范围
		putimage(x, y + shift, img, SRCPAINT); // 后或将图片贴入
*/
void getMask_black(IMAGE* Img_Mask);


/* 描述：因图像有黑边，若无效区域也为黑色将把有效黑边也去掉，故此函数为处理背景为纯蓝色的mask函数
*  注意：使用前一定要复制完全相同的image，mask操作将损坏图片
*  参数：copy原图片后的新IMAGE指针
*  使用示例：
*       putimage(x, y, &CardsImg_mask, SRCAND); // 先和原图与，把填新图的地方抠出来
		BlueBgToBlackBg(&CardsImg[i]); // 原图变回为黑背景，无效区域在与原图或时才不会影响原图
		putimage(x, y, &CardsImg, SRCPAINT); // 再或，把新图填上
*  注意: 你怎么总新建了mask之后不赋值呢，可以用新的函数了
*/
void getMask_blue(IMAGE* Img_Mask);

/*白色背景mask*/
void getMask_white(IMAGE* Img_Mask);

/* 描述：将原函数图片透明部分变为黑色背景
*  注意：使用后原图损坏
*  参数：原图指针
*/
void BlueBgToBlackBg(IMAGE* Img);

/*白色背景变黑色*/
void WhiteBgToBlackBg(IMAGE* Img);

#endif 

