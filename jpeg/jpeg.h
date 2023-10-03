#ifndef __JPEG_H_
#define __JPEG_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

enum JFIF_MARKER {
    NUL  = 0x0000 | 0x00FF, // JPEG reserved
    TEM  = 0x0100 | 0x00FF, // Temporary marker for arithmetic encoding
    RES  = 0x0200 | 0x00FF, // reserved
    SOF0 = 0xC000 | 0x00FF, // Start Of Frame (baseline DCT)
    SOF1 = 0xC000 | 0x00FF, // Start Of Frame (extended sequential, huffman)
    SOF2 = 0xC200 | 0x00FF, // Start of Frame (progressive DCT, huffman)
    SOF3 = 0xC300 | 0x00FF, // Start of Frame (lossless, huffman),                        libjpeg-unsupported
    SOF4 = 0xC400 | 0x00FF, // Start of Frame (DHT define huffman tables)
    DHT  = 0xC400 | 0x00FF, // Define Huffman Tables
    SOF5 = 0xC500 | 0x00FF, // Start of Frame (differential sequential, huffman),         libjpeg-unsupported
    SOF6 = 0xC600 | 0x00FF, // Start Of Frame (differential progressive, huffman),        libjpeg-unsupported
    SOF7 = 0xC700 | 0x00FF, // Start Of Frame (differential lossless, huffman),           libjpeg-unsupported
    SOF8 = 0xC800 | 0x00FF, // Start Of Frame (JPG reserved for JPEG extension),          libjpeg-unsupported
    JPG  = SOF8,            // JPG reserved for JPEG extension
    SOF9 = 0xC900 | 0x00FF, // Start Of Frame (extended sequential, arithmetic)
    SOF10= 0xCA00 | 0x00FF, // Start Of Frame (progressive, arithmetic)
    SOF11= 0xCB00 | 0x00FF, // Start Of Frame (lossless, arithmetic),                     libjpeg-unsupported
    SOF12= 0xCC00 | 0x00FF, // Start Of Frame (DAC define arithmetic coding conditioning),libjpeg-skipped
    DAC  = SOF12,           // Define arithmetic coding conditioning
    SOF13= 0xCD00 | 0x00FF, // Start Of Frame (differential sequential, arithmetic),      libjpeg-unsupported
    SOF14= 0xCE00 | 0x00FF, // Start Of Frame (differential progressive, arithmetic),     libjpeg-unsupported
    SOF15= 0xCF00 | 0x00FF, // Start Of Frame (differential lossless, arithmetic),        libjpeg-unsupported
    RST0 = 0xD000 | 0x00FF, // Restart
    RST1 = 0xD100 | 0x00FF, // Restart
    RST2 = 0xD200 | 0x00FF, // Restart
    RST3 = 0xD300 | 0x00FF, // Restart
    RST4 = 0xD400 | 0x00FF, // Restart
    RST5 = 0xD500 | 0x00FF, // Restart
    RST6 = 0xD600 | 0x00FF, // Restart
    RST7 = 0xD700 | 0x00FF, // Restart
    SOI  = 0xD800 | 0x00FF, // Start Of Image
    EOI  = 0xD900 | 0x00FF, // End Of Image
    SOS  = 0xDA00 | 0x00FF, // Start Of Scan
    DQT  = 0xDB00 | 0x00FF, // Define Quantization Table/Matrix
    DNL  = 0xDC00 | 0x00FF, // Define Number of Lines,                                    libjpeg-skipped
    DRI  = 0xDD00 | 0x00FF, // Define Restart Interval
    DHP  = 0xDE00 | 0x00FF, // Define Hierarchial Progression
    EXP  = 0xDF00 | 0x00FF, // Expand reference components
    COM  = 0xFE00 | 0x00FF, // extension data (Comment)
    APP0 = 0xE000 | 0x00FF, // application segment 0 (JFIF (len >=14) / JFXX (len >= 6) / AVI MJPEG)
    APP1 = 0xE100 | 0x00FF, // application segment 1 (EXIF/XMP/XAP ?)
    APP2 = 0xE200 | 0x00FF, // application segment 2 (FlashPix / ICC)
    APP3 = 0xE300 | 0x00FF, // application segment 3 (Kodak/...)
    APP4 = 0xE400 | 0x00FF, // application segment 4 (FlashPix/...)
    APP5 = 0xE500 | 0x00FF, // application segment 5 (Ricoh...)
    APP6 = 0xE600 | 0x00FF, // application segment 6 (GoPro...)
    APP7 = 0xE700 | 0x00FF, // application segment 7 (Pentax/Qualcomm)
    APP8 = 0xE800 | 0x00FF, // application segment 8 (Spiff)
    APP9 = 0xE900 | 0x00FF, // application segment 9 (MediaJukebox)
    APP10= 0xEA00 | 0x00FF, // application segment 10 (PhotoStudio)
    APP11= 0xEB00 | 0x00FF, // application segment 11 (HDR)
    APP12= 0xEC00 | 0x00FF, // application segment 12 (photoshoP ducky / savE foR web)
    APP13= 0xED00 | 0x00FF, // application segment 13 (photoshoP savE As)
    APP14= 0xEE00 | 0x00FF, // application segment 14 ("adobe" (length = 12))
    APP15= 0xEF00 | 0x00FF, // application segment 15 (GraphicConverter)
    JPG0 = 0xF000 | 0x00FF, // JPG extension data,                                        libjpeg-unsupported
    JPG1 = 0xF100 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG2 = 0xF200 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG3 = 0xF300 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG4 = 0xF400 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG5 = 0xF500 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG6 = 0xF600 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG7 = 0xF700 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    SOF48= JPG7,            // Start Of Frame (JPEG-LS)
    JPG8 = 0xF800 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    LSE  = JPG8,            // extension parameters (JPEG-LS)
    JPG9 = 0xF900 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG10= 0xFA00 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG11= 0xFB00 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG12= 0xFC00 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG13= 0xFD00 | 0x00FF, // JPG extension data,                                        libjpeg-unsupported
    TRAILER                 // Trailer
};

