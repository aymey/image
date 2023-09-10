// test files: https://eclecticgeek.com/dompdf/core_tests/image_bmp.html
#ifndef __BITMAP_H_
#define __BITMAP_H_
// #pragma pack(push, 1)
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define BM_BITMAPFILEHEADER 14*2

typedef struct {
    const uint8_t r;
    const uint8_t g;
    const uint8_t b;
} __attribute__((packed)) Color;

typedef struct tagBITMAPFILEHEADER {
    const uint16_t bfType;
    const uint32_t bfSize;
    const uint16_t bfReserved1;
    const uint16_t bfReserved2;
    const uint32_t bfOffBits;
} __attribute__((packed)) BITMAPFILEHEADER;

typedef long FXPT2DOT30;

typedef struct tagCIEXYZ {
    FXPT2DOT30 ciexyzX;
    FXPT2DOT30 ciexyzY;
    FXPT2DOT30 ciexyzZ;
} CIEXYZ;

typedef struct tagICEXYZTRIPLE {
    CIEXYZ ciexyzRed;
    CIEXYZ ciexyzGreen;
    CIEXYZ ciexyzBlue;
} CIEXYZTRIPLE;

enum BMP_SIGNATURE { // TODO: check endianness (little endian)
    BM = 0x4D42, // Windows 3.1x, 95, NT, ... etc.
    BA = 0x4142, // OS/2 struct bitmap array
    CI = 0x4943, // OS/2 struct color icon
    CP = 0x5043, // OS/2 const color pointer
    IC = 0x4349, // OS/2 struct icon
    PT = 0x4950  // OS/2 pointer
};

// header size that corresponds to header struct
enum BMP_STRUCT {
    CORE = 12,
    CORE2 = 64,
    CORE2V2 = 16,
    INFO = 40,
    INFOV2 = 52,
    INFOV3 = 56,
    INFOV4 = 108, // 140?
    INFOV5 = 124 // 156?
};

typedef struct {
    const uint32_t bcSize;
    const uint16_t bcWidth;
    const uint16_t bcHeight;
    const uint16_t bcPlanes;
    const uint16_t bcBitCount;
} __attribute__((packed)) BITMAPCOREHEADER, OS21XBITMAPHEADER;

typedef struct {
    const uint32_t bc2Size;
    const uint16_t bc2Width;
    const uint16_t bc2Height;
    const uint16_t bc2Planes;
    const uint16_t bc2BitCount;
    const uint32_t bc2Compression;
    const uint32_t bc2SizeImage;
    const uint32_t bc2XRes;
    const uint32_t bc2YRes;
    const uint32_t bc2ClrUsed;
    const uint32_t bc2ClrImportant;
    const uint16_t bc2ResUnit;
    const uint16_t bc2Reserved;
    const uint16_t bc2Orientation;
    const uint16_t bc2Halftoning;
    const uint32_t bc2HalftoneSize1;
    const uint32_t bc2HalftoneSize2;
    const uint32_t bc2ColorSpace;
    const uint32_t bc2AppData;
} __attribute__((packed)) BITMAPCOREHEADER2, OS22XBITMAPHEADER;

typedef struct tagBITMAPINFOHEADER {
    const uint32_t biSize;
    const uint32_t biWidth;
    const uint32_t biHeight;
    const uint16_t biPlanes;
    const uint16_t biBitCount;
    const uint32_t biCompression;
    const uint32_t biSizeImage;
    const uint32_t biXPelsPerMeter;
    const uint32_t biYPelsPerMeter;
    const uint32_t biClrUsed;
    const uint32_t biClrImportant;
} __attribute__((packed)) BITMAPINFOHEADER;

typedef struct tagBITMAPV2INFOHEADER {
    const uint32_t bi2Size;
    const uint32_t bi2Width;
    const uint32_t bi2Height;
    const uint16_t bi2Planes;
    const uint16_t bi2BitCount;
    const uint32_t bi2Compression;
    const uint32_t bi2SizeImage;
    const uint32_t bi2XPelsPerMeter;
    const uint32_t bi2YPelsPerMeter;
    const uint32_t bi2ClrUsed;
    const uint32_t bi2ClrImportant;
    const uint32_t bi2RedMask;
    const uint32_t bi2GreenMask;
    const uint32_t bi2BlueMask;
} __attribute((packed)) BITMAPV2INFOHEADER;

typedef struct tagBITMAPV3INFOHEADER {
    const uint32_t bi3Size;
    const uint32_t bi3Width;
    const uint32_t bi3Height;
    const uint16_t bi3Planes;
    const uint16_t bi3BitCount;
    const uint32_t bi3Compression;
    const uint32_t bi3SizeImage;
    const uint32_t bi3XPelsPerMeter;
    const uint32_t bi3YPelsPerMeter;
    const uint32_t bi3ClrUsed;
    const uint32_t bi3ClrImportant;
    const uint32_t bi3RedMask;
    const uint32_t bi3GreenMask;
    const uint32_t bi3BlueMask;
    const uint32_t bi3AlphaMask;
} __attribute((packed)) BITMAPV3INFOHEADER;

typedef struct tagBITMAPV4INFOHEADER {
    const uint32_t bi4Size;
    const uint32_t bi4Width;
    const uint32_t bi4Height;
    const uint16_t bi4Planes;
    const uint16_t bi4BitCount;
    const uint32_t bi4Compression;
    const uint32_t bi4SizeImage;
    const uint32_t bi4XPelsPerMeter;
    const uint32_t bi4YPelsPerMeter;
    const uint32_t bi4ClrUsed;
    const uint32_t bi4ClrImportant;
    const uint32_t bi4RedMask;
    const uint32_t bi4GreenMask;
    const uint32_t bi4BlueMask;
    const uint32_t bi4AlphaMask;
    const CIEXYZTRIPLE bi4Endpoints;
    const uint32_t bi4GammaRed;
    const uint32_t bi4GammaGreen;
    const uint32_t bi4GammaBlue;
} __attribute((packed)) BITMAPV4INFOHEADER;

typedef struct tagBITMAPV5INFOHEADER {
    const uint32_t bi5Size;
    const uint32_t bi5Width;
    const uint32_t bi5Height;
    const uint16_t bi5Planes;
    const uint16_t bi5BitCount;
    const uint32_t bi5Compression;
    const uint32_t bi5SizeImage;
    const uint32_t bi5XPelsPerMeter;
    const uint32_t bi5YPelsPerMeter;
    const uint32_t bi5ClrUsed;
    const uint32_t bi5ClrImportant;
    const uint32_t bi5RedMask;
    const uint32_t bi5GreenMask;
    const uint32_t bi5BlueMask;
    const uint32_t bi5AlphaMask;
    const CIEXYZTRIPLE bi5Endpoints;
    const uint32_t bi5GammaRed;
    const uint32_t bi5GammaGreen;
    const uint32_t bi5GammaBlue;
    const uint32_t bi5Intent;
    const uint32_t bi5ProfileData;
    const uint32_t bi5ProfileSize;
    const uint32_t bi5Reserved;
} __attribute((packed)) BITMAPV5INFOHEADER;

bool validate_BMP(uint16_t signature);
void header_BMP(uint32_t size);
void *read_pixmap_BMP(BITMAPV5INFOHEADER info, FILE *img, uint32_t OffBits);
void zero_BMP(uint32_t size, BITMAPV5INFOHEADER *zeroer);
void write_pixel_BMP(uint32_t dest, Color source, uint32_t count, BITMAPV5INFOHEADER info, uint32_t OffBits, FILE *img);

// #pragma pack(pop)
#endif // __FORMATS_H_
