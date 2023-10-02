#ifndef __JPEG_H_
#define __JPEG_H_

#include <stdint.h>
#include <stdbool.h>

enum JFIF_MARKER {
    NUL  = 0x00 | 0x00FF, // JPEG reserved
    TEM  = 0x01 | 0x00FF, // Temporary marker for arithmetic encoding
    RES  = 0x02 | 0x00FF, // reserved
    SOF0 = 0xC0 | 0x00FF, // Start Of Frame (baseline DCT)
    SOF1 = 0xC0 | 0x00FF, // Start Of Frame (extended sequential, huffman)
    SOF2 = 0xC2 | 0x00FF, // Start of Frame (progressive DCT, huffman)
    SOF3 = 0xC3 | 0x00FF, // Start of Frame (lossless, huffman),                        libjpeg-unsupported
    SOF4 = 0xC4 | 0x00FF, // Start of Frame (DHT define huffman tables)
    DHT  = 0xC4 | 0x00FF, // Define Huffman Tables
    SOF5 = 0xC5 | 0x00FF, // Start of Frame (differential sequential, huffman),         libjpeg-unsupported
    SOF6 = 0xC6 | 0x00FF, // Start Of Frame (differential progressive, huffman),        libjpeg-unsupported
    SOF7 = 0xC7 | 0x00FF, // Start Of Frame (differential lossless, huffman),           libjpeg-unsupported
    SOF8 = 0xC8 | 0x00FF, // Start Of Frame (JPG reserved for JPEG extension),          libjpeg-unsupported
    JPG  = SOF8,          // JPG reserved for JPEG extension
    SOF9 = 0xC9 | 0x00FF, // Start Of Frame (extended sequential, arithmetic)
    SOF10= 0xCA | 0x00FF, // Start Of Frame (progressive, arithmetic)
    SOF11= 0xCB | 0x00FF, // Start Of Frame (lossless, arithmetic),                     libjpeg-unsupported
    SOF12= 0xCC | 0x00FF, // Start Of Frame (DAC define arithmetic coding conditioning),libjpeg-skipped
    DAC  = SOF12,         // Define arithmetic coding conditioning
    SOF13= 0xCD | 0x00FF, // Start Of Frame (differential sequential, arithmetic),      libjpeg-unsupported
    SOF14= 0xCE | 0x00FF, // Start Of Frame (differential progressive, arithmetic),     libjpeg-unsupported
    SOF15= 0xCF | 0x00FF, // Start Of Frame (differential lossless, arithmetic),        libjpeg-unsupported
    RST0 = 0xD0 | 0x00FF, // Restart
    RST1 = 0xD1 | 0x00FF, // Restart
    RST2 = 0xD2 | 0x00FF, // Restart
    RST3 = 0xD3 | 0x00FF, // Restart
    RST4 = 0xD4 | 0x00FF, // Restart
    RST5 = 0xD5 | 0x00FF, // Restart
    RST6 = 0xD6 | 0x00FF, // Restart
    RST7 = 0xD7 | 0x00FF, // Restart
    SOI  = 0xD8 | 0x00FF, // Start Of Image
    EOI  = 0xD9 | 0x00FF, // End Of Image
    SOS  = 0xDA | 0x00FF, // Start Of Scan
    DQT  = 0xDB | 0x00FF, // Define Quantization Table/Matrix
    DNL  = 0xDC | 0x00FF, // Define Number of Lines,                                    libjpeg-skipped
    DRI  = 0xDD | 0x00FF, // Define Restart Interval
    DHP  = 0xDE | 0x00FF, // Define Hierarchial Progression
    EXP  = 0xDF | 0x00FF, // Expand reference components
    COM  = 0xFE | 0x00FF, // extension data (Comment)
    APP0 = 0xE0 | 0x00FF, // application segment 0 (JFIF (len >=14) / JFXX (len >= 6) / AVI MJPEG)
    APP1 = 0xE1 | 0x00FF, // application segment 1 (EXIF/XMP/XAP ?)
    APP2 = 0xE2 | 0x00FF, // application segment 2 (FlashPix / ICC)
    APP3 = 0xE3 | 0x00FF, // application segment 3 (Kodak/...)
    APP4 = 0xE4 | 0x00FF, // application segment 4 (FlashPix/...)
    APP5 = 0xE5 | 0x00FF, // application segment 5 (Ricoh...)
    APP6 = 0xE6 | 0x00FF, // application segment 6 (GoPro...)
    APP7 = 0xE7 | 0x00FF, // application segment 7 (Pentax/Qualcomm)
    APP8 = 0xE8 | 0x00FF, // application segment 8 (Spiff)
    APP9 = 0xE9 | 0x00FF, // application segment 9 (MediaJukebox)
    APP10= 0xEA | 0x00FF, // application segment 10 (PhotoStudio)
    APP11= 0xEB | 0x00FF, // application segment 11 (HDR)
    APP12= 0xEC | 0x00FF, // application segment 12 (photoshoP ducky / savE foR web)
    APP13= 0xED | 0x00FF, // application segment 13 (photoshoP savE As)
    APP14= 0xEE | 0x00FF, // application segment 14 ("adobe" (length = 12))
    APP15= 0xEF | 0x00FF, // application segment 15 (GraphicConverter)
    JPG0 = 0xF0 | 0x00FF, // JPG extension data,                                        libjpeg-unsupported
    JPG1 = 0xF1 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG2 = 0xF2 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG3 = 0xF3 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG4 = 0xF4 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG5 = 0xF5 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG6 = 0xF6 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG7 = 0xF7 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    SOF48= JPG7,          // Start Of Frame (JPEG-LS)
    JPG8 = 0xF8 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    LSE  = JPG8,          // extension parameters (JPEG-LS)
    JPG9 = 0xF9 | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG10= 0xFA | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG11= 0xFB | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG12= 0xFC | 0x00FF, // JPG extension data,                                        libjpeg-unknown
    JPG13= 0xFD | 0x00FF, // JPG extension data,                                        libjpeg-unsupported
    TRAILER               // Trailer
};

