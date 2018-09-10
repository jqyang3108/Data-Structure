#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

static Node *createSeq(Node *list, long *numOfEle);
void freeList(Node *list);

Node *Load_From_File(char *Filename){
 FILE * read = fopen(Filename, "r");
  if(read == NULL){
    printf("Invalid input");
    return NULL;
  }

  int i = 0;
  fseek(read, 0, SEEK_END);
  int length = ftell(read)/sizeof(long);
  fseek(read, 0, SEEK_SET);

  Node *list = NULL;
  if(length > 0){
    list = malloc(sizeof(Node));
  }
  
  Node *current = list;
  fread(&(current -> value), sizeof(long), 1, read);
  for(i = 1; i < length; i++){
    current -> next = malloc(sizeof(Node));
    current = current -> next;
    fread(&(current -> value), sizeof(long), 1, read);
    current -> next = NULL;
  }
  fclose(read);
  return list;
}

int Save_To_File(char * Filename, Node * list){
  FILE *write = fopen(Filename, "wb");
  if(write == NULL){
    return 0;
  }
  
  Node *current = list;
  int numOfEle = 0;
  
  while(current != NULL){
    fwrite(&(current -> value), sizeof(long), 1, write);
    current = current -> next;
    numOfEle++;
  }
  
  fclose(write);
  return numOfEle;
}

static Node *createSeq(Node *list, long *numOfEle) {
	Node *current = list -> next;
	while (current != NULL) {
		current = current -> next;
		(*numOfEle)++;
	}

	Node *seq = malloc(sizeof(Node));
	seq -> next = NULL;
	Node *new = NULL;
	int q = 0;
	int row = 0;
	int i = 0;
	long term1 = 1;
	long term2 = 1;

	while (term1 * term2 < (*numOfEle)) {
		seq -> value = term1 * term2;
		new = malloc(sizeof(Node));	
		new -> next = seq;
		seq = new;
		q++; 
		term1 = term1 * 2;
		term2 = term2 * 3;
		if (q > row || term1 * term2 >= (*numOfEle)) {
			row++; q = 0;
			term1 = 1;
			term2 = 1;
			for (i = 0; i < row; i++) { 
			  term1 = term1 * 2; 
			}
		}
	}
	seq = seq -> next;
	free(new);
	return seq;
}

Node *Shell_Sort(Node *list) {	
  long numOfEle = 0;
  long col = 0;
  long k = 0;
  long i = 0;
  Node *node1 = NULL; 
  Node *node2 = NULL;
  Node *temp = NULL;

  temp = list;
  list = malloc(sizeof(Node));
  list -> next = temp;	
  Node *seqPtr = createSeq(list, &numOfEle);
  Node *seq = seqPtr;


  while (seq != NULL) {
    for (col = numOfEle - 1; col >= numOfEle - (seq -> value); col--) {
      for (k = col - (seq -> value); k >= 0; k -= (seq -> value)) {
	node1 = list;
	for (i = 0; i < k; i++) {
	  node1 = node1 -> next;
	}

	node2 = node1;
	for (i = 0; i < (seq -> value); i++) {
	  node2 = node2 -> next;
	}

	while (node2 -> next != NULL && node1 -> next -> value > node2 -> next -> value) {
	  temp = node1 -> next;
	  node1 -> next = node2 -> next;
	  node2 -> next = temp;
	  temp = node1 -> next -> next;
	  node1 -> next -> next = node2 -> next -> next;
	  node2 -> next -> next = temp;

	  for (i = 0; node2 -> next != NULL && i < seq -> value; i++) {
	    node1 = node1 -> next;
	    node2 = node2 -> next;
	  }
	}
      }
    }
    seq = seq -> next;
  }

  freeList(seqPtr);
  temp = list -> next;
  free(list);
  list = temp;
  return list;
}


void freeList(Node *list){
  Node *temp = NULL;
  while(list != NULL){
    temp = list;
    list = list -> next;
    free(temp);
  }
  return;
}
