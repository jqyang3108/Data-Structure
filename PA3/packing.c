#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "packing.h"

int getSize(char * Filename);
treeNode * listPop(List ** list);
void listPush(List ** list,treeNode * treeRoot);
void getCoordinate(treeNode *treeRoot);
treeNode *compare(treeNode *node1, treeNode *node2, char choice);
void getWidthAndHeight(treeNode *root);
void printPostOrder(treeNode * treeRoot, FILE * open);

void Perform_Packing(treeNode *treeRoot){
  getWidthAndHeight(treeRoot);
  getCoordinate(treeRoot);
  return;
}

int getSize(char *Filename){
  FILE *open = fopen(Filename, "r");
  int line = 0;

  if(open == NULL){
    return line;
  }  

  int i = fgetc(open);

  while(i != EOF){
    if(i == '\n'){
      line++;
    }
    i = fgetc(open);
  }
  fseek(open,0,SEEK_END);
  fseek(open, -1, SEEK_CUR);

  int j = fgetc(open);
  if(j == '\n'){
    fseek(open,0,SEEK_SET);
    fclose(open);
    return line;
  }
  fclose(open);
  line++;
  return line; 
}

treeNode *Load_From_File(char *Filename){
  
  FILE * open = fopen(Filename, "r");
  if(open == NULL){
    return NULL;
  }  
  int numOfLine = getSize(Filename);
  if(numOfLine == 0){
    return NULL;
  }
  fseek(open, 0, SEEK_SET);

  List *temp = NULL;
  treeNode *treeRoot = NULL;

  int realSize = 0;
  int i = 0;
  
  for(i = 0; i < numOfLine;i++){
    //initialize treeNode structure
    treeRoot = malloc(sizeof(treeNode));
    treeRoot -> index = 0;
    treeRoot -> label = '0';
    treeRoot -> height = 0;
    treeRoot -> width = 0;
    treeRoot -> xVal = 0;
    treeRoot -> yVal = 0;
    treeRoot -> size = 0;
    treeRoot -> left = NULL;
    treeRoot -> right = NULL;
    
    fscanf(open, "%c", &(treeRoot -> label));
    if((treeRoot -> label != 'H') && (treeRoot -> label != 'V')){
      fseek(open, -1, SEEK_CUR);
      fscanf(open, "%d(%le, %le)", &(treeRoot -> index), &(treeRoot -> width), &(treeRoot -> height));
      
      realSize++;
      listPush(&temp, treeRoot);	   
    }
    else{
      treeRoot -> right = listPop(&temp);
      treeRoot -> left = listPop(&temp);
    
      listPush(&temp, treeRoot);
    }
    fscanf(open, "\n");
  }
  
  treeRoot -> size = realSize;
  treeNode *out = listPop(&temp);
  fclose(open);
  return out;
}

void listPush(List ** list,treeNode * treeRoot){
  List * newNode = malloc(sizeof(List));
  newNode -> node = treeRoot;
  newNode -> next = *list;
  *list = newNode;
  return;
}

treeNode * listPop(List ** list){
  if((*list) == NULL){
    return NULL;
  }	
  treeNode * tree = (*list) -> node;
  List * temp = (*list);
  (*list) = (*list) -> next;
  free(temp);
  return tree; 
}

void getWidthAndHeight(treeNode *treeRoot){
  
  if(treeRoot -> left == NULL){
    return;
  }
  if(treeRoot -> left -> width == 0){
    getWidthAndHeight(treeRoot -> left);
  }
  if(treeRoot -> right -> width == 0){
    getWidthAndHeight(treeRoot -> right);
  }
  if(treeRoot -> label == 'H'){
    treeRoot -> height = (treeRoot -> left -> height) + (treeRoot -> right -> height);    
    treeNode *temp = compare(treeRoot -> left, treeRoot -> right,'V');
    treeRoot -> width = temp -> width;
  }
  else if(treeRoot -> label == 'V'){
    treeRoot -> width = (treeRoot -> left -> width) + (treeRoot -> right -> width);
    treeNode *temp = compare(treeRoot -> left, treeRoot -> right, 'H');
    treeRoot -> height = temp -> height;
    
  }
  return;
}

treeNode *compare(treeNode *node1, treeNode *node2,char choice){
  if(choice == 'V'){
    if((node1 -> width) < (node2 -> width)){
      return node2;
    }
    else{
      return node1;
    }
  }
  else if(choice == 'H'){
    if((node1 -> height) < (node2 -> height)){
      return node2;
    }
    else{
      return node1;
    }

  } 
  return NULL;
}

void getCoordinate(treeNode *treeRoot){

  if(treeRoot == NULL){
    return;
  }

  if(treeRoot -> label== 'H'){
    treeRoot -> right -> xVal = treeRoot -> xVal;
    treeRoot -> right -> yVal = treeRoot -> yVal;
    treeRoot -> left -> xVal = treeRoot -> xVal;
    treeRoot -> left -> yVal = treeRoot -> yVal + treeRoot -> right -> height;
  }
  else if(treeRoot -> label== 'V'){
    treeRoot -> right -> yVal = treeRoot -> yVal;
    treeRoot -> right -> xVal = treeRoot -> xVal + treeRoot -> left -> width;
    treeRoot -> left -> xVal = treeRoot -> xVal;
    treeRoot -> left -> yVal = treeRoot -> yVal;
  }
  getCoordinate(treeRoot -> left);
  getCoordinate(treeRoot -> right);
		  
  return;
}

void printPostOrder(treeNode * treeRoot, FILE * open){
 
  if(treeRoot == NULL){
    return;
  }
  printPostOrder(treeRoot -> left, open);
  printPostOrder(treeRoot -> right, open);
  if(treeRoot -> label != 'H' && treeRoot -> label != 'V'){
    fprintf(open, "%d %le %le %le %le\n", treeRoot -> index, treeRoot -> width, treeRoot -> height, treeRoot -> xVal, treeRoot -> yVal);
  }
  return;
}
void getLargestNode(treeNode **largest, treeNode *tree){
  if(tree -> index > 0){
    if(tree -> index > (*largest) -> index){
      *(largest) = tree;
    }
    return;
  }
  getLargestNode(largest, tree -> right);
  getLargestNode(largest, tree -> left);
  return;
}

void Save_To_File(char *Filename, treeNode *tree){
  FILE *out = fopen(Filename, "w");
  if(out == NULL){
    return;
  }
  printPostOrder(tree, out);
  fclose(out);
  return;
}

void freeTree(treeNode *tree){
  if(tree == NULL){
    return;
  }
  freeTree(tree -> left);
  freeTree(tree -> right);
  free(tree);
  return;
}