enum JP2_MAGIC {
    /* delimiters */
    J2_SOC  = 0x4F | 0x00FF, // Start Of Codestream
    J2_SOT  = 0x90 | 0x00FF, // Start Of Tile
    J2_SOD  = 0x93 | 0x00FF, // Start Of ???
    J2_EOC  = 0xD9 | 0x00FF, // End Of Codestream (overlaps EOI)
    /* fixed information segment */
    J2_SIZ  = 0x51 | 0x00FF, // image and tile Size
    /* functional segments */
    J2_COD  = 0x52 | 0x00FF, // Coding style Default
    J2_COC  = 0x53 | 0x00FF, // Coding style Component
    J2_RNG  = 0x5E | 0x00FF, // Region of Interest
    J2_QCD  = 0x5C | 0x00FF, // Quantization Default
    J2_QCC  = 0x5D | 0x00FF, // Quantization Component
    J2_POC  = 0x5F | 0x00FF, // Progression Order Change
    /* pointer segments */
    J2_TLM  = 0x55 | 0x00FF, // Tile part Lengths
    J2_PLM  = 0x57 | 0x00FF, // Packet Length (main header)
    J2_PLT  = 0x58 | 0x00FF, // Packet Length (tile part header)
    J2_PPM  = 0x60 | 0x00FF, // Packed Packet headers (main header)
    J2_PPT  = 0x61 | 0x00FF, // Packed Packet headers (tile part header)
    /* bitstream internal markers and segments */
    J2_SOP  = 0x91 | 0x00FF, // Start Of Packet
    J2_EPH  = 0x92 | 0x00FF, // End of Packet Header
    /* informational segments */
    J2_CRG  = 0x63 | 0x00FF, // Component Registration
    J2_COM  = 0x64 | 0x00FF, // Comment
    J2_CBD  = 0x78 | 0x00FF, // Component Bit depth Definition
    J2_MCT  = 0x74 | 0x00FF, // Multiple Component Transform
    J2_MCC  = 0x75 | 0x00FF, // Multiple Component Collection
    J2_MCO  = 0x77 | 0x00FF, // Multiple Component transformation Ordering
    /* Part 8: Secure JPEG 2000 */
    J2_SEC  = 0x65 | 0x00FF, // Secured Codestream
    J2_INSEC= 0x94 | 0x00FF, // Insecure Codestream
    /* Part 11: JPEG 2000 for Wireless */
    J2_EPC  = 0x68 | 0x00FF, // Error Protection Capability
    J2_EPB  = 0x66 | 0x00FF, // Error Protection Block
    J2_ESD  = 0x67 | 0x00FF, // Error Sensitivity Descriptor
    J2_RED  = 0x69 | 0x00FF, // Residual Error Descriptor
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
} JFXX_APP0; // JFIF extension APP0 marker segment

bool validate_JPEG(uint16_t signature);


#endif // __JPEG_H_
