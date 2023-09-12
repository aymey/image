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

BITMAPV5INFOHEADER load_DIB_BMP(FILE *img) {
    BITMAPV5INFOHEADER DIB;
    fread(&DIB, sizeof(BITMAPV5INFOHEADER), 1, img);
    zero_DIB_BMP(DIB.bi5Size, &DIB);
    return DIB;
}

BITMAPFILEHEADER load_BFH_BMP(FILE *img) {
    BITMAPFILEHEADER BFH;
    fread(&BFH, sizeof(BITMAPFILEHEADER), 1, img);
    return BFH;
}

void header_BMP(uint32_t size) {

}

void zero_DIB_BMP(uint32_t size, BITMAPV5INFOHEADER *zeroer) {
    memset((char *)zeroer + size, 0, sizeof(BITMAPV5INFOHEADER) - size);
}

void *read_pixmap_BMP(BITMAPV5INFOHEADER info, FILE *img, uint32_t OffBits) {
    const uint32_t image_size = info.bi5SizeImage;
    void *pixels = malloc(image_size);
    fseek(img, OffBits, SEEK_SET);
    fread(pixels, ceil(info.bi5BitCount / 8.), image_size, img); // TODO: non whole bytes work weirdly
    return pixels;
}

void write_pixel_BMP(uint32_t dest, Color src, uint32_t count, BITMAPV5INFOHEADER info, uint32_t OffBits, FILE *img) {
    const uint8_t byte_count = ceil(info.bi5BitCount / 8.);
    fseek(img, byte_count*(OffBits + dest), SEEK_SET);
    const uint8_t pad = 0;
    uint8_t padding = (4 - (((int)ceil((info.bi5BitCount)/8.) * info.bi5Width) % 4) % 4);
    if(padding == 4)
        padding = 0;
    // const uint8_t part = ceil(info.bi5BitCount / 8.);
    const uint8_t part = 1;
    for(uint32_t i = 0; i < count; i++) {
        fwrite(&src.b, part, 1, img);
        fwrite(&src.g, part, 1, img);
        fwrite(&src.r, part, 1, img);
        if(!((i+1) % info.bi5Width))
            fwrite(&pad, 1, padding, img);
    }
}
