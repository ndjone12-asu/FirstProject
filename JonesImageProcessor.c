#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "BmpProcessor.h"
#include "PpmProcessor.h"
#include "PixelProcessor.h"

typedef struct BMP_Header BMP_Header;
typedef struct DIB_Header DIB_Header;
typedef struct PPM_Header PPM_Header;
typedef struct Pixel Pixel;

int main(int argc, char **argv) {
    char* readMode;
    char* writeMode;
    char* fileNameIn = "";
    char* fileExtIn;
    char* fileNameOut = "default";
    char* fileExtOut = ".ppm";
    char* intParser;
    int rshift, gshift, bshift;
    int c = 0;
    opterr = 0;

    while((c = getopt(argc, argv, "o:r:g:b:t:")) != -1){
        switch(c)
        {
            case 'o':
                fileNameOut = optarg;
                break;
            case 't':
                fileExtOut = optarg;
                break;
            case 'r':
                rshift = strtol(optarg, &intParser, 10);
                if(intParser != optarg && *intParser == '\0'){
                    rshift = (int)rshift;
                }
                else{
                    printf("Not a valid integer for r color shift.");
                    return 1;
                }
                break;

            case 'g':
                gshift = strtol(optarg, &intParser, 10);
                if(intParser != optarg && *intParser == '\0'){
                    gshift = (int)gshift;
                }
                else{
                    printf("Not a valid integer for g color shift.");
                    return 1;
                }
                break;
            case 'b':
                bshift = strtol(optarg, &intParser, 10);
                if(intParser != optarg && *intParser == '\0'){
                    bshift = (int)bshift;
                }
                else{
                    printf("Not a valid integer for b color shift.");
                    return 1;
                }
                break;
            case '?':
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                return 1;
            default:
                abort();
        }
    }
    fileNameIn = argv[optind];
    fileExtIn = strrchr(fileNameIn, '.');
    if(access(fileNameIn, F_OK) != 0){
        printf("Error: input file does not exist or is inaccessible.");
        return 1;
    }
    if(strcmp(fileExtIn, ".ppm") != 0 && strcmp(fileExtIn, ".bmp") != 0){
        printf("Error: Improper input file extension. Must be .bmp or .ppm.");
        return 1;
    }
    if(strcmp(fileExtOut, ".ppm") != 0 && strcmp(fileExtOut, ".bmp") != 0){
        printf("Error: Improper output file extension. Must be .bmp or .ppm.");
        return 1;
    }

    char* fullFileIn = malloc(strlen(fileNameIn)+1);
    strcpy(fullFileIn, fileNameIn);

    char* fullFileOut = malloc(strlen(fileNameOut) + strlen(fileExtOut) +1);
    strcpy(fullFileOut, fileNameOut);
    strcat(fullFileOut, fileExtOut);

    struct BMP_Header* bmpHeader = (BMP_Header*)malloc(sizeof(BMP_Header));
    struct DIB_Header* dibHeader = (DIB_Header*)malloc(sizeof(DIB_Header));
    struct PPM_Header* ppmHeader = (PPM_Header*)malloc(sizeof(PPM_Header));


    if(strcmp(fileExtIn, ".ppm") == 0) {
        readMode = "r";
        FILE* file_input = fopen(fullFileIn, readMode);

        readPPMHeader(file_input, ppmHeader);
        struct Pixel **ptrPpm = malloc(ppmHeader->height * sizeof(struct Pixel *));
        readPixelsPPM(file_input, ptrPpm, ppmHeader->width, ppmHeader->height);
        fclose(file_input);
//
//        printf("magic number: %c%c\n", ppmHeader->magicNumber[0], ppmHeader->magicNumber[1]);
//        printf("width: %d\n", ppmHeader->width);
//        printf("height: %d\n", ppmHeader->height);
//        printf("maxval: %d\n", ppmHeader->maxval);
//
//        printf("pixel: B=%d, G=%d, R=%d\n", ptrPpm[0][0].b, ptrPpm[0][0].g, ptrPpm[0][0].r);

        colorShiftPixels(ptrPpm, ppmHeader->width, ppmHeader->height, rshift, gshift, bshift);

//        printf("pixelshift: B=%d, G=%d, R=%d\n", ptrPpm[0][0].b, ptrPpm[0][0].g, ptrPpm[0][0].r);


        if (strcmp(fileExtOut, ".ppm") == 0) {
            writeMode = "w";
            FILE* file_output = fopen(fullFileOut, writeMode);
            writePPMHeader(file_output, ppmHeader);
            writePixelsPPM(file_output, ptrPpm, ppmHeader->width, ppmHeader->height);
            fclose(file_output);
        }
        else if(strcmp(fileExtOut, ".bmp") == 0){
            writeMode = "wb";
            FILE* file_output = fopen(fullFileOut, writeMode);

            makeBMPHeader(bmpHeader, ppmHeader->width, ppmHeader->height);
            makeDIBHeader(dibHeader, ppmHeader->width, ppmHeader->height);

            writeBMPHeader(file_output, bmpHeader);
            writeDIBHeader(file_output, dibHeader);
            writePixelsBMP(file_output, ptrPpm, dibHeader->width, dibHeader->height);
            fclose(file_output);
        }

    }
    else if(strcmp(fileExtIn, ".bmp")==0){
        readMode = "rb";
        FILE* file_input = fopen(fullFileIn, readMode);

        readBMPHeader(file_input, bmpHeader);
        readDIBHeader(file_input, dibHeader);

        struct Pixel  **ptr = malloc(dibHeader->height * sizeof(struct Pixel*));
        readPixelsBMP(file_input, ptr, dibHeader->width, dibHeader->height);
        fclose(file_input);

//        printf("signature: %c%c\n", bmpHeader->signature[0], bmpHeader->signature[1]);
//        printf("size: %d\n", bmpHeader->size);
//        printf("reserved1: %d\n", bmpHeader->reserved1);
//        printf("reserved2: %d\n", bmpHeader->reserved2);
//        printf("offset_pixel_array: %d\n", bmpHeader->offset_pixel_array);
//
//        printf("DIBsize: %d\n", dibHeader->DIBsize);
//        printf("Width: %d\n", dibHeader->width);
//        printf("Height: %d\n", dibHeader->height);
//        printf("planes: %d\n", dibHeader->planes);
//        printf("Bits per Pixel: %d\n", dibHeader->bitsPerPixel);
//        printf("Compression: %d\n", dibHeader->compression);
//        printf("imageSize: %d\n", dibHeader->imageSize);
//        printf("X Pixels Per Meter: %d\n", dibHeader->xPPM);
//        printf("Y Pixels Per Meter: %d\n", dibHeader->yPPM);
//        printf("Colors in Color Table: %d\n", dibHeader->numColors);
//        printf("Important Color Count: %d\n", dibHeader->colorCount);
//
//        printf("pixel: B=%d, G=%d, R=%d\n", ptr[0][0].b, ptr[0][0].g, ptr[0][0].r);

        colorShiftPixels(ptr, dibHeader->width, dibHeader->height, rshift, gshift, bshift);

//        printf("pixelshift: B=%d, G=%d, R=%d\n", ptr[0][0].b, ptr[0][0].g, ptr[0][0].r);

        if(strcmp(fileExtOut, ".bmp") ==0){
            writeMode = "wb";
            FILE* file_output = fopen(fullFileOut, writeMode);

            writeBMPHeader(file_output, bmpHeader);
            writeDIBHeader(file_output, dibHeader);
            writePixelsBMP(file_output, ptr, dibHeader->width, dibHeader->height);
            fclose(file_output);
        }
        else if(strcmp(fileExtOut, ".ppm") == 0){
            writeMode = "w";
            FILE* file_output = fopen(fullFileOut, writeMode);
            makePPMHeader(ppmHeader, dibHeader->width, dibHeader->height);
            writePPMHeader(file_output, ppmHeader);
            writePixelsPPM(file_output, ptr, ppmHeader->width, ppmHeader->height);
            fclose(file_output);
        }
    }

    free(fullFileIn);
    free(fullFileOut);

    free(bmpHeader);
    free(dibHeader);
    free(ppmHeader);
//    free(ptr);

    return 0;
}
