/**
* This program file implement the required functions to read, write
* and convert .ppm files and it's pixels array data.
* Completion time: (4 hours)
*
* @author (Mohammad Hamdan)
* @version (1.0)
*
*/





#include "PpmProcessor.h"
#include "PixelProcessor.h"



void readPPMHeader(FILE* file, struct PPM_Header* header){

    fread(&header->MagicNumber, sizeof(char) * 2, 1, file);
    fscanf(file, "%d %d %d", &header->width, &header->height, &header->MaxVal);

    printf("INPUT HEADER\n");
    printf("Magic number: %s\n", header->MagicNumber);
    printf("height: %d\n", header->height);
    printf("width: %d\n", header->width);
    printf("MaxVal: %d\n", header->MaxVal);

}

void writePPMHeader(FILE* file, struct PPM_Header* header){


    fprintf(file, "%s\n%d %d\n%d\n", &header->MagicNumber, &header->width, &header->height, &header->MaxVal);

    printf("OUTPUT HEADER\n");
    printf("Magic number: %s\n", header->MagicNumber);
    printf("height: %d\n", header->height);
    printf("width: %d\n", header->width);
    printf("MaxVal: %d\n", header->MaxVal);


}


void makePPMHeader(struct PPM_Header* header, int width, int height){


header->height=height;
header->width= width;
header->MaxVal=255;
strcpy(header->MagicNumber, "P6");

}







void readPixelsPPM(FILE* file, struct Pixel** pArr, int width, int height){


    for (int x=0; x<width; x++){

        for (int y=0; y<height; y++){

           fread(&pArr[x][y].r, sizeof(char), 1, file);

           fread(&pArr[x][y].g, sizeof(char), 1, file);

           fread(&pArr[x][y].b, sizeof(char), 1, file);

        }

              fseek(file, sizeof(unsigned char)*2, SEEK_CUR);
    }
}



void writePixelsPPM(FILE* file, struct Pixel** pArr, int width, int height){

char padding [2] = "  ";

for (int x=0; x<width; x++){

        for (int y=0; y<height; y++){

           fwrite(&pArr[x][y].r, sizeof(char), 1, file);

           fwrite(&pArr[x][y].g, sizeof(char), 1, file);

           fwrite(&pArr[x][y].b, sizeof(char), 1, file);

        }

             fwrite(&padding, sizeof(char)*2, 1, file);
    }
}

