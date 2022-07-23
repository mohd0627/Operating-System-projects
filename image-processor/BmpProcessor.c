/**
* This program file implement the required functions to read, write
* and convert .bmp files and it's pixels array data.
* Completion time: (4 hours)
*
* @author (Mohammad Hamdan)
* @version (1.0)
*
*/



#include "BmpProcessor.h"
#include "PixelProcessor.h"



void readBMPHeader(FILE* file, struct BMP_Header* header){


    fread(&header->signature, sizeof(char) * 2, 1, file);
    fread(&header->size, sizeof(int), 1, file);
    fread(&header->reserved1, sizeof(short), 1, file);
    fread(&header->reserved2, sizeof(short), 1, file);
    fread(&header->offset_pixel_array, sizeof(int), 1, file);

    printf("INPUT HEADER\n");
    printf("signature: %c%c\n", header->signature[0], header->signature[1]);
    printf("size: %d\n", header->size);
    printf("reserved1: %d\n", header->reserved1);
    printf("reserved2: %d\n", header->reserved2);
    printf("offset_pixel_array: %d\n", header->offset_pixel_array);



}


void writeBMPHeader(FILE* file, struct BMP_Header* header){

    fwrite(&header->signature, sizeof(char) * 2, 1, file);
    fwrite(&header->size, sizeof(int), 1, file);
    fwrite(&header->reserved1, sizeof(short), 1, file);
    fwrite(&header->reserved2, sizeof(short), 1, file);
    fwrite(&header->offset_pixel_array, sizeof(int), 1, file);

    printf("OUTPUT HEADER\n");
    printf("signature: %c%c\n", header->signature[0], header->signature[1]);
    printf("size: %d\n", header->size);
    printf("reserved1: %d\n", header->reserved1);
    printf("reserved2: %d\n", header->reserved2);
    printf("offset_pixel_array: %d\n", header->offset_pixel_array);



}


void readDIBHeader(FILE* file, struct DIB_Header* header){

    fread(&header->HeaderSize, sizeof(int), 1, file);
    fread(&header->width, sizeof(int), 1, file);
    fread(&header->height, sizeof(int), 1, file);
    fread(&header->planes, sizeof(short), 1, file);
    fread(&header->BitsPerPixel, sizeof(short), 1, file);
    fread(&header->comp, sizeof(int), 1, file);
    fread(&header->imgSize, sizeof(int), 1, file);
    fread(&header->x, sizeof(int), 1, file);
    fread(&header->y, sizeof(int), 1, file);
    fread(&header->color, sizeof(int), 1, file);
    fread(&header->colorCount, sizeof(int), 1, file);

    printf("HeaderSize: %d\n", header->HeaderSize);
    printf("width: %d\n", header->width);
    printf("height: %d\n", header->height);
    printf("planes: %d\n", header->planes);
    printf("Bits per pixel: %d\n", header->BitsPerPixel);
    printf("compression: %d\n", header->comp);
    printf("Image size: %d\n", header->imgSize);
    printf("X resolution: %d\n", header->x);
    printf("Y resolution: %d\n", header->y);
    printf("colors in table: %d\n", header->color);
    printf("important color count: %d\n", header->colorCount);

}


void writeDIBHeader(FILE* file, struct DIB_Header* header){

    fwrite(&header->HeaderSize, sizeof(int), 1, file);
    fwrite(&header->width, sizeof(int), 1, file);
    fwrite(&header->height, sizeof(int), 1, file);
    fwrite(&header->planes, sizeof(short), 1, file);
    fwrite(&header->BitsPerPixel, sizeof(short), 1, file);
    fwrite(&header->comp, sizeof(int), 1, file);
    fwrite(&header->imgSize, sizeof(int), 1, file);
    fwrite(&header->x, sizeof(int), 1, file);
    fwrite(&header->y, sizeof(int), 1, file);
    fwrite(&header->color, sizeof(int), 1, file);
    fwrite(&header->colorCount, sizeof(int), 1, file);

    printf("HeaderSize: %d\n", header->HeaderSize);
    printf("width: %d\n", header->width);
    printf("height: %d\n", header->height);
    printf("planes: %d\n", header->planes);
    printf("Bits per pixel: %d\n", header->BitsPerPixel);
    printf("compression: %d\n", header->comp);
    printf("Image size: %d\n", header->imgSize);
    printf("X resolution: %d\n", header->x);
    printf("Y resolution: %d\n", header->y);
    printf("colors in table: %d\n", header->color);
    printf("important color count: %d\n", header->colorCount);


}



void makeBMPHeader(struct BMP_Header* header, int width, int height){

   header->reserved1=0;
   header->reserved2=0;
   int x= width*height*3+ (width*2);

   header->size = 14+40+x;
   header->offset_pixel_array=54;
   strcpy(header->signature, "BM");


}



void makeDIBHeader(struct DIB_Header* header, int width, int height){

    header->planes=1;
    header->comp=0;
    header->color=0;
    header->colorCount=0;
    header->BitsPerPixel=24;
    header->width=width;
    header->height=height;
    header->HeaderSize=40;

    int x = width*height*3+ (width*2);

    header->imgSize = x;
    header->x=3780;
    header->y=3780;



}

void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height){


    for (int x=0; x<width; x++){

        for (int y=0; y<height; y++){

           fread(&pArr[x][y].b, sizeof(char), 1, file);

           fread(&pArr[x][y].g, sizeof(char), 1, file);

           fread(&pArr[x][y].r, sizeof(char), 1, file);

        }

              fseek(file, sizeof(unsigned char)*2, SEEK_CUR);
    }


}




void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height){

char c[2]= "  ";
    for (int x=0; x<width; x++){

        for (int y=0; y<height; y++){

           fwrite(&pArr[x][y].b, sizeof(char), 1, file);

           fwrite(&pArr[x][y].g, sizeof(char), 1, file);

           fwrite(&pArr[x][y].r, sizeof(char), 1, file);

        }

              fwrite(&c, sizeof(char)*2, 1, file);
    }

}

