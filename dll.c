#include <stdio.h>
#include <stdlib.h>
//#include "node.h"
#include "dll.h"
#include "string.h"

dll* newDLL(void){
  dll *temp = (dll*)malloc(sizeof(dll) +2);
  temp->size = 0;
  temp->head = NULL;
  temp->tail = NULL;
  return temp;
}

void insert(dll *list, node *n){
  list->size =  list->size + 1;
  n->next = n->prev = NULL;
  if ((list->tail == NULL && list->head == NULL) || (list->tail->data == NULL && list->head->data == NULL)){
    list->tail = n;
    list->head = n;
  }
  else{
    list->head->prev = n;
    n->next = list->head;
    list->head = n;
  }
}

void insertInPriQu(dll *list, node *n){
  list->size = list->size + 1;
  n->next = n->prev = NULL;
  if (list->size == 1) {
    list->tail = n;
    list->head = n;
  }
  else{
    list->head->prev = n;
    n->next = list->head;
    list->head = n;
  }
}

dll *merge(dll *flist, dll *llist){
  if(flist->size > 0 && llist->size > 0){
    flist->tail->next = llist->head;
    llist->head->prev = flist->tail;
    flist->tail = llist->tail;
    flist->size = flist->size + llist->size;
  }
  else if(flist->size == 0 && llist->size > 0){
    flist->head = llist->head;
    flist->tail = llist->tail;
    flist->size = llist->size;
  }
  return flist;
}

node *Delete(dll *list){
  node *temp;
  list->size = list->size - 1;
  if (list->head == list->tail){
    temp = list->head;
    list->head = NULL;
    list->tail = NULL;
    return temp;
  }
  else{
    temp = list->tail;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    return temp;
  }
  return temp;
}

void DeleteNode(dll *list, node *n){
  if (list->head == list->tail){
    list->head = NULL;
    list->tail = NULL;
  }
  else{
    if(n == list->head) {list->head = n->next;}
    else if(n == list->tail){
        list->tail = n->prev;
        n->prev->next = NULL;
    }
    else{
      node *prenode = n->prev;
      prenode->next = n->next;
      n->next->prev = prenode;
    }
    n->prev = NULL;
    n->next = NULL;
  }
  list->size = list->size - 1;
}
