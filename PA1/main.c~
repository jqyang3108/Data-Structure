#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "sorting.h"

int main(int argc, char ** argv) {
  
  int size = 0;
  int numOfStored = 0;
  int length = 0;
  double N_Comp = 0;
  double N_Move = 0;
  double sortTime = 0;
  double ioTime = 0;

  clock_t start;
  clock_t end;
  
  if(argc != 5){
    printf("Not enough inputs!");
    return EXIT_FAILURE;
  }
  
  //Load sequence and count length of the sequence
  start = clock();
  long * numArray = Load_From_File(argv[2], &size);
  length = Print_Seq(argv[3], size);

  end = clock();
  ioTime = ((double)(end - start)) / CLOCKS_PER_SEC + ioTime;


  //Insertion/Selection shell sort and sorting time
  if(strcmp(argv[1], "i") == 0){
    start = clock();
    Shell_Insertion_Sort(numArray, size, &N_Comp, &N_Move);
    end = clock();
    sortTime = ((double)(end - start)) / CLOCKS_PER_SEC + ioTime;
  }
  else if(strcmp(argv[1], "s") == 0){
    start = clock();
    Shell_Selection_Sort(numArray, size, &N_Comp, &N_Move);
    end = clock();
    sortTime = ((double)(end - start)) / CLOCKS_PER_SEC + ioTime;
  }
  else{
    printf("Neither Insertion nor selection has been choose");
    return EXIT_FAILURE;
  }

  //save file
  start = clock();
  numOfStored = Save_To_File(argv[4], numArray, size);
  end = clock();
  ioTime = ((double)(end - start)) / CLOCKS_PER_SEC + ioTime;
  
  printf("\nNumber of long integers read: %d\n", size);
  printf("Number of long integers stored: %d\n", numOfStored);
  printf("Length of sequence: %d\n", length);
  printf("Number of comparisons: %le\n", N_Comp);
  printf("Number of moves: %le\n", N_Move);
  printf("I/O time: %le\n", ioTime);
  printf("Sorting time: %le\n", sortTime);
  free(numArray);
  
  return EXIT_SUCCESS;
}
