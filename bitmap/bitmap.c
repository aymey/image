#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "bitmap.h"


// TODO: bit pack pixel information incase of bpp not being a multiple of 8. How does anyone else handle this?
// TODO: colorspace interpretation
// TODO: wrongly padding possibly?

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

BITMAPFILEHEADER load_BFH_BMP(FILE *img) {
    fseek(img, 0, SEEK_SET);
    BITMAPFILEHEADER BFH;
    fread(&BFH, sizeof(BITMAPFILEHEADER), 1, img);
    return BFH;
} // TODO: esure file pointer automatically changes

void save_BFH_BMP(BITMAPFILEHEADER BFH, FILE *img) {
    fseek(img, 0, SEEK_SET);
    fwrite(&BFH, BITMAPFILEHEADER_BMP, 1, img);
}

void zero_DIB_BMP(uint32_t size, BITMAPV5INFOHEADER *zeroer) {
    memset((char *)zeroer + size, 0, sizeof(BITMAPV5INFOHEADER) - size);
}

BITMAPV5INFOHEADER load_DIB_BMP(FILE *img) {
    fseek(img, BITMAPFILEHEADER_BMP, SEEK_SET);
    BITMAPV5INFOHEADER DIB;
    fread(&DIB, sizeof(BITMAPV5INFOHEADER), 1, img);
    zero_DIB_BMP(DIB.bi5Size, &DIB);
    return DIB;
}

void save_DIB_BMP(BITMAPV5INFOHEADER DIB, FILE *img) {
    fseek(img, 0, SEEK_SET);
    fwrite(&DIB, DIB.bi5Size, 1, img);
}

void *load_pixmap_BMP(BITMAPV5INFOHEADER info, FILE *img, uint32_t OffBits) {
    const uint32_t image_size = info.bi5SizeImage;
    void *pixels = malloc(image_size);
    fseek(img, OffBits, SEEK_SET);
    fread(pixels, ceil(info.bi5BitCount / 8.), image_size, img);
    return pixels;
}

void *load_pixels_BMP(BITMAPV5INFOHEADER info, FILE *img, uint32_t OffBits) {
    const uint32_t image_size = info.bi5SizeImage;
    const int colour_amount = image_size*ceil((info.bi5BitCount / 3.) / 8.);
    void *colours = malloc(colour_amount);
    fseek(img, OffBits, SEEK_SET);
    fread(colours, ceil((info.bi5BitCount / 3.) / 8.), colour_amount, img);
    return colours;
}

void save_pixel_BMP(uint32_t dest, Colour_BMP src, uint32_t count, BITMAPV5INFOHEADER info, uint32_t OffBits, FILE *img) {
    const uint8_t byte_count = ceil(info.bi5BitCount / 8.);
    fseek(img, byte_count*(OffBits + dest), SEEK_SET);
    const uint8_t pad = 0;
    uint8_t padding = (4 - (((int)ceil((info.bi5BitCount)/8.) * info.bi5Width) % 4) % 4);
    if(padding == 4)
        padding = 0;
    const uint8_t part = ceil((info.bi5BitCount / 3.) / 8.);
    for(uint32_t i = 0; i < count; i++) {
        fwrite(&src.b, part, 1, img);
        fwrite(&src.g, part, 1, img);
        fwrite(&src.r, part, 1, img);
        if((i+1) % info.bi5Width == 0)
            fwrite(&pad, 1, padding, img);
    }
}
