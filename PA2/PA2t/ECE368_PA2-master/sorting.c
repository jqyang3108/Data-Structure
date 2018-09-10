#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

// Helper function - Sequence Generation
// Sequence is stored in reverse
// Returns pointer to first node (the last value in the sequence)
static Node *Get_Seq(Node *list, long *nels_list);

Node *Load_From_File(char *Filename) {
	FILE *fp = fopen(Filename, "r");
	if (fp == NULL) {
		perror("Error ");
		return (Node *)EXIT_FAILURE;
	}
	// Determine how many longs are in file
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	int nels = len / sizeof(long);
	fseek(fp, 0, SEEK_SET);
	// Load elements into linked list
	Node * list = NULL;
	if (nels > 0) {
		list = malloc(sizeof(Node));
	}
	Node *cur = list;
	fread(&(cur -> value), sizeof(long), 1, fp);
	int i;
	for (i = 1; i < nels; i++) {
		cur -> next = malloc(sizeof(Node));
		cur = cur -> next;
		fread(&(cur -> value), sizeof(long), 1, fp);
		cur -> next = NULL;
	}
	fclose(fp);
	return list;
}

int Save_To_File(char *Filename, Node *list) {
	FILE *fp = fopen(Filename, "w");
	Node *cur = list;
	int nels_written = 0;
	while (cur != NULL) {
		fwrite(&(cur -> value), sizeof(long), 1, fp);
		cur = cur -> next;
		nels_written++;
	}
	fclose(fp);
	return nels_written;
}

static Node *Get_Seq(Node *list, long *nels_list) {
	// Find number of elements in data list
	Node *cur = list -> next;
	while (cur != NULL) {
		cur = cur -> next;
		(*nels_list)++;
	}
	Node *seq = malloc(sizeof(Node));
	seq -> next = NULL;
	Node *new = NULL;
	int q = 0, row = 0, i = 0;
	long t1 = 1, t2 = 1;
	while (t1 * t2 < (*nels_list)) {
		// Assign number in sequence
		seq -> value = t1 * t2;
		// Create new node to "left" of previous (remember, it's in reverse)
		new = malloc(sizeof(Node));	
		new -> next = seq;
		seq = new;
		// Calculate the next number in the sequence
		q++; t1 /= 2; t2 *= 3;
		if (q > row || t1 * t2 >= (*nels_list)) {
			row++; q = 0; t1 = 1; t2 = 1;
			for (i = 0; i < row; i++) { t1 *= 2; }
		}
	}
	// Destroy extra node
	seq = seq -> next;
	free(new);
	return seq;
}

Node *Shell_Sort(Node *list) {	
	long nels = 0, col, k, i;
	Node *p1, *p2, *temp;
	// Create an auxiliary head node for the list (needed for sorting)
	// i.e. list -> auxiliary head node -> data node -> ...
	temp = list;
	list = malloc(sizeof(Node));
	list -> next = temp;	
	// Generate sequence
	Node *seq_ptr = Get_Seq(list, &nels);
	Node *seq = seq_ptr;
	// For each number in sequence...
	while (seq != NULL) {
		// For each "column" from right to left (indexing from 0)...
		for (col = nels - 1; col >= nels - (seq -> value); col--) {
			// For each "insertion"...
			for (k = col - (seq -> value); k >= 0; k -= (seq -> value)) {
				// p1 points to the node BEFORE the node at index k
				// p2 points to the node BEFORE the comparison node
				p1 = list;
				for (i = 0; i < k; i++) {
					p1 = p1 -> next;
				}
				p2 = p1;
				for (i = 0; i < (seq -> value); i++) {
					p2 = p2 -> next;
				}
				// Compare values until the end of the "column"
				while (p2 -> next != NULL && p1 -> next -> value > p2 -> next -> value) {
					// Swap pointers
					temp = p1 -> next;
					p1 -> next = p2 -> next;
					p2 -> next = temp;
					temp = p1 -> next -> next;
					p1 -> next -> next = p2 -> next -> next;
					p2 -> next -> next = temp;
					// Move the pointers to the next comparison
					for (i = 0; p2 -> next != NULL && i < seq -> value; i++) {
						p1 = p1 -> next;
						p2 = p2 -> next;
					}
				}
			}
		}
		seq = seq -> next;
	}
	// Deallocate the sequence
	while (seq_ptr != NULL) {
		temp = seq_ptr;
		seq_ptr = seq_ptr -> next;
		free(temp);
	}
	// Deallocate auxiliary head node
	temp = list -> next;
	free(list);
	list = temp;
	return list;
}

