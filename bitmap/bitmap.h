// test images: https://eclecticgeek.com/dompdf/core_tests/image_bmp.html
#ifndef __BITMAP_H_
#define __BITMAP_H_
// #pragma pack(push, 1)
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define BITMAPFILEHEADER_BMP 14

// TODO: channels may not be a byte, do variable size instead
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

enum BMP_SIGNATURE {
    BM = 0x4D42, // Windows 3.1x, 95, NT, ... etc.
    BA = 0x4142, // OS/2 struct bitmap array
    CI = 0x4943, // OS/2 struct colour icon
    CP = 0x5043, // OS/2 const colour pointer
    IC = 0x4349, // OS/2 struct icon
    PT = 0x4950  // OS/2 pointer
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
    uint32_t bV2Size;
    uint32_t bV2Width;
    uint32_t bV2Height;
    uint16_t bV2Planes;
    uint16_t bV2BitCount;
    uint32_t bV2Compression;
    uint32_t bV2SizeImage;
    uint32_t bV2XPelsPerMeter;
    uint32_t bV2YPelsPerMeter;
    uint32_t bV2ClrUsed;
    uint32_t bV2ClrImportant;
    uint32_t bV2RedMask;
    uint32_t bV2GreenMask;
    uint32_t bV2BlueMask;
} __attribute((packed)) BITMAPV2HEADER;

typedef struct tagBITMAPV3INFOHEADER {
    uint32_t bV3Size;
    uint32_t bV3Width;
    uint32_t bV3Height;
    uint16_t bV3Planes;
    uint16_t bV3BitCount;
    uint32_t bV3Compression;
    uint32_t bV3SizeImage;
    uint32_t bV3XPelsPerMeter;
    uint32_t bV3YPelsPerMeter;
    uint32_t bV3ClrUsed;
    uint32_t bV3ClrImportant;
    uint32_t bV3RedMask;
    uint32_t bV3GreenMask;
    uint32_t bV3BlueMask;
    uint32_t bV3AlphaMask;
} __attribute((packed)) BITMAPV3HEADER;

typedef struct tagBITMAPV4INFOHEADER {
    uint32_t bV4Size;
    uint32_t bV4Width;
    uint32_t bV4Height;
    uint16_t bV4Planes;
    uint16_t bV4BitCount;
    uint32_t bV4Compression;
    uint32_t bV4SizeImage;
    uint32_t bV4XPelsPerMeter;
    uint32_t bV4YPelsPerMeter;
    uint32_t bV4ClrUsed;
    uint32_t bV4ClrImportant;
    uint32_t bV4RedMask;
    uint32_t bV4GreenMask;
    uint32_t bV4BlueMask;
    uint32_t bV4AlphaMask;
    CIEXYZTRIPLE bi4Endpoints;
    uint32_t bV4GammaRed;
    uint32_t bV4GammaGreen;
    uint32_t bV4GammaBlue;
} __attribute((packed)) BITMAPV4HEADER;

typedef struct tagBITMAPV5INFOHEADER {
    uint32_t bV5Size;
    uint32_t bV5Width;
    uint32_t bV5Height;
    uint16_t bV5Planes;
    uint16_t bV5BitCount;
    uint32_t bV5Compression;
    uint32_t bV5SizeImage;
    uint32_t bV5XPelsPerMeter;
    uint32_t bV5YPelsPerMeter;
    uint32_t bV5ClrUsed;
    uint32_t bV5ClrImportant;
    uint32_t bV5RedMask;
    uint32_t bV5GreenMask;
    uint32_t bV5BlueMask;
    uint32_t bV5AlphaMask;
    CIEXYZTRIPLE bi5Endpoints;
    uint32_t bV5GammaRed;
    uint32_t bV5GammaGreen;
    uint32_t bV5GammaBlue;
    uint32_t bV5Intent;
    uint32_t bV5ProfileData;
    uint32_t bV5ProfileSize;
    uint32_t bV5Reserved;
} __attribute((packed)) BITMAPV5HEADER;

/* general */
bool validate_BMP(uint16_t signature);                    // verifies if the file is a bitmap file via a signature
/* BFH */
BITMAPFILEHEADER load_BFH_BMP(FILE *img);                 // reads the BFH
void save_BFH_BMP(BITMAPFILEHEADER BFH, FILE *img);       // writes a BFH
/* DIB */
void zero_DIB_BMP(uint32_t size, BITMAPV5HEADER *zeroer); // clears unused members of the BITMAPV5INFOHEADER
BITMAPV5HEADER load_DIB_BMP(FILE *img);                   // reads the DIB
void save_DIB_BMP(BITMAPV5HEADER DIB, FILE *img);         // writes a DIB
/* pixel */
void *load_pixmap_BMP(BITMAPV5HEADER info, FILE *img, uint32_t OffBits); // reads the pixmap
void *load_pixels_BMP(BITMAPV5HEADER info, FILE *img, uint32_t OffBits); // reads pixels
void save_pixel_BMP(uint32_t dest, Colour_BMP source, uint32_t count, BITMAPV5HEADER info, uint32_t OffBits, FILE *img); // writes pixels

// #pragma pack(pop)
#endif // __FORMATS_H_
