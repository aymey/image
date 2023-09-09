#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "bitmap.h"

bool validate_BMP(uint16_t signature) {
    switch(signature) {
        case BM:
        case BA:
        case CI:
        case CP:
        case IC:
        case PT:
            return true;
        default:
            return false;
    }
}

void header_BMP(uint32_t size) {

}

void zero_BMP(uint32_t size, BITMAPV5INFOHEADER *zeroer) {
    memset((char *)zeroer + size, 0, sizeof(BITMAPV5INFOHEADER) - size);
}

void *get_BMP(BITMAPV5INFOHEADER info, FILE *img, uint32_t OffBits) {
    uint32_t image_size = info.bi5SizeImage;
    void *pixels = malloc(image_size);
    fseek(img, OffBits, SEEK_SET);
    fread(pixels, ceil(info.bi5BitCount / 8.), image_size, img);
    return pixels;
}

void set_BMP() {

}