enum JP2_MAGIC {
    /* delimiters */
    J2_SOC  = 0x4F00 | 0x00FF, // Start Of Codestream
    J2_SOT  = 0x9000 | 0x00FF, // Start Of Tile
    J2_SOD  = 0x9300 | 0x00FF, // Start Of ???
    J2_EOC  = 0xD900 | 0x00FF, // End Of Codestream (overlaps EOI)
    /* fixed information segment */
    J2_SIZ  = 0x5100 | 0x00FF, // image and tile Size
    /* functional segments */
    J2_COD  = 0x5200 | 0x00FF, // Coding style Default
    J2_COC  = 0x5300 | 0x00FF, // Coding style Component
    J2_RNG  = 0x5E00 | 0x00FF, // Region of Interest
    J2_QCD  = 0x5C00 | 0x00FF, // Quantization Default
    J2_QCC  = 0x5D00 | 0x00FF, // Quantization Component
    J2_POC  = 0x5F00 | 0x00FF, // Progression Order Change
    /* pointer segments */
    J2_TLM  = 0x5500 | 0x00FF, // Tile part Lengths
    J2_PLM  = 0x5700 | 0x00FF, // Packet Length (main header)
    J2_PLT  = 0x5800 | 0x00FF, // Packet Length (tile part header)
    J2_PPM  = 0x6000 | 0x00FF, // Packed Packet headers (main header)
    J2_PPT  = 0x6100 | 0x00FF, // Packed Packet headers (tile part header)
    /* bitstream internal markers and segments */
    J2_SOP  = 0x9100 | 0x00FF, // Start Of Packet
    J2_EPH  = 0x9200 | 0x00FF, // End of Packet Header
    /* informational segments */
    J2_CRG  = 0x6300 | 0x00FF, // Component Registration
    J2_COM  = 0x6400 | 0x00FF, // Comment
    J2_CBD  = 0x7800 | 0x00FF, // Component Bit depth Definition
    J2_MCT  = 0x7400 | 0x00FF, // Multiple Component Transform
    J2_MCC  = 0x7500 | 0x00FF, // Multiple Component Collection
    J2_MCO  = 0x7700 | 0x00FF, // Multiple Component transformation Ordering
    /* Part 8: Secure JPEG 2000 */
    J2_SEC  = 0x6500 | 0x00FF, // Secured Codestream
    J2_INSEC= 0x9400 | 0x00FF, // Insecure Codestream
    /* Part 11: JPEG 2000 for Wireless */
    J2_EPC  = 0x6800 | 0x00FF, // Error Protection Capability
    J2_EPB  = 0x6600 | 0x00FF, // Error Protection Block
    J2_ESD  = 0x6700 | 0x00FF, // Error Sensitivity Descriptor
    J2_RED  = 0x6900 | 0x00FF, // Residual Error Descriptor
};

enum APP_IDENTIFIER {
    JFIF = 0x004649464A,   // JFIF
    EXIF = 0x0066697845    // Exif
};

typedef struct {
    uint16_t marker;
    uint16_t length;
    uint8_t identifier[5]; // TODO: whats best way to do this (custom data type, 4 byte identifier 1 byte null terminator)?
    uint16_t version;
    uint8_t density_units; // 00: no units, 01: ppi, 02: ppcm
    uint16_t Xdensity;
    uint16_t Ydensity;
    uint8_t Xthumbnail;
    uint8_t Ythumbnail;
    // NOTE: this doesnt include thumbnail data as it is of variable size, it must be read seperately
} __attribute__((packed)) JFIF_APP0; // JFIF APP0 marker segment

typedef struct {
    uint16_t marker;
    uint16_t length;
    uint8_t identifier[5]; // TODO: whats best way to do this (custom data type, 4 byte identifier 1 byte null terminator)?
    uint8_t thumbnail_format; // 10: jpeg format, 11: 1 bpp palettized format, 13: 3 bpp rgb format
    // NOTE: this doesnt include thumbnail data as it is of variable size, it must be read seperately
} __attribute__((packed)) JFXX_APP0; // JFIF extension APP0 marker segment

/* general */
bool validate_JPEG(uint16_t signature);
/* segment */
JFIF_APP0 load_JFIF_JPEG(FILE *img);

#endif // __JPEG_H_
