#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "BMPstructures.h"
uint16_t read2LE(uint8_t *pBMP){
	int a0 = pBMP[0];
	int a1 = pBMP[1];
	return a0 + (a1*256);
}
uint32_t read4LE(uint8_t *pBMP){
	int a0 = pBMP[0];
	int a1 = pBMP[1];
	int a2 = pBMP[2];
	int a3 = pBMP[3];
	return a0 + (a1*256) + (a2*256*256) + (a3 *256*256*256);
}
void write4LE(uint32_t val, FILE *fp) //write four bytes of val little-endian to a file, exit if error
{
	uint32_t byte1 = val%256;
    val /= 256;
    uint32_t byte2 = val%256;
    val /= 256;
    uint32_t byte3 = val%256;
    val /= 256;
    uint32_t byte4 = val%256;
    fputc(byte1,fp);
	fputc(byte2,fp);
	fputc(byte3,fp);
    fputc(byte4,fp);
}
void write2LE(uint32_t val, FILE *fp) //write two bytes of val little-endian to a file, exit if error 
{
	int byte1 = val%256;
    val /= 256;
    int byte2 = val%256;
    fputc(byte1,fp);
	fputc(byte2,fp);
}
uint16_t padding(uint16_t pixelsize, uint32_t ncols){
	return (4-(pixelsize*ncols)%4)%4;
}	//number of bytes of padding to add to the end of each pixel row

struct header initializeHeader(FILE *file){
	int c;
	struct header hdr;
	uint8_t arr[54];
	for(c = 0; c < 54; c++){
		arr[c] = fgetc(file);
	}
	hdr.id_mark = read2LE(arr);
	hdr.file_len = read4LE(arr+2);
	hdr.reserved = read4LE(arr+6);
	hdr.data_offset = read4LE(arr+10);
	hdr.hdr_size = read4LE(arr+14);
	hdr.bitmap_width = read4LE(arr+18);
	hdr.bitmap_height = read4LE(arr+22);
	hdr.num_colorplanes = read2LE(arr+26);
	hdr.bits_per_pixel = read2LE(arr+28);
	hdr.compression_mode = read4LE(arr+30);
	hdr.pixeldata_size = read4LE(arr+34);
	hdr.pixels_per_meter_horizontal = read4LE(arr+38);
	hdr.pixels_per_meter_vertical = read4LE(arr+42);
	hdr.number_colors_used = read4LE(arr+46);
	hdr.number_important_colors = read4LE(arr+50);
	return hdr;
}

struct pixel *initializePixels(struct header hdr, FILE *file){
	int height = hdr.bitmap_height;
	int width = hdr.bitmap_width;
	struct pixel *p_arr;
	p_arr = (struct pixel *)malloc(sizeof(struct pixel) * width * height);
	int pad = padding(hdr.bits_per_pixel, width);
	int r,c,p;
	for(r = 0; r < height; r++){
		for(c = 0; c < width; c++){
			p_arr[r*width + c].blue = fgetc(file);
			p_arr[r*width + c].green = fgetc(file);
			p_arr[r*width + c].red = fgetc(file);
		}
		for(p = 0; p < pad; p++){
			fgetc(file);
		}
	}
	return p_arr;
}

void writeHeader(struct header hdr, FILE *file){
	write2LE(hdr.id_mark, file);
	write4LE(hdr.file_len, file);
	write4LE(hdr.reserved, file);
	write4LE(hdr.data_offset, file);
	write4LE(hdr.hdr_size, file);
	write4LE(hdr.bitmap_width, file);
	write4LE(hdr.bitmap_height, file);
	write2LE(hdr.num_colorplanes, file);
	write2LE(hdr.bits_per_pixel, file);
	write4LE(hdr.compression_mode, file);
	write4LE(hdr.pixeldata_size, file);
	write4LE(hdr.pixels_per_meter_horizontal, file);
	write4LE(hdr.pixels_per_meter_vertical, file);
	write4LE(hdr.number_colors_used, file);
	write4LE(hdr.number_important_colors, file);
}
void writePixels(struct BMPfile bmfile, FILE *file){
	int r, c, p;
	int pad = padding(bmfile.hdr.pixeldata_size,bmfile.hdr.bitmap_width);
	for(r = 0; r<bmfile.hdr.bitmap_height; r++){
		for(c = 0; c < bmfile.hdr.bitmap_width; c++){
			fputc(bmfile.pix[r*bmfile.hdr.bitmap_width +c].blue,file);
			fputc(bmfile.pix[r*bmfile.hdr.bitmap_width +c].green,file);
			fputc(bmfile.pix[r*bmfile.hdr.bitmap_width +c].red,file);
		}
		for(p = 0; p < pad; p++){
			fputc(0,file);
		}
	}
}	
