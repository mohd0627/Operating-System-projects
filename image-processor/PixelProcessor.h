/**
* This header file define the pixel struct and the color shift function
*
* Completion time: (1 hour)
*
* @author (Mohammad Hamdan), (Acuna)
* @version (1.0)
*
*/




#ifndef PIXELPROCESSOR_H
#define PIXELPROCESSOR_H


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>





struct Pixel{
	//TODO:Finish struct

unsigned char r,g,b;

};

/**
 * Shift color of Pixel array. The dimension of the array is width * height. The shift value of RGB is
 * rShift, gShift，bShift. Useful for color shift.
 *
 * @param  pArr: Pixel array of the image that this header is for
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 * @param  rShift: the shift value of color r shift
 * @param  gShift: the shift value of color g shift
 * @param  bShift: the shift value of color b shift
 */
void colorShiftPixels(struct Pixel** pArr, int width, int height, int rShift, int gShift, int bShift);


#endif // PIXELPROCESSOR_H
