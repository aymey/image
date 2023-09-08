#ifndef __BITMAP_H_
#define __BITMAP_H_
// #pragma pack(push, 1)
#include <stdint.h>
#include <stdbool.h>

#define BM_INFO 18

enum BMP_SIGNATURE {
    BM = 0x4D42, // two byte header "BM" (little endian)
    //...
};

typedef struct {
    const uint16_t biSize;
    const long biWidth;
    const long biHeight;
    const uint8_t biPlanes;
    const uint8_t biBitCount;
    const uint16_t biCompression;
    const uint16_t biSizeImage;
    const long long biXPelsPerMeter;
    const long long biYPelsPerMeter;
    const uint16_t biClrUsed;
    const uint16_t biClrImportant;
} __attribute__((packed)) BMP; // bitmap header

bool validate_BMP(uint16_t signature);

// #pragma pack(pop)
#endif // __FORMATS_H_
