#include <stdio.h>
#include <stdlib.h>
#include "image.h"

/* prototype */
up_jpeg decompress(const char *filename);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <input.jpg>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    up_jpeg img = decompress(filename);

    if (img.pixel_data == NULL) {
        printf("Decompression failed.\n");
        return 1;
    }

    /* Basic sanity checks */
    printf("JPEG decompressed successfully!\n");
    printf("Width   : %u pixels\n", img.width);
    printf("Height  : %u pixels\n", img.height);
    printf("Channels: %u\n", img.channels);

    /* Inspect first pixel */
    printf("First pixel values:\n");
    for (unsigned int c = 0; c < img.channels; c++) {
        printf("  Channel %u: %u\n", c, img.pixel_data[c]);
    }

    /* Free image memory */
    free(img.pixel_data);

    return 0;
}

