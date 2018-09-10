#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node{
  long value;
  struct Node *next;
}Node;

Node *Load_From_File(char *Filename);
int Save_To_File(char * Filename, Node * list);
Node * Shell_Sort(Node *list);

