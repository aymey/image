// test images: https://eclecticgeek.com/dompdf/core_tests/image_bmp.html
#ifndef __BITMAP_H_
#define __BITMAP_H_
// #pragma pack(push, 1)
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define BITMAPFILEHEADER_BMP 14

typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} __attribute__((packed)) Colour_BMP;

typedef struct tagBITMAPFILEHEADER {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
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
    CI = 0x4943, // OS/2 struct colour icon
    CP = 0x5043, // OS/2 const colour pointer
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
    uint32_t bcSize;
    uint16_t bcWidth;
    uint16_t bcHeight;
    uint16_t bcPlanes;
    uint16_t bcBitCount;
} __attribute__((packed)) BITMAPCOREHEADER, OS21XBITMAPHEADER;

typedef struct {
    uint32_t bc2Size;
    uint16_t bc2Width;
    uint16_t bc2Height;
    uint16_t bc2Planes;
    uint16_t bc2BitCount;
    uint32_t bc2Compression;
    uint32_t bc2SizeImage;
    uint32_t bc2XRes;
    uint32_t bc2YRes;
    uint32_t bc2ClrUsed;
    uint32_t bc2ClrImportant;
    uint16_t bc2ResUnit;
    uint16_t bc2Reserved;
    uint16_t bc2Orientation;
    uint16_t bc2Halftoning;
    uint32_t bc2HalftoneSize1;
    uint32_t bc2HalftoneSize2;
    uint32_t bc2ColorSpace;
    uint32_t bc2AppData;
} __attribute__((packed)) BITMAPCOREHEADER2, OS22XBITMAPHEADER;

typedef struct tagBITMAPINFOHEADER {
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} __attribute__((packed)) BITMAPINFOHEADER;

typedef struct tagBITMAPV2INFOHEADER {
    uint32_t bi2Size;
    uint32_t bi2Width;
    uint32_t bi2Height;
    uint16_t bi2Planes;
    uint16_t bi2BitCount;
    uint32_t bi2Compression;
    uint32_t bi2SizeImage;
    uint32_t bi2XPelsPerMeter;
    uint32_t bi2YPelsPerMeter;
    uint32_t bi2ClrUsed;
    uint32_t bi2ClrImportant;
    uint32_t bi2RedMask;
    uint32_t bi2GreenMask;
    uint32_t bi2BlueMask;
} __attribute((packed)) BITMAPV2INFOHEADER;

typedef struct tagBITMAPV3INFOHEADER {
    uint32_t bi3Size;
    uint32_t bi3Width;
    uint32_t bi3Height;
    uint16_t bi3Planes;
    uint16_t bi3BitCount;
    uint32_t bi3Compression;
    uint32_t bi3SizeImage;
    uint32_t bi3XPelsPerMeter;
    uint32_t bi3YPelsPerMeter;
    uint32_t bi3ClrUsed;
    uint32_t bi3ClrImportant;
    uint32_t bi3RedMask;
    uint32_t bi3GreenMask;
    uint32_t bi3BlueMask;
    uint32_t bi3AlphaMask;
} __attribute((packed)) BITMAPV3INFOHEADER;

typedef struct tagBITMAPV4INFOHEADER {
    uint32_t bi4Size;
    uint32_t bi4Width;
    uint32_t bi4Height;
    uint16_t bi4Planes;
    uint16_t bi4BitCount;
    uint32_t bi4Compression;
    uint32_t bi4SizeImage;
    uint32_t bi4XPelsPerMeter;
    uint32_t bi4YPelsPerMeter;
    uint32_t bi4ClrUsed;
    uint32_t bi4ClrImportant;
    uint32_t bi4RedMask;
    uint32_t bi4GreenMask;
    uint32_t bi4BlueMask;
    uint32_t bi4AlphaMask;
    CIEXYZTRIPLE bi4Endpoints;
    uint32_t bi4GammaRed;
    uint32_t bi4GammaGreen;
    uint32_t bi4GammaBlue;
} __attribute((packed)) BITMAPV4INFOHEADER;

typedef struct tagBITMAPV5INFOHEADER {
    uint32_t bi5Size;
    uint32_t bi5Width;
    uint32_t bi5Height;
    uint16_t bi5Planes;
    uint16_t bi5BitCount;
    uint32_t bi5Compression;
    uint32_t bi5SizeImage;
    uint32_t bi5XPelsPerMeter;
    uint32_t bi5YPelsPerMeter;
    uint32_t bi5ClrUsed;
    uint32_t bi5ClrImportant;
    uint32_t bi5RedMask;
    uint32_t bi5GreenMask;
    uint32_t bi5BlueMask;
    uint32_t bi5AlphaMask;
    CIEXYZTRIPLE bi5Endpoints;
    uint32_t bi5GammaRed;
    uint32_t bi5GammaGreen;
    uint32_t bi5GammaBlue;
    uint32_t bi5Intent;
    uint32_t bi5ProfileData;
    uint32_t bi5ProfileSize;
    uint32_t bi5Reserved;
} __attribute((packed)) BITMAPV5INFOHEADER;

/* general */
bool validate_BMP(uint16_t signature);                        // verifies if the file is a bitmap file via a signature
/* BFH */
BITMAPFILEHEADER load_BFH_BMP(FILE *img);                     // reads the BFH
void save_BFH_BMP(BITMAPFILEHEADER BFH, FILE *img);           // writes a BFH
/* DIB */
void zero_DIB_BMP(uint32_t size, BITMAPV5INFOHEADER *zeroer); // clears unused members of the BITMAPV5INFOHEADER
BITMAPV5INFOHEADER load_DIB_BMP(FILE *img);                   // reads the DIB
void save_DIB_BMP(BITMAPV5INFOHEADER DIB, FILE *img);         // writes a DIB
/* pixel */
void *load_pixmap_BMP(BITMAPV5INFOHEADER info, FILE *img, uint32_t OffBits); // reads the pixmap
void *load_pixels_BMP(BITMAPV5INFOHEADER info, FILE *img, uint32_t OffBits); // reads pixels
void save_pixel_BMP(uint32_t dest, Colour_BMP source, uint32_t count, BITMAPV5INFOHEADER info, uint32_t OffBits, FILE *img); // writes pixels

// #pragma pack(pop)
#endif // __FORMATS_H_
