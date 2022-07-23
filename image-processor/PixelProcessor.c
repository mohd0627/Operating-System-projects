/**
* This program file implements the color shift function
*
* Completion time: (1 hour)
*
* @author (Mohammad Hamdan)
* @version (1.0)
*
*/



#include "PixelProcessor.h"



void colorShiftPixels(struct Pixel** pArr, int width, int height, int rShift, int gShift, int bShift){




  for (int x=0; x<width; x++){

        for (int y=0; y<height; y++){

            pArr[x][y].b = pArr[x][y].b+bShift;
            pArr[x][y].r = pArr[x][y].b+rShift;
            pArr[x][y].g = pArr[x][y].b+gShift;




        }


    }


}

