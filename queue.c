#include <stdlib.h>
#include <stdio.h>
#include "sll.h"
#include "queue.h"

//fifo
queue *newQueue(void (*d)(FILE *,void *)){
  queue *q = malloc(sizeof(queue));
  q->list = newSLL(d);
  return q;
}

void enqueue(queue *items,void *value){
  insertSLL(items->list,items->list->size ,value);
}

void *dequeue(queue *items){
  void *r = removeSLL(items->list,0);
  return r;
}

void *peekQueue(queue *items){
  return items->list->head->value;
}

int sizeQueue(queue *items){
  return items->list->size;
}

void displayQueue(FILE *fp,queue *items){
  sllnode *temp = items->list->head;
  fprintf(fp, "[" );
  while(temp != NULL){
    items->list->display(fp,temp->value);
    if(temp->next != NULL){fprintf(fp,",");}
    temp = temp->next;
  }
  fprintf(fp, "]");
}