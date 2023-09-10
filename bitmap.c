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

void *get_pixmap_BMP(BITMAPV5INFOHEADER info, FILE *img, uint32_t OffBits) {
    uint32_t image_size = info.bi5SizeImage;
    void *pixels = malloc(image_size);
    fseek(img, OffBits, SEEK_SET);
    fread(pixels, ceil(info.bi5BitCount / 8.), image_size, img); // TODO: non whole bytes work weirdly
    return pixels;
}

void set_pixel_BMP(uint32_t dest, Color src, uint32_t count, BITMAPV5INFOHEADER info, uint32_t OffBits, FILE *img) {
    uint8_t byte_count = ceil(info.bi5BitCount / 8.);
    fseek(img, byte_count*(OffBits + dest), SEEK_SET);
    uint8_t padding = (4 - (info.bi5Width * byte_count) % 4) % 4;
    uint8_t pad = 0;
    uint8_t part = ceil(info.bi5BitCount / 8.);
    for(uint32_t i = 0; i < count; i++) {
        fwrite(&src.r, part, 1, img);
        fwrite(&src.g, part, 1, img);
        fwrite(&src.b, part, 1, img);

        fwrite(&pad, padding, 1, img);
    }
}
