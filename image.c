#include <stdio.h>
#include <stdint.h>

#include "bitmap.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("supply an image path\n");
        return 1;
    }

    FILE *img = fopen(argv[1], "rb");
    if(!img) {
        printf("unable to open image \"%s\"\n", argv[1]);
        return 1;
    }

    BITMAPFILEHEADER bfh;
    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, img);
    if(!validate_BMP(bfh.bfType)) {
        printf("\"%s\" was not recognised as a bitmap file\n", argv[1]);
        fclose(img);
        return 1;
    }

    printf("Type (%p): %c\n", bfh.bfType, bfh.bfType);
    printf("Size (%p): %d\n", bfh.bfSize, bfh.bfSize);
    printf("Reserved1 (%p): %d\n", bfh.bfReserved1, bfh.bfReserved1);
    printf("Reserved2 (%p): %d\n", bfh.bfReserved2, bfh.bfReserved2);
    printf("OffBits (%p): %d\n", bfh.bfOffBits, bfh.bfOffBits);

    structure_BMP(bfh.bfType);
    BITMAPINFOHEADER data;
    fread(&data, sizeof(BITMAPINFOHEADER), 1, img);

    printf("size: %p: %d\n", data.biSize, data.biSize);
    printf("width: %p: %d\n", data.biWidth, data.biWidth);
    printf("height: %p: %d\n", data.biHeight, data.biHeight);

    fclose(img);
    return 0;
}
