#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "packing.h"

int getSize(FILE *open);
treeNode *Pick_Max(treeNode *node1, treeNode *node2, char choice);
void getCoordinate(treeNode *treeRoot);
void getWidthAndHeight(treeNode *root);
void printPostOrder(treeNode * treeRoot, FILE * open);
void freeArray(nodeArray input, FILE *open);

/****
void freeArray(nodeArray input, FILE *open){
  int i = 0;
  int size = getSize(open);
  for(i = 0; i < size; i++){
    free(input.array[i]);
  }
  return;
}


**/

void Perform_Packing(treeNode *treeRoot){
  getWidthAndHeight(treeRoot);
  getCoordinate(treeRoot);
  return;
}

int getSize(FILE *open){
  int numOfLine = 0;
  do{
    if(fgetc(open) == '\n'){
      numOfLine++;
    }
  }while(feof(open) == 0);
  rewind(open);
  return numOfLine;
}
/***
nodeArray Load_From_File(FILE *open){
  int i = 0;
  nodeArray input;
  int numOfLine = getSize(open);
  input.array = malloc(numOfLine * sizeof(treeNode*));
  input.size = numOfLine;
  for(i = 0; i < numOfLine ; i++){
    input.array[i] = malloc(sizeof(treeNode));
    input.array[i] -> left = NULL;
    input.array[i] -> right = NULL;
    input.array[i] -> index = 0;
    input.array[i] -> width = 0;
    input.array[i] -> height = 0;
    input.array[i] -> xVal = 0;
    input.array[i] -> yVal = 0;
    //get the first number (label)
    input.array[i] -> label = fgetc(open);
    
    if(fgetc(open) != '\n'){
      fseek(open, -2, SEEK_CUR);
      fscanf(open, "%d(%le,%le)\n", &(input.array[i] -> index),  &(input.array[i] -> width),  &(input.array[i] -> height)); 
      printf( "%d(%le,%le)\n", input.array[i] -> index,  input.array[i] -> width, input.array[i] -> height);
      input.array[i] -> label = 0; 
    }
   
  }
  return input;
}


treeNode *buildTree(int * cur, treeNode **array){
  (*cur)--;
  int cursor = *cur;
  
  if((array[cursor]) -> index > 0){
    return array[cursor];
  }
  array[cursor] -> right = buildTree(cur, array);
  array[cursor] -> left = buildTree(cur, array);
  return array[cursor];
}

***/

treeNode * Load_From_File(FILE *open){
  
  int numOfLine = getSize(open);
  if(numOfLine == 0){
    return NULL;
  }
  fseek(open, 0, SEEK_SEK);

  List *temp = NULL;
  treeNode *treeRoot = NULL;
  
  for(i = 0; i < line_number;i++){
		//initialize treeNode structure
		treeRoot = malloc(sizeof(treeNode));
		treeRoot -> label = 0;
		treeRoot -> character = '0';
	        treeRoot -> left = NULL;
		treeRoot -> right = NULL;
		treeRoot -> height = 0;
		treeRoot -> width = 0;
		treeRoot -> x_pos = 0;
		treeRoot -> y_pos = 0;
		treeRoot -> size = 0;
		
  

  
}
void push(List ** list,treeNode * root){
	List * newNode = malloc(sizeof(List));
	newNode -> node = root;
	newNode -> next = *list;
	*list = newNode;
	return;
}

treeNode * pop(List ** list){
	if((*list) == NULL)
	{
		return NULL;
	}	
	treeNode * tNode = (*list) -> node;
	List * temp = (*list);
	(*list) = (*list) -> next;
	free(temp);
	return tNode; 
}

int Size(char * Filename){
	int line = 0;
	FILE * fp =fopen(Filename, "r");
	if(fp == NULL)return line;
	int ch = fgetc(fp);
	while(ch != EOF){
		if(ch == '\n'){
			line++;
		}
		ch = fgetc(fp);
	}
	fseek(fp,0,SEEK_END);
	fseek(fp, -1, SEEK_CUR);
	int gg = fgetc(fp);
	if(gg == '\n'){
		fseek(fp,0,SEEK_SET);
		fclose(fp);
		return line;
	}
	fclose(fp);
	return (line + 1); //purposely add "1",because of the last "\n"
}


//-------------------------------------------------------------------------------------------




void getWidthAndHeight(treeNode *root){

	if(root -> left == NULL){
		return;
	}
	if(root -> left -> width == 0){
		getWidthAndHeight(root -> left);
	}
	if(root -> right -> width == 0){
		getWidthAndHeight(root -> right);
	}
	if(root -> label == 'H'){
		root -> height = (root -> left -> height) + (root -> right -> height);    
		treeNode *temp = Pick_Max(root -> left, root -> right,'W');
		root -> width = temp -> width;
	}
	else if(root -> label == 'V'){
		root -> width = (root -> left -> width) + (root -> right -> width);
		treeNode *temp = Pick_Max(root -> left, root -> right, 'H');
		root -> height = temp -> height;
     
	}
  return;
}

treeNode *Pick_Max(treeNode *node1, treeNode *node2,char choice){
  if(choice == 'W'){
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
  else  if(treeRoot -> label== 'V'){
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

