//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  File name: album/src/jpg.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2017-7
//  
//  Description: 对jpg/jpeg图片的处理
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "jpg.h"

bool is_jpg(char *filename)
{
	assert(filename);

	// check the filename contains the specified suffix
	char *tmp1 = strstr(filename, ".jpg");
	char *tmp2 = strstr(filename, ".jpeg");

	if(tmp1 == NULL && tmp2 == NULL)
	{
		return false;	
	}

	if(tmp1 != NULL && strlen(tmp1) > strlen(".jpg") ||
	   tmp2 != NULL && strlen(tmp2) > strlen(".jpeg") )
	{
		return false;
	}

	return true;
}

bool read_jpg(char *jpgname, char *jpgdata, int size)
{
	assert(jpgname);
	assert(jpgdata);

	int fd = open(jpgname, O_RDONLY);
	if(fd == -1)
	{
		fprintf(stderr, "open() %s failed: %s\n",
				 jpgname, strerror(errno));
		return false;
	}

	int n;
	char *tmp = jpgdata;
	while(size > 0)
	{
		while((n=read(fd, tmp, size)) == -1 && errno == EINTR);

		if(n == -1)
		{
			fprintf(stderr, "read() %s failed: %s\n",
					 jpgname, strerror(errno));
			return false;
		}

		size -= n;
		tmp  += n;
	}

	return true;
}

void decompress(filenode *jpg)
{
	assert(jpg);

#ifdef DEBUG
	fprintf(stderr, "decompressing %s ...\n", jpg->name);
#endif

	// get file-info of the jpg
	struct stat finfo;
	bzero(&finfo, sizeof(finfo));
	stat(jpg->name, &finfo);

	// allocate a piece of memory for jpg-data
	char *jpgdata = calloc(1, finfo.st_size);

	read_jpg(jpg->name, jpgdata, finfo.st_size);

	/*
	 ** decompress the jpgdata under JPEG-lib API
	*/
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	jpeg_mem_src(&cinfo, jpgdata, finfo.st_size);


	if(jpeg_read_header(&cinfo, true) != 1)
	{
		fprintf(stderr, "[%d]: jpeg_read_header failed: %s\n",
				 __LINE__, strerror(errno));
		exit(0);
	}

	jpeg_start_decompress(&cinfo);

	jpg->width = cinfo.output_width;
	jpg->height= cinfo.output_height;
	jpg->bpp   = cinfo.output_components*8;

	int row_stride = jpg->width * jpg->bpp/8;

	jpg->rgb = calloc(1, row_stride * jpg->height);

	while(cinfo.output_scanline < cinfo.output_height)
	{
		unsigned char *buffer_array[1];
		buffer_array[0] = jpg->rgb +
				(cinfo.output_scanline) * row_stride;
		jpeg_read_scanlines(&cinfo, buffer_array, 1);
	}

 	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	free(jpgdata);

}


void display(filenode *jpg, lcd_info *lcdinfo)
{
	assert(jpg);
	assert(jpg->rgb);
	assert(lcdinfo);
	assert(lcdinfo->fbmem);

	bzero(lcdinfo->fbmem, lcdinfo->xres * lcdinfo->yres * lcdinfo->bpp/8);

	int xoffset = ((int)lcdinfo->xres - jpg->width ) / 2;
	int yoffset = ((int)lcdinfo->yres - jpg->height) / 2;

	int ele  = MAX(lcdinfo->xres, lcdinfo->yres);
	int step = 0;

	if(xoffset < 0 || yoffset < 0)
	{
		float times = MAX( (float)jpg->width /lcdinfo->xres, 
				   (float)jpg->height/lcdinfo->yres );

		printf("times: %f\n", times);

		if(times >= 2)
		{
			ele = 1;
			step = times;
			printf("1ele:  %d\n", ele);
			printf("1step: %d\n", step);
		}
		else
		{
			step = 1;
			ele = 1/(times-1);
			printf("2ele:  %d\n", ele);
			printf("2step: %d\n", step);
		}

		printf("%f\n", (float)jpg->width/(ele+step) * ele);
		printf("%f\n", (float)jpg->height/(ele+step) * ele);

		//if(xoffset < 0)
			xoffset = ((float)lcdinfo->xres - (float)jpg->width /(ele + step) * ele) / 2;
		//if(yoffset < 0)
			yoffset = ((float)lcdinfo->yres - (float)jpg->height/(ele + step) * ele) / 2;

		printf("xoffset:%d\n", xoffset);
		printf("yoffset:%d\n", yoffset);
	}

	long pos = (lcdinfo->xres * yoffset + xoffset ) * lcdinfo->bpp /8;
	char *FB = lcdinfo->fbmem + pos;

#define RED   0
#define GREEN 1
#define BLUE  2

	long row, column;
	long lcd_offset = 0;
	long rgb_offset = 0;
	long rgb_offset_row = 0;
	long rgb_offset_col = 0;

	long x, y;

	for(row=0,x=0; row<lcdinfo->yres-yoffset && x<jpg->height; row++)
	{
		rgb_offset_row = (jpg->width * x) * jpg->bpp/8;

		for(column=0, y=0; column<lcdinfo->xres-xoffset && y<jpg->width; column++)
		{
			lcd_offset = (lcdinfo->xres*row + column) * lcdinfo->bpp/8;

			rgb_offset_col = y * jpg->bpp/8;
			rgb_offset     = rgb_offset_row + rgb_offset_col;

			memcpy(FB+lcd_offset+lcdinfo->red_offset/8,  jpg->rgb+rgb_offset+RED,  1);
			memcpy(FB+lcd_offset+lcdinfo->green_offset/8,jpg->rgb+rgb_offset+GREEN,1);
			memcpy(FB+lcd_offset+lcdinfo->blue_offset/8, jpg->rgb+rgb_offset+BLUE, 1);

			y++;

			if(column != 0 && column % ele == 0)
				y += step;
		}

		x++;
		if(row != 0 && row % ele == 0)
			x += step;
	}
}
