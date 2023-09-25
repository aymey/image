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

    const Colour_BMP pixc = {
        .b = 0,
        .g = 255,
        .r = 0,
    };
    save_pixel_BMP(0, pixc, data.bi5SizeImage, data, bfh.bfOffBits, img);
    printf("test (%X): %d\n", bfh.bfOffBits, bfh.bfOffBits);

    fclose(img);
    return 0;
}
