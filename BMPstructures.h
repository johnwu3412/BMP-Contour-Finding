#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
struct header{
	uint16_t id_mark;
	uint32_t file_len;
	uint32_t reserved;
	uint32_t data_offset;
	uint32_t hdr_size;
	uint32_t bitmap_width;
	uint32_t bitmap_height;
	uint16_t num_colorplanes;
	uint16_t bits_per_pixel;
	uint32_t compression_mode;
	uint32_t pixeldata_size;
	uint32_t pixels_per_meter_horizontal;
	uint32_t pixels_per_meter_vertical;
	uint32_t number_colors_used;
	uint32_t number_important_colors;
};
struct pixel{
	uint8_t red;
	uint8_t blue;
	uint8_t green;
};
struct BMPfile{
	struct header hdr;
	struct pixel *pix;
};