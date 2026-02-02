#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include <jpeglib.h>


//This function follows the standard pipeline of the decompression of jpeg as per the official manual
// Output is a single line unsigned char

up_jpeg *decompress(const char *img_file){
	//~~~~~~~~~~~~~~~stage 1~~~~~~~~~~~~~~~	
	struct jpeg_decompress_struct jobj;

	FILE *fp = fopen(img_file, "rb");
	if(!fp) exit(1);


	//error handling
	struct jpeg_error_mgr jerr;
	jobj.err = jpeg_std_error(&jerr);

	jpeg_create_decompress(&jobj);


	//~~~~~~~~~~~~~~~stage 2~~~~~~~~~~~~~~
	jpeg_stdio_src(&jobj, fp);
	
	//~~~~~~~~~~~~~~~stage 3~~~~~~~~~~~~~~
	jpeg_read_header(&jobj, TRUE);

	//~~~~~~~~~~~~~~~~stage 4~~~~~~~~~~~~~~
	//Not required
	
	//~~~~~~~~~~~~~~~~stage 5~~~~~~~~~~~~~~
	jpeg_start_decompress(&jobj);

	int width = jobj.output_width;
	int height= jobj.output_height;

	unsigned char* pixel_data= malloc(height * width * jobj.output_components);

	unsigned char* rowptr;
	while(jobj.output_scanline < height){
		rowptr = pixel_data + jobj.output_scanline * width * jobj.output_components;
		jpeg_read_scanlines(&jobj, &rowptr, 1);
	}

	up_jpeg* img = malloc(sizeof(up_jpeg));
	if(!img) exit(1);

	img->height = height;
	img->width = width;
	img->pixel_data = pixel_data;
	img->channels = jobj.output_components;

	//~-~~~~~~~~~~~~~stage 6~~~~~~~~~~~~~~~
	jpeg_finish_decompress(&jobj);
	jpeg_destroy_decompress(&jobj);

	fclose(fp);	

	return (img);
}
