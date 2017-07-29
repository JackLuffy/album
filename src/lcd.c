//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  File name: album/src/lcd.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2017-7
//  
//  Description: LCD设备操作
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "lcd.h"

lcd_info *init_lcd(void)
{
	int lcd = open("/dev/fb0", O_RDWR);
	if(lcd == -1)
	{
		perror("open /dev/fb0 failed");
		exit(0);
	}

	// get info about LCD
	struct fb_var_screeninfo vinfo;
	bzero(&vinfo, sizeof(vinfo));
	ioctl(lcd, FBIOGET_VSCREENINFO, &vinfo);

	static lcd_info lcdinfo;

	lcdinfo.xres = vinfo.xres;
	lcdinfo.yres = vinfo.yres;

	lcdinfo.xres_virtual = vinfo.xres_virtual;
	lcdinfo.yres_virtual = vinfo.yres_virtual;

	lcdinfo.red_offset   = vinfo.red.offset;
	lcdinfo.green_offset = vinfo.green.offset;
	lcdinfo.blue_offset  = vinfo.blue.offset;

	lcdinfo.xoffset = vinfo.xoffset;
	lcdinfo.yoffset = vinfo.yoffset;

	lcdinfo.bpp = vinfo.bits_per_pixel;

#ifdef DEBUG
	printf("xres: %d\n", lcdinfo.xres);
	printf("yres: %d\n", lcdinfo.yres);

	printf("xres_v: %d\n", lcdinfo.xres_virtual);
	printf("yres_v: %d\n", lcdinfo.yres_virtual);

	printf("bpp: %d\n", lcdinfo.bpp);

	printf("xoffset: %d\n", lcdinfo.xoffset);
	printf("yoffset: %d\n", lcdinfo.yoffset);
#endif

	// allocate a double size buffer of size of LCD
	lcdinfo.fbmem = mmap(NULL, lcdinfo.xres * lcdinfo.yres * lcdinfo.bpp/8,
			    PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);

	if(lcdinfo.fbmem == MAP_FAILED)
	{
		perror("mmap() failed");
		exit(0);
	}

	return &lcdinfo;
}
