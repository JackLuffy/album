//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  File name: album/src/list.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2017-7
//  
//  Description: 普通双向循环链表实现
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "list.h"

linklist init_list(void)
{
	linklist head = calloc(1, sizeof(listnode));
	if(head != NULL)
	{
		INIT_LIST_HEAD(head);
	}

	return head;
}

// insert new after head
void list_add(linklist new, linklist head)
{
	assert(new);
	assert(head);

	new->prev = head;
	new->next = head->next;

	head->next->prev = new;
	head->next = new;
}

// insert new before head, i.e. the tail of the list
void list_add_tail(linklist new, linklist head)
{
	assert(new);
	assert(head);

	new->prev = head->prev;
	new->next = head;

	head->prev->next = new;
	head->prev = new;
}

// remove del from the list in which it contains 
void list_del(linklist del)
{
	assert(del);

	del->prev->next = del->next;
	del->next->prev = del->prev;

	INIT_LIST_HEAD(del);
}

bool is_empty(linklist list)
{
	assert(list);

	return list->next == list;
}
