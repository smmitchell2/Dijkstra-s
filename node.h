struct DLL;

typedef struct Node{
  struct Node *parent;
  struct Node *next;
  struct Node *prev;
  void * data;
  struct DLL *children;
}node;
