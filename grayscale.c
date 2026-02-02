#include <stdlib.h>
#include "image.h"

void rgb_to_grayscale(up_jpeg *ptr_img) {
	unsigned char* gray_pxl_data = malloc((ptr_img->height) * (ptr_img->width));
	if(!gray_pxl_data)
		return;

	//gray intensity extraction
	unsigned char *R = ptr_img -> pixel_data;
	unsigned char *G = ptr_img -> pixel_data + 1;
	unsigned char *B = ptr_img -> pixel_data + 2;

	unsigned char *ptr_gray_pixel = gray_pxl_data;

	for (int row=0; row< ptr_img->height; row++){
		for(int col=0; col< ptr_img->width; col++){
			*ptr_gray_pixel = (unsigned char)((299*(*R) + 587*(*G) + 114*(*B))/1000);

			R = R + 3;
			G = G + 3;
			B = B + 3;

			ptr_gray_pixel++;
		}
	}

	//free the old memory
	free(ptr_img->pixel_data);

	//Redirect the old buffer towards the gray_pixel buffer
	ptr_img->pixel_data = gray_pxl_data;

	//Update metadata
	ptr_img->channels = 1;

}

			

