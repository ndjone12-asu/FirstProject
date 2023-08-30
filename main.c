#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BmpProcessor.h"
#include "PpmProcessor.h"
#include "PixelProcessor.h"

typedef struct BMP_Header BMP_Header;
typedef struct DIB_Header DIB_Header;
typedef struct PPM_Header PPM_Header;
typedef struct Pixel Pixel;

int main() {
    char* readMode = "r";
    char* writeMode = "w";

    char* fileNameIn = "nehoymenory-clamped";
    char* fileExtIn = ".ppm";
    char* fullFileIn = malloc(strlen(fileNameIn) + strlen(fileExtIn) +1);
    strcpy(fullFileIn, fileNameIn);
    strcat(fullFileIn, fileExtIn);

    char* fileNameOut = "default";
    char* fileExtOut = ".ppm";
    char* fullFileOut = malloc(strlen(fileNameOut) + strlen(fileExtOut) +1);
    strcpy(fullFileOut, fileNameOut);
    strcat(fullFileOut, fileExtOut);

    FILE* file_input = fopen(fullFileIn, readMode);
    free(fullFileIn);

    struct BMP_Header* bmpHeader = (BMP_Header*)malloc(sizeof(BMP_Header));
    struct DIB_Header* dibHeader = (DIB_Header*)malloc(sizeof(DIB_Header));
    struct PPM_Header* ppmHeader = (PPM_Header*)malloc(sizeof(PPM_Header));


    //readBMPHeader(file_input, bmpHeader);
    //readDIBHeader(file_input, dibHeader);
    readPPMHeader(file_input, ppmHeader);
    //struct Pixel  **ptr = malloc(dibHeader->height * sizeof(struct Pixel*));
    struct Pixel  **ptrPpm = malloc(ppmHeader->height * sizeof(struct Pixel*));
    //readPixelsBMP(file_input, ptr, dibHeader->width, dibHeader->height);
    readPixelsPPM(file_input, ptrPpm, ppmHeader->width, ppmHeader->height);

    printf("magic number: %c%c\n", ppmHeader->magicNumber[0], ppmHeader->magicNumber[1]);
    printf("width: %d\n", ppmHeader->width);
    printf("height: %d\n", ppmHeader->height);
    printf("maxval: %d\n", ppmHeader->maxval);

//    printf("signature: %c%c\n", bmpHeader->signature[0], bmpHeader->signature[1]);
//    printf("size: %d\n", bmpHeader->size);
//    printf("reserved1: %d\n", bmpHeader->reserved1);
//    printf("reserved2: %d\n", bmpHeader->reserved2);
//    printf("offset_pixel_array: %d\n", bmpHeader->offset_pixel_array);
//
//    printf("DIBsize: %d\n", dibHeader->DIBsize);
//    printf("Width: %d\n", dibHeader->width);
//    printf("Height: %d\n", dibHeader->height);
//    printf("planes: %d\n", dibHeader->planes);
//    printf("Bits per Pixel: %d\n", dibHeader->bitsPerPixel);
//    printf("Compression: %d\n", dibHeader->compression);
//    printf("imageSize: %d\n", dibHeader->imageSize);
//    printf("X Pixels Per Meter: %d\n", dibHeader->xPPM);
//    printf("Y Pixels Per Meter: %d\n", dibHeader->yPPM);
//    printf("Colors in Color Table: %d\n", dibHeader->numColors);
//    printf("Important Color Count: %d\n", dibHeader->colorCount);
//
//    printf("pixel: B=%d, G=%d, R=%d\n", ptr[0][0].b, ptr[0][0].g, ptr[0][0].r);
//    printf("pixel: B=%d, G=%d, R=%d\n", ptr[0][1].b, ptr[0][1].g, ptr[0][1].r);
//    printf("pixel: B=%d, G=%d, R=%d\n", ptr[1][0].b, ptr[1][0].g, ptr[1][0].r);
//    printf("pixel: B=%d, G=%d, R=%d\n", ptr[1][1].b, ptr[1][1].g, ptr[1][1].r);

    printf("pixel: B=%d, G=%d, R=%d\n", ptrPpm[0][0].b, ptrPpm[0][0].g, ptrPpm[0][0].r);
//    printf("pixel: B=%d, G=%d, R=%d\n", ptrPpm[0][1].b, ptrPpm[0][1].g, ptrPpm[0][1].r);
//    printf("pixel: B=%d, G=%d, R=%d\n", ptrPpm[1][0].b, ptrPpm[1][0].g, ptrPpm[1][0].r);
//    printf("pixel: B=%d, G=%d, R=%d\n", ptrPpm[1][1].b, ptrPpm[1][1].g, ptrPpm[1][1].r);


    fclose(file_input);

    colorShiftPixels(ptrPpm, ppmHeader->width, ppmHeader->height, 0, 0, 0);
    printf("pixelshift: B=%d, G=%d, R=%d\n", ptrPpm[0][0].b, ptrPpm[0][0].g, ptrPpm[0][0].r);
//    printf("pixelshift: B=%d, G=%d, R=%d\n", ptr[0][1].b, ptr[0][1].g, ptr[0][1].r);
//    printf("pixelshift: B=%d, G=%d, R=%d\n", ptr[1][0].b, ptr[1][0].g, ptr[1][0].r);
//    printf("pixelshift: B=%d, G=%d, R=%d\n", ptr[1][1].b, ptr[1][1].g, ptr[1][1].r);

    FILE* file_output = fopen(fullFileOut, writeMode);
//    writeBMPHeader(file_output, bmpHeader);
//    writeDIBHeader(file_output, dibHeader);
    writePPMHeader(file_output, ppmHeader);
//    writePixelsBMP(file_output, ptr, dibHeader->width, dibHeader->height);
    writePixelsPPM(file_output, ptrPpm, ppmHeader->width, ppmHeader->height);

    fclose(file_output);
    free(fullFileOut);

    free(bmpHeader);
    free(dibHeader);
//    free(ptr);

    return 0;
}
