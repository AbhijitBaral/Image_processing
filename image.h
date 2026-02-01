#ifndef IMAGE_H
#define IMAGE_H

#include <stddef.h>
#include <stdint.h>

typedef struct{
	uint32_t width;
	uint32_t height;
	uint32_t channels;
	unsigned char *pixel_data;
} up_jpeg;	//unpacked jpeg struct

#endif
