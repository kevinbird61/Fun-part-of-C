#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmp.h"

/*********************************************************/
/*  Global variables declaration：                                             */
/*  bmpHeader    ： BMP's header part
/*  bmpInfo      ： BMP's file infomation
/*  **BMPSaveData： BMP's data , which will be store into output
/*  **BMPData    ： BMP's temperary data storage
/*********************************************************/
BMPHEADER bmpHeader;
BMPINFO bmpInfo;
RGBTRIPLE *BMPSaveData = NULL;
RGBTRIPLE *BMPData = NULL;
unsigned char *color_r;
unsigned char *color_g;
unsigned char *color_b;
/*********************************************************/
/* Function declaration：
/*  readBMP    ： read the source bmp data , and store data into BMPSaveData
/*  saveBMP    ： write the BMPSaveData into output file , which is also .bmp
/*  fetchloc   :  get the element which is on (X,Y)
/*  swap       ： swap 2 data pointer (BMPSaveData and BMPData)
/*  **alloc_memory： dynamically allocate the 1D array data (sim. 2D)
/*  split_structure : split the original structure to fit SSE
/*********************************************************/
int readBMP( char *fileName);
int saveBMP( char *fileName);
RGBTRIPLE fetchloc(RGBTRIPLE *arr, int Y, int X);
RGBTRIPLE *alloc_memory( int Y, int X );
void swap(RGBTRIPLE **a, RGBTRIPLE **b);
void split_structure();
void merge_structure(int merge_mode);

int main(int argc,char *argv[])
{
  char *infileName = argv[1];
  char *outfileName = argv[2];

  // Load Data into BMPSaveData
  if ( readBMP( infileName) )
    printf("Read file successfully\n");
  else
    printf("Read file failed\n");

#ifdef SPLIT
  color_r = (char*)malloc(bmpInfo.biWidth*bmpInfo.biHeight*sizeof(char));
  color_g = (char*)malloc(bmpInfo.biWidth*bmpInfo.biHeight*sizeof(char));
  color_b = (char*)malloc(bmpInfo.biWidth*bmpInfo.biHeight*sizeof(char));
  split_structure();
#endif
  // =================== Main Operation to BMP data ===================== //

  // =================== Main Operation to BMP data ===================== //

#ifdef SPLIT
  merge_structure(SPLIT);
#endif

  // Save Data into output file from BMPSaveData
  if ( saveBMP( outfileName ) )
    printf("Save file successfully\n");
  else
    printf("Save file failed\n");

  return 0;
}

void split_structure(){
  for(int i=0;i<bmpInfo.biHeight;i++){
    for(int j=0;j<bmpInfo.biWidth;j++){
      color_r[i*bmpInfo.biWidth+j] = BMPSaveData[i*bmpInfo.biWidth+j].rgbRed;
      color_g[i*bmpInfo.biWidth+j] = BMPSaveData[i*bmpInfo.biWidth+j].rgbGreen;
      color_b[i*bmpInfo.biWidth+j] = BMPSaveData[i*bmpInfo.biWidth+j].rgbBlue;
    }
  }
}

void merge_structure(int merge_mode){
  for(int i=0;i<bmpInfo.biHeight;i++){
    for(int j=0;j<bmpInfo.biWidth;j++){
      BMPSaveData[i*bmpInfo.biWidth+j].rgbRed = color_r[i*bmpInfo.biWidth+j]*(merge_mode & 0x01);
      BMPSaveData[i*bmpInfo.biWidth+j].rgbGreen = color_g[i*bmpInfo.biWidth+j]*(merge_mode & 0x02);
      BMPSaveData[i*bmpInfo.biWidth+j].rgbBlue = color_b[i*bmpInfo.biWidth+j]*(merge_mode & 0x04);
    }
  }
}

/*********************************************************/
/* Read BMP                                              */
/*********************************************************/
int readBMP(char *fileName)
{
	// Open BMP File
  FILE *bmpFile = fopen(fileName,"rb");
  // Check the file
  if (!bmpFile){
    printf("It can't open file!!\n");
    return 0;
  }
  // Read header information into bmpHeader
  fread( &bmpHeader, sizeof( BMPHEADER ) , 1 , bmpFile );
  // Check this image's type
  if( bmpHeader.bfType != 0x4d42 ){
    printf("This file is not .BMP\n");
    return 0;
  }
  // Read file information into bmpinfo
  fread( &bmpInfo , sizeof( BMPINFO ) , 1 , bmpFile);

  printf("Picture size of picture is width: %d , height %d\n",bmpInfo.biWidth,bmpInfo.biHeight);

  // check the bit depth is 24 bits or not (bpp)
  if ( bmpInfo.biBitCount != 24 ){
    printf("This is not 24 bits!!\n");
    return 0;
  }

  // Revise the picture's width size to 4's times
  while( bmpInfo.biWidth % 4 != 0 )
  	bmpInfo.biWidth++;

  // Allocate memory to BMPSaveData
  BMPSaveData = alloc_memory( bmpInfo.biHeight, bmpInfo.biWidth);

  // Read the real picture information into BMPSaveData
  fread( BMPSaveData , sizeof(RGBTRIPLE) , bmpInfo.biWidth*bmpInfo.biHeight , bmpFile);

  // close file
  fclose(bmpFile);
  return 1;
}
/*********************************************************/
/* Save BMP                                              */
/*********************************************************/
int saveBMP( char *fileName)
{
  if( bmpHeader.bfType != 0x4d42 ){
    printf("This file is not .BMP!!\n");
    return 0;
  }

  FILE *newFile = fopen(fileName,"wb");

  if ( !newFile ){
    printf("The File can't create!!\n");
    return 0;
  }

  // Write header first
  fwrite(&bmpHeader,sizeof(BMPHEADER),1,newFile);
  // Write information
  fwrite(&bmpInfo,sizeof(BMPINFO),1,newFile);
  // Write the picture information
  fwrite(BMPSaveData,sizeof(RGBTRIPLE),bmpInfo.biWidth*bmpInfo.biHeight,newFile);

  // close file
  fclose(newFile);
  return 1;
}
/*********************************************************/
/*  Retrive location                                     */
/*********************************************************/
RGBTRIPLE fetchloc(RGBTRIPLE *arr, int Y, int X){
	return arr[bmpInfo.biWidth * Y + X ];
}
/*********************************************************/
/* allocate 1D array memory                              */
/*********************************************************/
RGBTRIPLE *alloc_memory(int Y, int X )
{
  // 2D -> 1D (column number=X , row number=Y)
	RGBTRIPLE *temp = (RGBTRIPLE *)malloc(Y*X*sizeof(RGBTRIPLE));//new RGBTRIPLE [ Y * X ];
  memset( temp, 0, sizeof( RGBTRIPLE ) * Y * X);
  return temp;
}
/*********************************************************/
/* swap data pointer                                     */
/*********************************************************/
void swap(RGBTRIPLE **a, RGBTRIPLE **b)
{
	RGBTRIPLE *temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
