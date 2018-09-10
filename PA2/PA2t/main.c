#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Number of arguments must be 3!\n");
		return EXIT_FAILURE;
	}
	clock_t start_t, end_t;
	double io_t = 0, sorting_t = 0;
	
	// Load data from file and store in linked list
	start_t = clock();
	Node * list = Load_From_File(argv[1]);
	if (list == (Node *)EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	end_t = clock();
	io_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;

	// Sort the data
	start_t = clock();
	list = Shell_Sort(list);
	end_t = clock();
	sorting_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;

	// Write the data from linked list to file
	start_t = clock();
	Save_To_File(argv[2], list);
	end_t = clock();
	io_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;

	// Deallocate list
	Node *temp;
	while (list != NULL) {
		temp = list;
		list = list -> next;
		free(temp);
	}

	// Print statistics to stdout
	printf("I/O time: %le\n", io_t);
	printf("Sorting time: %le\n", sorting_t);

	return 0;
}
