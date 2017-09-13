///////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  文件: album/src/lcd.c
//
//  日期: 2017-9
//  描述: LCD设备操作
//
//  作者: Vincent Lin (林世霖)  
//  微信公众号：秘籍酷
//
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
///////////////////////////////////////////////////////////

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
