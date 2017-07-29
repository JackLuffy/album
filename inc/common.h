#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>

typedef struct filenode
{
	char *name;

	int width;
	int height;
	int bpp;

	char *rgb;
}filenode;

#define LIST_NODE_DATATYPE filenode
#include "list.h"

#include "ts.h"
#include "lcd.h"
#include "jpeglib.h"

#define CURRENT 0
#define PREV 1
#define NEXT 2

#endif
