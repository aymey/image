#include <stdio.h>

#include "bitmap.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("supply an input and output image path\n");
        return 1;
    }

    FILE *img = fopen(argv[1], "r+w+b");
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

    BITMAPV5INFOHEADER data;
    fread(&data, sizeof(BITMAPV5INFOHEADER), 1, img);
    zero_BMP(data.bi5Size, &data);

    unsigned char *pixels = get_BMP(data, img, bfh.bfOffBits);
    for(int i = 0; i < data.bi5SizeImage; i++)
        printf("%d, ", pixels[i]);
    printf("\n");

    fclose(img);
    return 0;
}
