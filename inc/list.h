//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  File name: album/inc/list.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2017-7
//  
//  Description: 普通双向循环链表头文件
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef __LIST_H
#define __LIST_H

#include "common.h"

#ifndef LIST_NODE_DATATYPE 
#define LIST_NODE_DATATYPE int
#endif


typedef LIST_NODE_DATATYPE datatype;

typedef struct node
{
	datatype data;

	struct node *prev;
	struct node *next;
}listnode, *linklist;

#define INIT_LIST_HEAD(p) do \
			{ \
				assert(p); \
				p->prev = p; \
				p->next = p; \
			}while(0)

linklist init_list(void);

void list_add(linklist new, linklist head);
void list_add_tail(linklist new, linklist head);

void list_del(linklist list);

void list_move(linklist list, linklist head);
void list_move_tail(linklist list, linklist head);

bool is_empty(linklist list);

#endif
