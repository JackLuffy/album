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
void display(filenode *jpg, lcd_info *lcdinfo, int xoffset, int yoffset);

#endif
