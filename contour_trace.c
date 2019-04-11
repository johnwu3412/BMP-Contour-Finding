#include <stdlib.h>
#include <stdio.h>
#include "ctrace_helper.h"
int main(int argc, char *argv[]){
	FILE *input = fopen(argv[1],"r");//input bmp file -- first argument
	FILE *output = fopen(argv[2], "w");//output contour file -- second argument
	
	int startR = atoi(argv[3]);//user-selected row
	int startC = atoi(argv[4]);//user-selected column
	
	//reading in the bmp file
	struct BMPfile file;
	file.hdr = initializeHeader(input);
	file.pix = (struct pixel *)initializePixels(file.hdr, input);
	
	
	//defining the mask
	uint8_t mask[file.hdr.bitmap_height * file.hdr.bitmap_width]; // declare the mask
	int i;
	for(i = 0; i < file.hdr.bitmap_height * file.hdr.bitmap_width; i++){
		mask[i] = 0;
	}
	
	//printing out bmp header information
	printf("BMPfile_len: %lu\n", file.hdr.file_len);
	printf("BMPreserved: %lu\n", file.hdr.reserved);
	printf("BMPdata_offset: %lu\n", file.hdr.data_offset); 
	printf("BMPhdr_size: %lu\n", file.hdr.hdr_size);
	printf("BMPbitmap_width: %lu\n", file.hdr.bitmap_width);
	printf("BMPbitmap_height: %lu\n", file.hdr.bitmap_height); 
	printf("BMPnum_colorplanes: %lu\n", file.hdr.num_colorplanes);
	printf("BMPbits_per_pixel: %lu\n", file.hdr.bits_per_pixel);
	printf("BMPcompression_mode: %lu\n", file.hdr.compression_mode); 
	printf("BMPpixeldata_size: %lu\n", file.hdr.pixeldata_size);
	printf("BMPpixels_per_meter_horizontal: %lu\n", file.hdr.pixels_per_meter_horizontal);
	printf("BMPpixels_per_meter_vertical: %lu\n", file.hdr.pixels_per_meter_vertical);
	printf("BMPnumber_colors_used: %lu\n", file.hdr.number_colors_used); 
	printf("BMPnumber_important_colors: %lu\n", file.hdr.number_important_colors);
	
	//calling bmpfloodfill -- initializes the linkedlist inside ctrace_helper.c
	bmpfloodfill(startR, startC, mask, file, file.pix[startR*file.hdr.bitmap_width + startC]);
	
	//frees the original file's pixel array
	free(file.pix);
	
	//reassigns pixel array to one that only shows edge
	file.pix = linkedlistToPix(file.hdr.bitmap_height, file.hdr.bitmap_width);
	
	//writing bmp file
	writeHeader(file.hdr, output);
	writePixels(file, output);
	
	//frees all left over pointers
	free(file.pix);
	fclose(input);
	fclose(output);
	return 1;
}