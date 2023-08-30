#include <stdio.h>
#include <stdlib.h>
#include "PixelProcessor.h"

void colorShiftPixels(struct Pixel** pArr, int width, int height, int rShift, int gShift, int bShift){
    for(int i=0; i<height; i++) {
        for (int j = 0; j < width; j++) {
            if( (pArr[i][j].b + bShift) > 255){
                pArr[i][j].b = 255;
            }
            else{
                pArr[i][j].b += bShift;
            }
            if( (pArr[i][j].g + gShift) > 255){
                pArr[i][j].g = 255;
            }
            else{
                pArr[i][j].g += gShift;
            }
            if( (pArr[i][j].r + rShift) > 255){
                pArr[i][j].r = 255;
            }
            else{
                pArr[i][j].r += rShift;
            }
        }
    }
}
