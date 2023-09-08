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
        fclose(img);
        return 1;
    }

    fseek(img, 0, SEEK_SET);
    uint16_t signature;
    fread(&signature, sizeof(uint16_t), 1, img);
    if(!validate_BMP(signature)) {
        printf("\"%s\" was not recognised as a bitmap file\n", argv[1]);
        fclose(img);
        return 1;
    }
    BITMAPINFOHEADER data;
    fread(&data, sizeof(BITMAPINFOHEADER), 1, img);
    // fread(&data.width, sizeof(int), 1, img);
    // fseek(img, 4, SEEK_CUR);
    // fread(&data.height, sizeof(int), 1, img);
    printf("size: %d\n", data.biSize);
    printf("width: %ld\nheight: %ld\n", data.biWidth, data.biHeight);

    fclose(img);
    return 0;
}
