//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  File name: album/inc/jpg.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2017-7
//  
//  Description: 对jpg/jpeg图片操作头文件
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef __JPG_H
#define __JPG_H

#include "common.h"
#include "ts.h"
#include "lcd.h"
#include "jpeglib.h"

#define LIST_NODE_DATATYPE filenode
#include "list.h"

bool is_jpg(char *filename);
bool read_jpg(char *jpgname, char *jpgdata, int size);
void decompress(filenode *jpg);
void display(filenode *jpg, lcd_info *lcdinfo);

#endif
