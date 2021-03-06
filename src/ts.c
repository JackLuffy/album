///////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  文件: album/src/ts.c
//
//  日期: 2017-9
//  描述: 触摸屏设备的操作
//
//  作者: Vincent Lin (林世霖)  
//  微信公众号：秘籍酷
//
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
///////////////////////////////////////////////////////////

#include "common.h"
#include "ts.h"

int wait4touch(int touch_panel)
{
	struct input_event event;

	int x = 0;
	while(1)
	{
		bzero(&event, sizeof(event));
		read(touch_panel, &event, sizeof(event));	

		// some coordinations from the TP is ready
		if(event.type == EV_ABS)
		{
			x = event.code==ABS_X ? event.value : x;
		}

		// state of TP has changed
		if(event.type == EV_KEY)
		{
			// release the TP
			if(event.code  == BTN_TOUCH &&
		   	   event.value == 0 &&
			   x != 0)
			{
				break;
			}
		}
	}

	return x<400 ? PREV : NEXT;
}
