#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "packing.h"

int main(int argc, char ** argv) {
  //load file
  treeNode *treeRoot = Load_From_File(argv[1]);

  //Find dimension and coodinate
  Perform_Packing(treeRoot);

  //Output file
  Save_To_File(argv[2],treeRoot);

  //print out the width and height
  printf("\nWidth: %le\nHeight: %le\n", treeRoot -> width, treeRoot -> height);

  //print out the coordinate of the largest rect
  treeNode *largestNode = treeRoot;
  getLargestNode(&largestNode, treeRoot);
  printf("X-coordinate: %le\nY-coordinate: %le\n", largestNode -> xVal, largestNode -> yVal);


  freeTree(treeRoot);

  return EXIT_SUCCESS;
}
