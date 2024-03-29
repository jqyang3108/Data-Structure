#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "sorting.h"

int main(int argc, char ** argv) {
  
  double sortTime = 0;
  double totalTime = 0;
  clock_t start;
  clock_t end;
  
  if(argc != 3){
    printf("Not enough inputs!");
    return EXIT_FAILURE;
  }
  
  start = clock();
  Node * list = Load_From_File(argv[1]);
  if(list == NULL){
    printf("empty list!");
    return EXIT_FAILURE;
  }
  end = clock();
  totalTime = ((double)(end - start)) / CLOCKS_PER_SEC + totalTime;

  start = clock();
  list = Shell_Sort(list);
  end = clock();
  sortTime = ((double)(end - start)) / CLOCKS_PER_SEC + sortTime;

  start = clock();
  Save_To_File(argv[2], list);
  end = clock();
  totalTime = ((double)(end - start)) / CLOCKS_PER_SEC + totalTime;
  
  while(list != NULL){
    Node *temp1 = list;
    list = list -> next;
    free(temp1);
  }
  printf("I/O time: %le\n", totalTime);
  printf("Sorting time: %le\n", sortTime);
  
  return EXIT_SUCCESS;
}
