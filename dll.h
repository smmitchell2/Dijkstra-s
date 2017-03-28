//#include "node.h"

struct DLL;

typedef struct Node{
  struct Node *parent;
  struct Node *next;
  struct Node *prev;
  void * data;
  struct DLL *children;
}node;

typedef struct DLL{
  int size;
  node *head;
  node *tail;
}dll;

dll* newDLL(void);
void insert(dll *list, node *n);
dll* merge(dll *flist, dll *llist);
void insertInPriQu (dll *dll, node *n);
node* Delete (dll *list);
void DeleteNode (dll *list, node *n);
