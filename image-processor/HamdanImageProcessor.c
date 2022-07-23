/**
* This program allows the user load bmp or ppm files, perform color shifting on pixels,
* copy files and convert between bmp and ppm files types.
*
* Completion time: (10 hours)
*
* @author (Mohammad Hamdan)
* @version (1.0)
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "BmpProcessor.h"
#include "PpmProcessor.h"
#include "PixelProcessor.h"

int main(int argc, char* argv[]){

    struct BMP_Header BmpHeader;
    struct DIB_Header DibHeader;
    struct PPM_Header PpmHeader;
    struct Pixel** pArr;

    char* inputFile;
    char* outputFile;
    char* outputFileType;
    int rShift, bShift, gShift;
    int opt;

    while((opt = getopt(argc, argv, ":o:t:r:g:b:" )) != -1){

        switch (opt){

        case 'o':
           outputFile = optarg;
           break;

        case 't':
        outputFileType = optarg;
        break;

        case 'r':
            rShift=optarg;
            break;

        case 'g':
            gShift=optarg;
            break;

        case 'b':
            bShift=optarg;
            break;

        case ':':
            printf("option needs a value\n");
		break;

		 case '?':
        printf("unknown option: %c\n", optopt);
        break;


        }


    }

    for (; optind < argc; optind++){

        printf("Input: %s\n ", argv[optind]);
        inputFile = argv[optind];

    }

printf("Output: %s%c%s\n" ,outputFile, '.', outputFileType);

int inputFileLen;

if (inputFile == NULL){

   printf("try again, no such file\n");
}

if (inputFile != NULL){

    inputFileLen = strlen(inputFile);

    if (inputFileLen >= 5 && (( strcmp(&inputFile[inputFileLen-4], ".bmp") == 0) || (strcmp(&inputFile[inputFileLen-4], ".ppm") == 0))
        && (access(inputFile, F_OK) != -1) ){

            FILE* file = fopen(inputFile, "rb");

            if (strcmp(&inputFile[inputFileLen-4], ".bmp") == 0){

                readBMPHeader(file, &BmpHeader);
                readDIBHeader(file,&DibHeader);

                pArr =(struct Pixel*) malloc(DibHeader.width* sizeof(struct Pixel*));

                for (int i=0; i<DibHeader.width; i++){

                   pArr[i]=(struct Pixel*)malloc(DibHeader.height* sizeof(struct Pixel));
                }

                readPixelsBMP(file, pArr, DibHeader.width, DibHeader.height );
                printf("%d %d %d\n", rShift, gShift, bShift);

                if ((rShift !=0) && (bShift !=0) && (gShift !=0)){


                    colorShiftPixels(pArr, DibHeader.width, DibHeader.height, rShift, gShift, bShift);

                    }
                    fclose(file);

            }

            else if (strcmp(&inputFile[inputFileLen-4], ".ppm") == 0){



                 readPPMHeader(file, &PpmHeader);
                 pArr =(struct Pixel*) malloc(PpmHeader.width* sizeof(struct Pixel*));

                 for (int i=0; i<PpmHeader.width; i++){

                   pArr[i]=(struct Pixel*)malloc(PpmHeader.height* sizeof(struct Pixel));
                }

               readPixelsPPM(file, pArr, PpmHeader.width, PpmHeader.height);

                  if ((rShift !=0) && (bShift !=0) && (gShift !=0)){


                    colorShiftPixels(pArr, PpmHeader.width, PpmHeader.height, rShift, gShift, bShift);

                    }
                     fclose(file);

            }

            else { printf("Invalid input file type\n");
                    exit(1);
                }


        }
}


if (outputFile != NULL){

        if (outputFileType == NULL){

            int outputFileSize = strlen(outputFile) + 1 + 3;

            char outputFileName [outputFileSize];
            strcpy(outputFileName, outputFile);
            strcat(outputFileName, ".bmp");
            FILE* file1 = fopen(outputFileName, "wb");
            writeBMPHeader(file1, &BmpHeader);
            writeDIBHeader(file1, &DibHeader);
            writePixelsBMP(file1, pArr, DibHeader.width, DibHeader.height);
            fclose(file1);
}

        int outputFileSize = strlen(outputFile) + 1 + strlen(outputFileType);

        char outputFileName [outputFileSize];
        strcpy(outputFileName, outputFile);
        strcat(outputFileName, ".");
        strcat(outputFileName, outputFileType);


        FILE* file1 = fopen(outputFileName, "wb");


        if (strcmp(&outputFileName[outputFileSize-4], &inputFile[inputFileLen-4])==0) {

            if (strcmp(&inputFile[inputFileLen-4], ".bmp")==0){
                 writeBMPHeader(file1, &BmpHeader);
            writeDIBHeader(file1, &DibHeader);
            writePixelsBMP(file1, pArr, DibHeader.width, DibHeader.height);
            fclose(file1);

            }

            else  {

            writePPMHeader(file1, &PpmHeader);
            writePixelsPPM(file1, pArr, PpmHeader.width, PpmHeader.height);
            fclose(file1);

        }



        }


        else if ( (strcmp(&outputFileName[outputFileSize-4], ".ppm") == 0)) {

            makePPMHeader(&PpmHeader, DibHeader.width, DibHeader.height);
            writePPMHeader(file1, &PpmHeader);
            writePixelsPPM(file1, pArr, PpmHeader.width, PpmHeader.height);
            fclose(file1);

        }

        else {

             makeBMPHeader(&BmpHeader ,PpmHeader.width, PpmHeader.height);
             makeDIBHeader(&DibHeader, PpmHeader.width, PpmHeader.height);
             writeBMPHeader(file1, &BmpHeader);
             writeDIBHeader(file1, &DibHeader);
             writePixelsBMP(file1, pArr, DibHeader.width, DibHeader.height);
             fclose(file1);
        }



    }


    return 0;
}
