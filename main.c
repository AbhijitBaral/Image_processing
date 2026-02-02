#include <stdio.h>
#include <stdlib.h>
#include "image.h"

/* function prototypes */
up_jpeg decompress(const char *img_file);
int compress(const char *out_file, const up_jpeg *img, int quality);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s <input.jpg> <output.jpg>\n", argv[0]);
        return 1;
    }

    const char *input  = argv[1];
    const char *output = argv[2];

    /* Decompress */
    up_jpeg img = decompress(input);

    if (img.pixel_data == NULL) {
        printf("Decompression failed.\n");
        return 1;
    }

    printf("Decompressed image:\n");
    printf("  Width   : %d\n", img.width);
    printf("  Height  : %d\n", img.height);
    printf("  Channels: %d\n", img.channels);

    /* Compress */
    if (!compress(output, &img, 90)) {
        printf("Compression failed.\n");
        free(img.pixel_data);
        return 1;
    }

    printf("JPEG written successfully: %s\n", output);

    free(img.pixel_data);
    return 0;
}

