#ifndef STD_H
#define STD_H

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

#endif

#ifndef _LIST_H
#define _LIST_H
#endif

typedef struct list_node {
    void *data;
	struct list_node *next;
} list_node;

/* linked list abstract function */
list_node* list_create(void *data);
void list_destroy(list_node **list);
list_node* list_insert_after(list_node *node,void *data);
list_node* list_insert_begining(list_node *list,void *data);
list_node* list_insert_end(list_node *list, void *data);
void list_remove(list_node **list, list_node *node);
void list_remove_by_data(list_node **list,void *data);
list_node* list_find_node(list_node *list, list_node *node);
list_node* list_find_by_data(list_node *list,void *data);
list_node* list_find(list_node *list,int(*func)(list_node*,void*),void* data);
