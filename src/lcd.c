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
	static lcd_info lcdinfo;

	if((lcdinfo.fd=open("/dev/fb0", O_RDWR)) == -1)
	{
		perror("open /dev/fb0 failed");
		exit(0);
	}

	// get info about LCD
	bzero(&lcdinfo.vinfo, sizeof(lcdinfo.vinfo));
	ioctl(lcdinfo.fd, FBIOGET_VSCREENINFO, &lcdinfo.vinfo);

#ifdef DEBUG
	printf("xres: %d\n", lcdinfo.vinfo.xres);
	printf("yres: %d\n", lcdinfo.vinfo.yres);

	printf("xres_v: %d\n", lcdinfo.vinfo.xres_virtual);
	printf("yres_v: %d\n", lcdinfo.vinfo.yres_virtual);

	printf("bpp: %d\n", lcdinfo.vinfo.bits_per_pixel);

	printf("xoffset: %d\n", lcdinfo.vinfo.xoffset);
	printf("yoffset: %d\n", lcdinfo.vinfo.yoffset);
#endif

	int row_size = lcdinfo.vinfo.xres * lcdinfo.vinfo.bits_per_pixel/8;
	int frm_size = row_size * lcdinfo.vinfo.yres;

	// allocate a double size buffer of size of LCD
	lcdinfo.fbmem = mmap(NULL, 2 * frm_size, PROT_READ | PROT_WRITE,
			     MAP_SHARED, lcdinfo.fd, 0);
	if(lcdinfo.fbmem == MAP_FAILED)
	{
		perror("mmap() failed");
		exit(0);
	}

	bzero(lcdinfo.fbmem, 2 * frm_size);
	return &lcdinfo;
}
