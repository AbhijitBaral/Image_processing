#include <stdio.h>
#include <stdlib.h>
#include "image.h"

/* prototypes */
up_jpeg *decompress(const char *img_file);
void rgb_to_grayscale(up_jpeg *img);
int compress(const char *out_file, const up_jpeg *img, int quality);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s <input.jpg> <output.jpg>\n", argv[0]);
        return 1;
    }

    up_jpeg *img = decompress(argv[1]);

    if (!img || !img->pixel_data) {
        printf("Decompression failed\n");
        return 1;
    }

    printf("Decompressed image:\n");
    printf("  Width   : %d\n", img->width);
    printf("  Height  : %d\n", img->height);
    printf("  Channels: %d\n", img->channels);

    printf("First pixel values:\n");
    for (int c = 0; c < img->channels; c++) {
        printf("  channel %d = %u\n", c, img->pixel_data[c]);
    }

    /* Optional: test grayscale */
    rgb_to_grayscale(img);

    printf("After grayscale:\n");
    printf("  Channels: %d\n", img->channels);

    /* Optional: test compression */
    if (!compress(argv[2], img, 90)) {
        printf("Compression failed\n");
    } else {
        printf("JPEG written to %s\n", argv[2]);
    }

    /* Cleanup */
    free(img->pixel_data);
    free(img);

    return 0;
}

