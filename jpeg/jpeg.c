#include <stdio.h>

#include "jpeg.h"

void endian16_JPEG(uint16_t *value) {
    *value = *value >> 8 | *value << 8;
}

uint16_t load_signature(FILE *img) {
    fseek(img, 0, SEEK_SET);
    uint16_t signature;
    fread(&signature, MARKER_SIZE, 1, img);
    return signature;
}

bool validate_JPEG(uint16_t signature) {
    return signature == SOI;
}

void scanfor_JPEG(uint16_t marker, void (*callback)(uint16_t, FILE *), FILE *img) {
    fseek(img, 0, SEEK_SET);
    bool file_status = true; // has not reached EOI
    uint16_t segment = NUL;
    while(file_status) {
        fread(&segment, MARKER_SIZE, 1, img);
        callback(segment, img);
        if(segment == EOI || segment == 0xFFD9)
            file_status = false;
    }
}

JFIF_APP0 load_APP0_JPEG(FILE *img) {
    fseek(img, MARKER_SIZE, SEEK_SET);
    JFIF_APP0 segment;
    fread(&segment, sizeof(JFIF_APP0), 1, img);

    // convert to big endian because JPEG standard is big endian
    endian16_JPEG(&segment.marker);
    endian16_JPEG(&segment.length);
    endian16_JPEG(&segment.version);
    endian16_JPEG(&segment.Xdensity);
    endian16_JPEG(&segment.Ydensity);

    return segment;
}

void load_thumbnail_data(FILE *img) {

}

const uint8_t zigzag_map[64] = {
     0,  1,  8, 16,  9,  2,  3, 10,
    17, 24, 32, 25, 18, 11,  4,  5,
    12, 19, 26, 33, 40, 48, 41, 34,
    27, 20, 13,  6,  7, 14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36,
    29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46,
    53, 60, 61, 54, 47, 55, 62, 63
};

uint8_t current_table = 0;
Quantization_Table* load_DQT_JPEG(FILE *img) {
    fseek(img, -MARKER_SIZE, SEEK_CUR); // to include marker
    static Quantization_Table table[4];
    fread(&table, MARKER_SIZE, 2, img);
    endian16_JPEG(&table[current_table].marker);
    endian16_JPEG(&table[current_table].length);

    int16_t length = table[current_table].length - MARKER_SIZE;
    while(length > 0 && current_table < 4) {
        table[current_table].marker = table[0].marker;
        table[current_table].length = table[0].length;

        fread(&table[current_table].info, 1, 1, img);
        length--;
        if(table[current_table].info >> 4) { // 16 bit
            fread(&table[current_table].table, 2, 64, img);
            for(uint8_t i = 0; i < 64; i++)
                endian16_JPEG(&table[current_table].table[i]);
            length -= 128;
        } else {  // 8 bit
            fread(&table[current_table].table, 1, 64, img);
            length -= 64;
        }
        // TODO: read with zig zag map to array
        current_table++;
    }

    return table;
}

uint8_t get_QT_amount_JPEG(void) {
    // maybe just extern current_table instead of a getter?
    return current_table;
}

Frame load_SOF0_JPEG(FILE *img) {
    fseek(img, -MARKER_SIZE, SEEK_CUR); // to include marker
    Frame segment;
    fread(&segment, sizeof(Frame)-sizeof(struct component_info[4]), 1, img);
    if(segment.precision != 8) {
        printf("ignoring invalid precision value: expected 8 found %d\n", segment.precision);
        // return segment;
    }
    endian16_JPEG(&segment.marker);
    endian16_JPEG(&segment.length);
    endian16_JPEG(&segment.width);
    endian16_JPEG(&segment.height);
    // if(!segment.width || !segment.height) {}
    // TODO: support all number of components
    bool zero = false;
    for(uint8_t i = 0; i < segment.components; i++) {
        uint8_t component = 0;
        fread(&component, 1, 1, img);
        if(!component)
            zero = true;
        if(!zero)
            component--;
        segment.component_info[component].id = component+1;
        fread(&segment.component_info[component].sampling_factor, 1, 1, img);
        fread(&segment.component_info[component].table, 1, 1, img);
        if(segment.component_info[component].table > 3)
            printf("invalid quantization table id %d\n", segment.component_info[component].table);
    }

    if(segment.length - (sizeof(Frame)-sizeof(struct component_info[4]) - MARKER_SIZE) - segment.components*sizeof(struct component_info[4]) == 0)
        printf("invalid SOF segment (length)\n");
    return segment;
}

Define_Restart_Interval load_DRI_JPEG(FILE *img) {
    fseek(img, -MARKER_SIZE, SEEK_CUR);
    Define_Restart_Interval segment;
    fread(&segment, sizeof(segment), 1, img);
    endian16_JPEG(&segment.marker);
    endian16_JPEG(&segment.length);
    endian16_JPEG(&segment.interval);
    if(segment.length - (sizeof(segment) - MARKER_SIZE) != 0)
        printf("invalid DRI segment (length)\n");
    return segment;
}

Huffman_Table load_DHT_JPEG(FILE *img) {
    fseek(img, -MARKER_SIZE, SEEK_CUR);
    Huffman_Table table;
    fread(&table, MARKER_SIZE, 2, img);
    endian16_JPEG(&table.marker);
    endian16_JPEG(&table.length);
    int16_t length = table.length; // TODO: potential overflow
    length -= MARKER_SIZE;
    while(length > 0) {
        fread(&table.info, 1, 1, img);
        length--;
        // if(table.info >> 4) // AC
            // Huffm
        fread(&table.codes, 1, 16, img);
        length -= 16;

    }

    return table;
}
