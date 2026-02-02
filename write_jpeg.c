#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include <jpeglib.h>

//This function follows the standard pipeline for compression of raw pixel data into jpeg as instructed in the jpeglib manual

int compress (const char *out_file, const up_jpeg *ptr_img, int quality) {
	//~~~~~~~~~~~stage 1~~~~~~~~~~~~~~
	struct jpeg_compress_struct c_obj;

	//Error management
	struct jpeg_error_mgr jerr;
	c_obj.err = jpeg_std_error(&jerr);

	jpeg_create_compress(&c_obj);

	//~~~~~~~~~~stage 2~~~~~~~~~~~~~~~
	FILE *fp = fopen(out_file, "wb");
	if(!fp) return 0;

	jpeg_stdio_dest(&c_obj, fp);

	//~~~~~~~~~stage 3~~~~~~~~~~~~~~~
	c_obj.image_height = ptr_img-> height;
	c_obj.image_width = ptr_img-> width;
	c_obj.input_components = ptr_img-> channels;

	if(ptr_img->channels == 3)
		c_obj.in_color_space = JCS_RGB;
	else if(ptr_img->channels == 1)
		c_obj.in_color_space = JCS_GRAYSCALE;
	else {
		fclose(fp);
		jpeg_destroy_compress(&c_obj);
		return 0;
	}

	jpeg_set_defaults(&c_obj);

	jpeg_set_quality(&c_obj, quality, TRUE);

	//~~~~~~~~~~~stage 4~~~~~~~~~~~~~~~~
	jpeg_start_compress(&c_obj, TRUE);

	//~~~~~~~~~~~stage 5~~~~~~~~~~~~~~~
	unsigned char* rowptr;
	
	while(c_obj.next_scanline < c_obj.image_height){
		rowptr = (ptr_img-> pixel_data) + c_obj.next_scanline*(ptr_img->channels * ptr_img->width);
		jpeg_write_scanlines(&c_obj, &rowptr, 1);
	}

	//~~~~~~~~~~~stage 6~~~~~~~~~~~~~~~
	jpeg_finish_compress(&c_obj);

	jpeg_destroy_compress(&c_obj);

	fclose(fp);

	return 1;
}

