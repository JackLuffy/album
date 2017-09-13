///////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  文件: album/album.c
//
//  日期: 2017-9
//  描述: 一个简单的电子相册
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
#include "lcd.h"
#include "jpg.h"

#define LIST_NODE_DATATYPE filenode
#include "list.h"

// global variables
linklist  g_head    = NULL;
lcd_info *g_lcdinfo = NULL; // for signal

char *check_args(int argc, char **argv)
{
	if(argc >= 3)
	{
		fprintf(stderr, "invalid arguments\n");
		fprintf(stderr, "Usage: %s [file][directory]\n", argv[0]);

		exit(0);
	}

	return argc==2 ? argv[1] : ".";
}

void refresh_list(linklist current_jpg)
{
	assert(current_jpg);

	current_jpg->data.CBFB = 10;

	linklist tmp;
	for(tmp=g_head->next; tmp!=g_head; tmp=tmp->next)
	{
		if(tmp == current_jpg)
			continue;

		int count = tmp->data.CBFB - 1;
		tmp->data.CBFB = count > 0 ? count : 0;

		if(tmp->data.CBFB == 0 && tmp->data.rgb != NULL)
		{
#ifdef DEBUG
			printf("freeing %s ...\n", tmp->data.name);
#endif
			free(tmp->data.rgb);
			tmp->data.rgb = NULL;
		}
	}
}

linklist show_jpg(linklist list, int action, lcd_info *lcdinfo)
{
	assert(list);
	assert(lcdinfo);

	switch(action)
	{
	case CURRENT:
		list = list;
		break;

	case PREV:
		if(list->prev == g_head)
		{
			fprintf(stderr, "this is the first list.\n");	
			return list;
		}
		list = list->prev;
		break;

	case NEXT:
		if(list->next == g_head)
		{
			fprintf(stderr, "this is the last list.\n");	
			return list;
		}
		list = list->next;
		break;
	}

	// check is there any rgb-buffer can be free
	refresh_list(list);

	filenode *jpg = &list->data;

	decompress(jpg);
	display(jpg, lcdinfo);

	return list;
}

linklist newnode(char *jpgname)
{
	assert(jpgname);

	linklist new = calloc(1, sizeof(listnode));
	if(new == NULL)
	{
		fprintf(stderr, "[%d] calloc() failed: %s\n",
				 __LINE__, strerror(errno));
		return NULL;
	}

	filenode *tmp = &new->data;

	tmp->name  = jpgname;
	tmp->rgb   = NULL;

	tmp->width = 0;
	tmp->height= 0;
	tmp->bpp   = 0;

	tmp->CBFB = 0; // Count Backwards to Free RGB Buffer

	return new;
}


void show_jpg_dir(char *dirname, lcd_info *lcdinfo)
{
	assert(dirname);

	// prepare the double-link list
	g_head = init_list();

	DIR *dp = opendir(dirname);
	if(dp == NULL)
	{
		fprintf(stderr, "open %s failed: %s\n",
				dirname, strerror(errno));
		return;
	}

	// enter the directory
	chdir(dirname);

	struct dirent *ep = NULL;
	struct stat finfo;
	while(1)
	{
		if((ep=readdir(dp)) == NULL)
		{
			break;
		}

		bzero(&finfo, sizeof(finfo));
		stat(ep->d_name, &finfo);

		if(!S_ISREG(finfo.st_mode) || !is_jpg(ep->d_name))
			continue;

		linklist new = newnode(ep->d_name);
		list_add(new, g_head);
	}

	// no jpg-file was found
	if(is_empty(g_head))
	{
		fprintf(stderr, "no jpg-file was found, bye-bye!\n");
		exit(0);
	}

	// prepare the touch-panel
	int tp = open("/dev/input/event0", O_RDONLY);
	if(tp == -1)
	{
		perror("open() /dev/input/event0 failed");
		exit(0);
	}

	// navigate the album from the first jpg-picture
	linklist current_jpg = g_head->next;
	int action = CURRENT;
	while(1)
	{
		current_jpg = show_jpg(current_jpg, action, lcdinfo);
		action = wait4touch(tp);
	}
}

struct stat *get_file_info(char *filename)
{
	static struct stat finfo;
	bzero(&finfo, sizeof(finfo));
	stat(filename, &finfo);

	return &finfo;
}

void reset_lcd_then_quit(int sig)
{
	g_lcdinfo->vinfo.xoffset = 0;
	g_lcdinfo->vinfo.yoffset = 0;

	if(ioctl(g_lcdinfo->fd, FBIOPAN_DISPLAY, &g_lcdinfo->vinfo) == -1)
	{
		fprintf(stderr, "[%d] ioctl failed: %s\n", __LINE__, strerror(errno));
		return;
	}

	int row_size = g_lcdinfo->vinfo.xres * g_lcdinfo->vinfo.bits_per_pixel/8;
	int frm_size = g_lcdinfo->vinfo.yres * row_size;

	if(munmap(g_lcdinfo->fbmem, 2 * frm_size) == -1)
	{
		fprintf(stderr, "[%d] munmap failed: %s\n", __LINE__, strerror(errno));
		return;
	}

	close(g_lcdinfo->fd);
	exit(0);
}

int main(int argc, char **argv)
{
	char *file = check_args(argc, argv);

	// deal with ctl-c signal
	signal(SIGINT, reset_lcd_then_quit);

	// prepare LCD
	lcd_info *lcdinfo = init_lcd();
	g_lcdinfo = lcdinfo;

	printf("fd: %d\n", g_lcdinfo->fd);

	// get file's infomation
	struct stat *finfo = get_file_info(file);

	if(S_ISREG(finfo->st_mode) && is_jpg(file))
	{
		filenode *jpg = malloc(sizeof(filenode));
		jpg->name = file;

		decompress(jpg);
		display(jpg, lcdinfo);
	}
	else if(S_ISDIR(finfo->st_mode))
	{
		show_jpg_dir(file, lcdinfo);	
	}
	else
	{
		fprintf(stderr, "only regular or directory accepted.\n");
		fprintf(stderr, "bye bye!.\n");
	}

	return 0;
}
