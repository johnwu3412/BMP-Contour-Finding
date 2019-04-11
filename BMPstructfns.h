#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "BMPstructures.h"
uint16_t padding(uint16_t pixelsize, uint32_t ncols); //number of bytes of padding to add to the end of each pixel row
struct header initializeHeader(FILE *file);
struct pixel *initializePixel(struct header hdr, FILE *file);
uint32_t read4LE(uint8_t *pBMP);
uint16_t read2LE(uint8_t *pBMP);
void writeHeader(struct header hdr, FILE *file);
void writePixels(struct BMPfile bmfile, FILE *file);
void write4LE(uint32_t val, FILE *fp); //write four bytes of val little-endian to a file, exit if error
void write2LE(uint32_t val, FILE *fp); //write two bytes of val little-endian to a file, exit if erro