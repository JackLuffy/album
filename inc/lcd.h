//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  File name: album/inc/lcd.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2017-7
//  
//  Description: LCD设备操作头文件
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef __LCD_H
#define __LCD_H

#include "common.h"
#include <linux/fb.h>

typedef struct
{
	int fd;
	char *fbmem;
	struct fb_var_screeninfo vinfo;

}lcd_info;

lcd_info *init_lcd();

#endif
