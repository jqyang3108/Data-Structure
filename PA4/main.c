#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

void freeNode(Node * node);

int main(int argc, char * argv[]) {
    if(argc != 3)
    {
        return EXIT_FAILURE;
    }
    clock_t start_input, end_input, start_output, end_output, start_sort, end_sort;
    
    start_input = clock();
	Node * node = Load_From_File(argv[1]);
    end_input = clock();
    double input_time = (double)(end_input - start_input) / CLOCKS_PER_SEC;
    
    start_sort = clock();
	node = Shell_Sort(node);
	end_sort = clock();
    double sort_time = (double)(end_sort - start_sort) / CLOCKS_PER_SEC;
    
    start_output = clock();
    int size = Save_To_File(argv[2], node);
    end_output = clock();
    double output_time = (double)(end_output - start_output) / CLOCKS_PER_SEC;
    
    double total_time = input_time + output_time;
    
	if(size == 0)
	{
		return EXIT_FAILURE;
	}

    printf("I/O time: %le\n", total_time);
    printf("Sorting time %le\n",sort_time);
	freeNode(node);
	
	return EXIT_SUCCESS;
}

