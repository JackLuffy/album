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
