#include "../list.h"

/*
 *
 */
list_node* list_create(void *data)
{
    list_node *list = malloc(sizeof(list_node));
	if(list != NULL){
	    list->next = NULL;
		list->data = data;
	}
	
	return list;
}

void list_destroy(list_node **list)
{
    if(list == NULL) return;
	while(*list != NULL){
	    list_remove(list,*list);
	}
}

list_node* list_insert_after(list_node *node, void *data)
{
    list_node *new_node = list_create(data);
	if(new_node){
	    new_node->next = node->next;
		node->next = new_node;
	}
	return new_node;
}

list_node* list_insert_beginning(list_node *list,void *data)
{
    list_node *new_node = list_create(data);
	if(new_node != NULL){
	   new_node->next = list;
	}
	return new_node;
}

list_node* list_insert_end(list_node *list,void *data)
{
    list_node *new_node = list_create(data);
    if(new_node != NULL){
      list_node *it = list;
      while(it->next != NULL){
	it = it->next;
      }
      it->next = new_node;
    }
    return new_node;
}

void list_remove(list_node **list, list_node *node)
{
    list_node *tmp = NULL;
	if(list == NULL || *list == NULL || node == NULL) return;
	//remove the whole list
	if(*list == node){
	    *list = (*list)->next;
		free(node);
		node = NULL;
	}else{
	//remvoe one of the item
	    tmp = *list;
		while(tmp->next && tmp->next != node) tmp = tmp->next;
		if(tmp->next){
		    tmp->next = node->next;
			free(node);
			node = NULL;
		}
	}
}

void list_remove_by_data(list_node **list,void *data)
{
    if(list == NULL || *list == NULL || data == NULL) return;
	list_remove(list,list_find_by_data(*list,data));
}

list_node* list_find_node(list_node *list, list_node *node)
{
    while(list){
	    if(list == node) break;
		list = list->next;
	}
	return list;
}

list_node* list_find_by_data(list_node *list,void *data)
{
    while(list){
	   if(list->data == data) break;
	   list = list->next;
	}
	return list;
}

list_node* list_find(list_node *list, int(*func)(list_node*,void*),void *data)
{
    if(!func) return NULL;
	while(list){
	    if(func(list,data)) break;
		list = list->next;
	}
	return list;
}

/* main(){ */
/*   int num1 = 1; */
/*   int num2 = 2; */
/*   int *one = &num1; */
/*   int *two = &num2; */
/*   list_node *head = list_create(one); */
/*   list_insert_after(head,two); */
/*   printf("Num: %d \n",*((int *)head->data)); */
/*   printf("Num: %d \n",*((int *)head->next->data)); */
/*   char in[50]; */
/*   scanf("%s",in); */
/*   int a = 1; */
/*   int *b; */
/*   int **c; */
/*   b = &a; */
/*   c = &b; */
/*   printf("a: %d \n",a); */
/*   printf("b: %p \n",b); */
/*   printf("c: %p \n",c); */
	
/*   printf("*b: %d \n",*b); */
/*   printf("*c: %p \n",*c); */
	
/*   printf("**c: %d \n",**c); */
	
/*   ++(*b); */
/*   printf("++(*b): %d \n",*b); */
/*   //++(*c); */
/*   ++(**c); */
/*   printf("++(*c): %p \n",*c); */
/*   printf("++(**c): %d \n",**c); */
	
/*   return 0; */
/* } */




