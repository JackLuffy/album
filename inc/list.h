#ifndef __LIST_H
#define __LIST_H

#ifndef LIST_NODE_DATATYPE 
#define LIST_NODE_DATATYPE int
#endif

#include "common.h"

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


#endif
