#include <stdio.h>
#include <stdlib.h>

#include "bitmap.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("supply an input and output image path\n");
        return 1;
    }
    FILE *img = fopen(argv[1], "r+wb");
    if(!img) {
        printf("unable to open image \"%s\"\n", argv[1]);
        return 1;
    }

    BITMAPFILEHEADER bfh = load_BFH_BMP(img);
    if(!validate_BMP(bfh.bfType)) {
        printf("\"%s\" was not recognised as a bitmap file\n", argv[1]);
        fclose(img);
        return 1;
    }
    BITMAPV5INFOHEADER data = load_DIB_BMP(img);

    Color pixc = {
        .b = 0,
        .g = 0,
        .r = 255,
    };
    save_pixel_BMP(0, pixc, data.bi5Width*4, data, bfh.bfOffBits, img);

    unsigned char *pixels = load_pixmap_BMP(data, img, bfh.bfOffBits);
    for(int i = 0; i < data.bi5SizeImage; i++)
        printf("[%X: %d], ", pixels[i], pixels[i]);
    printf("\n");
    free(pixels);

    printf("%d\n", data.bi5BitCount);
    printf("%d\n", data.bi5Width);

    fclose(img);
    return 0;
}
