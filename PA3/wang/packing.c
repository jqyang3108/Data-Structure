#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "packing.h"

void free_list(List * head);
int Size(char * Filename);
treeNode * pop(List ** list);
void push(List ** list,treeNode * root);
void Print_Tree(FILE *fp, treeNode *root);
treeNode *Search_Node(treeNode *root, int number);
void Node_pos(treeNode *root);
void HV_pos(treeNode *root);
treeNode *getMax_W(treeNode *node1, treeNode *node2);
treeNode *getMax_H(treeNode *node1, treeNode *node2);


treeNode *Load_From_File(char * Filename){
	FILE * fp = fopen(Filename,"r");
	if(fp == NULL) return NULL;
	
	int line_number = Size(Filename);//determine size of file
	if(line_number == 0) return NULL;
	fseek(fp,0,SEEK_SET);//set cursor in the begining
	
	List * temp = NULL;
	treeNode * root = NULL;
	int real_size = 0;///
	int i;
	for(i = 0; i < line_number;i++){
		//initialize treeNode structure
		root = malloc(sizeof(treeNode));
		root -> label = 0;
		root -> character = '0';
		root -> left = NULL;
		root -> right = NULL;
		root -> height = 0;
		root -> width = 0;
		root -> x_pos = 0;
		root -> y_pos = 0;
		root -> size = 0;
		
		fscanf(fp,"%c", &(root -> character));
		if((root -> character != 'H') && (root -> character != 'V')){
			fseek(fp, -1, SEEK_CUR);
			fscanf(fp, "%d(%le,%le)",&(root -> label), &(root -> width), &(root -> height));
			real_size++;

			push(&temp,root);//push on stack
		}
		else{
			root -> right = pop(&temp);
			root -> left = pop(&temp);

			push(&temp,root);
		}
		fscanf(fp,"\n");

	}
	
	root -> size = real_size;///
	treeNode * final = pop(&temp);
	fclose(fp);
	return (final);
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

void free_tree(treeNode * root){
	if(root == NULL) return;
	free_tree(root -> left);
	free_tree(root -> right);
	free(root);
} 


///starting perform packing
treeNode *Perform_Packing(treeNode *root){
	HV_pos(root);
	Node_pos(root);
	treeNode *node = Search_Node(root, root -> size);
	return node;
}

void HV_pos(treeNode *root){
	if(root -> left == NULL){
		return;
	}
	if(root -> left -> width == 0){
		HV_pos(root -> left);
	}
	if(root -> right -> width == 0){
		HV_pos(root -> right);
	}
	if(root -> character == 'H'){
		root -> height = (root -> left -> height) + (root -> right -> height);
		treeNode *temp = getMax_W(root -> left, root -> right);
		root -> width = temp -> width;
	}
	else if(root -> character == 'V'){
		root -> width = (root -> left -> width) + (root -> right -> width);
		treeNode *temp = getMax_H(root -> left, root -> right);
		root -> height = temp -> height;
	}
	return;
}
treeNode *getMax_W(treeNode *node1, treeNode *node2){
	if((node1 -> width) < (node2 -> width)){
		return node2;
	}
	else{
		return node1;
	}
}

treeNode *getMax_H(treeNode *node1, treeNode *node2){
	if((node1 -> height) < (node2 -> height)){
		return node2;
	}
	else{
		return node1;
	}
}

void Node_pos(treeNode *root){
	if(root == NULL){
		return;
	}
	if(root -> character == 'V'){
		root -> right -> y_pos = root -> y_pos;
		root -> right -> x_pos = root -> x_pos + root -> left -> width;
		root -> left -> x_pos = root -> x_pos;
		root -> left -> y_pos = root -> y_pos;
	}
	else if(root -> character == 'H'){
		root -> right -> x_pos = root -> x_pos;
		root -> right -> y_pos = root -> y_pos;
		root -> left -> x_pos = root -> x_pos;
		root -> left -> y_pos = root -> y_pos + root -> right -> height;
	}
	Node_pos(root -> left);
	Node_pos(root -> right);
	return;
}

treeNode *Search_Node(treeNode *root, int number){
	if(root == NULL) return NULL;

	else if(root -> label == number){
		return root;
	}
	else{
		treeNode *left = Search_Node(root -> left, number);
		if(left){
			return left;
		}
		left = Search_Node(root -> right, number);
		if(left){
			return left;
		}
	}
	return NULL;
}

void Save_To_File(char *Filename, treeNode *tree){
	FILE *fp = fopen(Filename, "w");
	if(fp == NULL)	return;
	Print_Tree(fp, tree);
	fclose(fp);
	return;
}

void Print_Tree(FILE *fp, treeNode *root){
	if(root == NULL) return;
	Print_Tree(fp, root -> left);
	Print_Tree(fp, root -> right);
	if(root -> character != 'H' && root -> character != 'V'){
		fprintf(fp, "%d %le %le %le %le\n", root -> label, root -> width, root -> height, root -> x_pos, root -> y_pos);
	}
	return;
}

