//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  File name: album/src/ts.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2017-7
//  
//  Description: 触摸屏设备的操作
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

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
