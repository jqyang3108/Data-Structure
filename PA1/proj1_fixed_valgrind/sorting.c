#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

static int * createSeq(int Size, int *length);

long *Load_From_File(char *Filename, int *size){
  
  FILE * read = fopen(Filename, "rb");

  if(read == NULL){
    printf("Invalid input");
    return NULL;
  }
  fseek(read,0,SEEK_END);
  *size = (int)(ftell(read) / sizeof(long));
  if(*size == 0){
    return NULL;
  }
  
  long * array = NULL;
  if(*size > 0){
    array = malloc(ftell(read));
  }
  fseek(read, 0, SEEK_SET);
  fread(array, sizeof(long), *size, read);
  fclose(read);
  
  return array;
}

int Save_To_File(char * Filename, long * array, int Size){
  
  FILE *read = fopen(Filename, "w");
  int num = 0;
  if(read == NULL){
    return EXIT_FAILURE;
  }
  num = fwrite(array, sizeof(long), Size, read);
  fclose(read);
  return num;
}

static int * createSeq(int Size, int *length){

  int count = 0;
  int row = 0;
  int i = 0;
  int index = 0;
  int term1 = 1;
  int term2 = 1;
  int *array = NULL;
  
  while((term1 * term2) < Size){

    array = realloc(array, sizeof(int) * (index + 1));
    array[index] = term1 * term2;
    index++;
    
    count++;
    term1 = term1 / 2;
    term2 = term2 * 3;

    if((count > row) || (term1 * term2 >= Size)){	
      row++;
      count = 0;
      term2 = 1;
      for(term1 = 1, i = 0; i < row; i++){
	term1 = term1 * 2;
      }
    }
  }
  *length = index;
  return array;
}

void Shell_Insertion_Sort(long * Array, int Size, double * N_Comp, double * N_Move){
  int length = 0;
  int * seqArray = createSeq(Size, &length);
  long temp;
  int i = 0;
  int j = 0;
  int k = 0;
  int x = 0;
  
  for(i = length -1; i >= 0; i--){
    for(j = 0; j < seqArray[i]; j++){
      for(k = j + seqArray[i]; k < Size; k += seqArray[i]){
	x = k;
	do{
	  (*N_Comp)++;
	  if(Array[x] < Array[x - seqArray[i]]){
	    temp = Array[x];
	    Array[x] = Array[x - seqArray[i]];
	    Array[x - seqArray[i]] = temp;
	    (*N_Move) += 3;
	    x -= seqArray[i];
	  }
	  else{
	    x = -1;
	  }
	}while(x - seqArray[i] >= 0);
      }
    }
  }
  free(seqArray);
  return;
}

void Shell_Selection_Sort(long * Array, int Size, double * N_Comp, double * N_Move){
 
  int length = 0;
  int * seqArray = createSeq(Size, &length);
  long temp = 0;
  int i, j, k, minNum, a = 0;

  for(i = length - 1; i >= 0; i--){
    for(j = 0; j < seqArray[i]; j++){
      for(k = j; k < Size; k = k + seqArray[i]){
	minNum = k;
	for(a = k + seqArray[i]; a < Size; a = a + seqArray[i]){
	  (*N_Comp)++;
	  if(Array[a] < Array[minNum]){
	    minNum = a;
	  }
	}
	if(minNum != k){
	    (*N_Move) = (*N_Move + 3);
	    temp = Array[k];
	    Array[k] = Array[minNum];
	    Array[minNum] = temp;
	  }
      }      
    }
  }
  
  free(seqArray);
  return;
}

int Print_Seq(char * Filename, int Size){
  FILE * read = fopen(Filename, "w");
  int length = 0;
  int i = 0;
  
  int * numOfArray = createSeq(Size, &length);
  
  while(i < length){
    fprintf(read, "%d\n", numOfArray[i]);
    i++;
  }
  fclose(read);
  free(numOfArray);
  
  return length;
}
