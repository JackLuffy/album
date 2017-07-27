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

#endif
