//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  File name: album/inc/common.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2017-7
//  
//  Description: 通用头文件
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

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
