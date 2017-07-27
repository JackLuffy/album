#include "lcd.h"

lcdinfo *init_lcd(void)
{
	int lcd = open("/dev/fb0", O_RDONLY);
	if(lcd == -1)
	{
		perror("open /dev/fb0 failed");
		return NULL;
	}

	// get info about LCD
	struct fb_var_screeninfo vinfo;
	bzero(&vinfo, sizeof(vinfo));
	ioctl(lcd, FBIOGET_VSCREENINFO, &vinfo);

	lcdinfo *linfo = calloc(1, sizeof(lcdinfo));
	if(linfo == NULL)
	{
		fprintf(stderr, "[] calloc failed: %s\n",
				__LINE__, strerror(errno));
		return NULL;
	}

	linfo->xres = vinfo.xres;
	linfo->yres = vinfo.yres;

	linfo->xres_virtual = vinfo.xres_virtual;
	linfo->yres_virtual = vinfo.yres_virtual;

	linfo->red_offset   = vinfo.red.offset;
	linfo->green_offset = vinfo.green.offset;
	linfo->blue_offset  = vinfo.blue.offset;

	linfo->xoffset = vinfo.xoffset;
	linfo->xoffset = vinfo.xoffset;

	linfo->bpp = vinfo.bits_per_pixel;

	// allocate a double size buffer of size of LCD
	linfo->fbmem = mmap(NULL, linfo->xres * linfo->yres*2 * linfo->bpp/8,
			    PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);

	if(linfo->fbmem == MAP_FAILED)
	{
		perror("mmap() failed");
		free(linfo);
		return NULL;
	}

	return linfo;
}
