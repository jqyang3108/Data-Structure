#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "math.h"

#ifndef READIMAGE_OFF
BMPImage * readImage(FILE * fp) {

// FILL IN
  //file check
  if(fp == NULL){
    return NULL;
  }
  
  BMPImage * image = malloc(sizeof(BMPImage));
  BMPHeader h;
  fread(&h,sizeof(BMPHeader),1,fp);
  
  image -> header = h;
  image -> norm_height = abs(image -> header.height_px);
  image -> pixels = malloc(sizeof(Pixel *) * image -> norm_height);

  for(int c = 0; c < image -> norm_height; c++){
    image -> pixels[c] = malloc(sizeof(Pixel) * image -> header.width_px);
  }
 
  
  for(int i = 0; i < image -> norm_height; i++){
    for(int j = 0; j < image -> header.width_px; j++)
      {
	fread(&(image -> pixels[i][j]), sizeof(Pixel),1,fp); //
      }				
  }
  return image;
}

void freeImage(BMPImage * image) {
	
// FILL IN
  for(int i = 0; i < image -> norm_height;i++){
    free(image -> pixels[i]);
  }
  free(image -> pixels);
  free(image);
  return;
}
#endif

#ifndef WRITEIMAGE_OFF
void writeImage(BMPImage * image, FILE * fp) {

// FILL IN
  fwrite(&(image -> header), 54,1,fp);
  for(int i = 0; i < image -> norm_height;i++){
    for(int j = 0;j < image -> header.width_px; j++){
      fwrite(&(image -> pixels[i][j]),sizeof(Pixel),1,fp); ///
    }
  }
  return;

}
#endif
