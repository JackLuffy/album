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
	char *fbmem;

	unsigned long xres;
	unsigned long yres;

	unsigned long xres_virtual;
	unsigned long yres_virtual;

	unsigned long red_offset;
	unsigned long green_offset;
	unsigned long blue_offset;

	unsigned long xoffset;
	unsigned long yoffset;

	unsigned long bpp;
}lcd_info;

lcd_info *init_lcd();

#endif
