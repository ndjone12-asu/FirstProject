#include <stdio.h>
#include <stdlib.h>
#include "PixelProcessor.h"
#include "PpmProcessor.h"

struct PPM_Header;

void readPPMHeader(FILE* file, struct PPM_Header* header){
    fscanf(file, "%9s", &header->magicNumber);
    fscanf(file, "%d", &header->width);
    fscanf(file, "%d", &header->height);
    fscanf(file, "%d", &header->maxval);
    fscanf(file, "%c", &header->newLine);
}
void writePPMHeader(FILE* file, struct PPM_Header* header){
    fprintf(file, "%s", header->magicNumber);
    fprintf(file, "%s", "\n");
    fprintf(file, "%d", header->width);
    fprintf(file, "%s", "\n");
    fprintf(file, "%d", header->height);
    fprintf(file, "%s", "\n");
    fprintf(file, "%d", header->maxval);
    fprintf(file, "%c", '\n');
}
void makePPMHeader(struct PPM_Header* header, int width, int height) {
    header->magicNumber[0] = 'P';
    header->magicNumber[1] = '6';
    header->width = width;
    header->height = height;
    header->maxval = 255;
    //header->newLine = '\n';
}
void readPixelsPPM(FILE* file, struct Pixel** pArr, int width, int height){
    for(int i=height-1; i>= 0; --i) {
        pArr[i] = malloc(width * sizeof(struct Pixel));
        for (int j = 0; j < width; j++) {
            fread(&pArr[i][j].r, sizeof(char), 1, file);
            fread(&pArr[i][j].g, sizeof(char), 1, file);
            fread(&pArr[i][j].b, sizeof(char), 1, file);
        }
    }
}
void writePixelsPPM(FILE* file, struct Pixel** pArr, int width, int height){
    for(int i=height-1; i>= 0; --i) {
        for (int j = 0; j < width; j++) {
            fwrite(&pArr[i][j].r, sizeof(char), 1, file);
            fwrite(&pArr[i][j].g, sizeof(char), 1, file);
            fwrite(&pArr[i][j].b, sizeof(char), 1, file);
        }
    }
}