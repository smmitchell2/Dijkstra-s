#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

sllnode *newSLLNode(void *v){
  sllnode *n = malloc(sizeof(sllnode));
  n->value = v;
  n->next = NULL;
  return n;
}

sll *newSLL(void (*d)(FILE *,void *)){
  sll *list = malloc(sizeof(sll));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  list->display = d;
  return list;
}

void insertSLL(sll *items,int index,void *value){
  if(items->size == 0 || index < 0){
    sllnode *h = newSLLNode(value);
    items->head = h;
    items->tail = h;
    items->size = items->size + 1;
  }
  else if(index == 0 && items->tail != NULL){
    sllnode *temp = items->head;
    sllnode *h = newSLLNode(value);
    h->next = temp;
    items->head = h;
    items->size = items->size + 1;
  }
  else if(index == items->size){
    sllnode *h = newSLLNode(value);
    sllnode *temp = items->tail;
    temp->next = h;
    items->tail = h;
    items->size = items->size + 1;
  }
  else {
    int i;
    sllnode *temp = items->head;
    for (i = 0; i <= index; i++) {
      if(i == index - 1){
        sllnode *h = newSLLNode(value);
        sllnode *t = temp->next;
        temp->next = h;
        h->next = t;
        items->size = items->size + 1;
        break;
      }
      temp = temp->next;
    }
  }
}

void *removeSLL(sll *items,int index){
  void *r = NULL;
  if (index == 0) {
    r = items->head->value;
    items->head = items->head->next;
    items->size = items->size - 1;
    return r;
  }
  else if(index == items->size - 1){
    int i;
    sllnode *temp = items->head;
    for(i = 0;i < items->size;++i){
      if(i == index - 1){
          r = temp->next->value;
          items->tail = temp;
          items->tail->next = NULL;
          items->size = items->size - 1;
          break;
      }
      temp = temp->next;
    }
  }
  else{
    int i;
    sllnode *temp = items->head;
    for(i = 0;i < items->size;++i){
      if(i == index - 1){
          r = temp->next->value;
          temp->next = temp->next->next;
          items->size = items->size - 1;
          break;
      }
      temp = temp->next;
    }
  }
  return r;
}

void unionSLL(sll *recipient,sll *donor){
  if(donor->head == NULL && recipient->head != NULL){return;}
  else if(recipient->head == NULL && donor->head != NULL){
    recipient->head = donor->head;
    recipient->tail = donor->tail;
    donor->head = donor->tail = NULL;
    recipient->size = donor->size;
    donor->size = 0;
    return;
  }
  else if(donor->head == NULL && recipient->head == NULL){return;}
  else{
    recipient->tail->next = donor->head;
    recipient->tail = donor->tail;
    recipient->size = recipient->size + donor->size;
    donor->head = NULL;
    donor->tail = NULL;
    donor->size = 0;
  }
}

int sizeSLL(sll *items){
  return items->size;
}

void displaySLL(FILE *fp,sll *items){
  sllnode *temp = items->head;
  fprintf(fp, "[" );
  while(temp != NULL){
    items->display(fp,temp->value);
    if(temp->next != NULL){fprintf(fp,",");}
    temp = temp->next;
  }
  fprintf(fp, "]");
}

void *getSLL(sll *items,int index){
  int i;
  sllnode *temp = items->head;
  for(i = 0;i <= items->size; ++i){
    if (i == index) {
      break;
    }
    temp  = temp->next;
  }
  return temp->value;
}