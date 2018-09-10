#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

int main(int argc, char **argv) {
	if (argc != 5) {
		printf("Not enough arguments\n");
		return EXIT_FAILURE;
	}
	if (*(argv[1]) != 'i' && *(argv[1]) != 's') {
		printf("Enter either 'i' or 's' as second arg\n");
		return EXIT_FAILURE;
	}
	int Size = 0; // Number of elements in Array
	clock_t start_t, end_t;
	double io_t = 0, sorting_t = 0;

	// Load elements from file into an array
	start_t = clock();
	long * Array = Load_From_File(argv[2], &Size);
	if (Array == (long *)EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	// Print out the sequence to file
	int Seq_Size = Print_Seq(argv[3], Size);
	end_t = clock();
	io_t += ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
	
	double comps = 0, moves = 0; // num of comparisons and moves
	// Shell insertion sort
	if (*(argv[1]) == 'i') {
		start_t = clock();
		Shell_Insertion_Sort(Array, Size, &comps, &moves);
		end_t = clock();
		sorting_t += ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
	}
	// Shell selection sort
	if (*(argv[1]) == 's') {
		start_t = clock();
		Shell_Selection_Sort(Array, Size, &comps, &moves);
		end_t = clock();
		sorting_t += ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
	}

	// Write the elements from array into file
	start_t = clock();
	int nels_w = Save_To_File(argv[4], Array, Size);
	end_t = clock();
	io_t += ((double)(end_t - start_t)) / CLOCKS_PER_SEC;

	// Print information to stdout
	printf("\nNumber of long integers read: %d\n", Size);
	printf("Number of long integers stored: %d\n", nels_w);
	printf("Length of sequence: %d\n", Seq_Size);
	printf("Number of comparisons: %le\n", comps);
	printf("Number of moves: %le\n", moves);
	printf("I/O time: %le\n", io_t);
	printf("Sorting time: %le\n", sorting_t);

	free(Array);
	return 0;
}
