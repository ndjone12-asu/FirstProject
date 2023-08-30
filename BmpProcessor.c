#include <stdio.h>
#include <stdlib.h>
#include "BmpProcessor.h"
#include "PixelProcessor.h"

struct BMP_Header;

struct DIB_Header;

void readBMPHeader(FILE* file, struct BMP_Header* header){
    fread(&header->signature, sizeof(char) * 2, 1, file);
    fread(&header->size, sizeof(int), 1, file);
    fread(&header->reserved1, sizeof(short), 1, file);
    fread(&header->reserved2, sizeof(short), 1, file);
    fread(&header->offset_pixel_array, sizeof(int), 1, file);
}
void writeBMPHeader(FILE* file, struct BMP_Header* header){
    fwrite(&header->signature, sizeof(char) * 2, 1, file);
    fwrite(&header->size, sizeof(int), 1, file);
    fwrite(&header->reserved1, sizeof(short), 1, file);
    fwrite(&header->reserved2, sizeof(short), 1, file);
    fwrite(&header->offset_pixel_array, sizeof(int), 1, file);
}
void readDIBHeader(FILE* file, struct DIB_Header* header){
    fread(&header->DIBsize, sizeof(int), 1, file);
    fread(&header->width, sizeof(int), 1, file);
    fread(&header->height, sizeof(int), 1, file);
    fread(&header->planes, sizeof(short), 1, file);
    fread(&header->bitsPerPixel, sizeof(short), 1, file);
    fread(&header->compression, sizeof(int), 1, file);
    fread(&header->imageSize, sizeof(int),1, file);
    fread(&header->xPPM, sizeof(int), 1, file);
    fread(&header->yPPM, sizeof(int), 1, file);
    fread(&header->numColors, sizeof(int), 1, file);
    fread(&header->colorCount, sizeof(int), 1, file);
};
void writeDIBHeader(FILE* file, struct DIB_Header* header){
    fwrite(&header->DIBsize, sizeof(int), 1, file);
    fwrite(&header->width, sizeof(int), 1, file);
    fwrite(&header->height, sizeof(int), 1, file);
    fwrite(&header->planes, sizeof(short), 1, file);
    fwrite(&header->bitsPerPixel, sizeof(short), 1, file);
    fwrite(&header->compression, sizeof(int), 1, file);
    fwrite(&header->imageSize, sizeof(int),1, file);
    fwrite(&header->xPPM, sizeof(int), 1, file);
    fwrite(&header->yPPM, sizeof(int), 1, file);
    fwrite(&header->numColors, sizeof(int), 1, file);
    fwrite(&header->colorCount, sizeof(int), 1, file);
}
void makeBMPHeader(struct BMP_Header* header, int width, int height){
    header->signature[0] = 'B';
    header->signature[1] = 'M';
    header->size = (width * height * 3) + sizeof(struct BMP_Header) - 2  + sizeof(struct DIB_Header);
    header->reserved1 = 0;
    header->reserved2 = 0;
    header->offset_pixel_array = 54;
}
void makeDIBHeader(struct DIB_Header* header, int width, int height){
    header->DIBsize = sizeof(struct DIB_Header);
    header->width = width;
    header->height = height;
    header->planes = 1;
    header->bitsPerPixel = sizeof(struct Pixel) * 8;
    header->compression = 0;
    header->imageSize = height * width * sizeof(struct Pixel);
    header->xPPM = 3780;
    header->yPPM = 3780;
    header->numColors = 0;
    header->colorCount = 0;
}
void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height){
    int padding = (4 - (width * sizeof(struct Pixel))%4)%4;
    for(int i=0; i<height; i++) {
        pArr[i] = malloc(width * sizeof(struct Pixel));
        for (int j = 0; j < width; j++) {
            fread(&pArr[i][j].b, sizeof(char), 1, file);
            fread(&pArr[i][j].g, sizeof(char), 1, file);
            fread(&pArr[i][j].r, sizeof(char), 1, file);
        }
        if(padding > 0) {
            fseek(file, padding, SEEK_CUR);
        }
    }
}
void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height){
    int padding = (4 - (width * sizeof(struct Pixel))%4)%4;
    for(int i=0; i<height; i++) {
        for (int j = 0; j < width; j++) {
            fwrite(&pArr[i][j].b, sizeof(char), 1, file);
            fwrite(&pArr[i][j].g, sizeof(char), 1, file);
            fwrite(&pArr[i][j].r, sizeof(char), 1, file);
        }
        if(padding >0) {
            fwrite(pArr, padding, 1, file);
        }
    }
}