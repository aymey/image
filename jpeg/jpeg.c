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

void scanfor_JPEG(uint16_t marker, void (*callback)(int, uint16_t, FILE *), FILE *img) {
    fseek(img, 0, SEEK_SET);
    bool file_status = true; // has not reached EOI
    uint16_t segment = NUL;
    for(int offset = 0; file_status; offset += MARKER_SIZE) {
        fread(&segment, MARKER_SIZE, 1, img);
        callback(offset, segment, img);
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
            fread(&table[current_table].table, 128, 1, img);
            for(uint8_t i = 0; i < 64; i++)
                endian16_JPEG(&table[current_table].table[i]);
            length -= 128;
        } else {  // 8 bit
            fread(&table[current_table].table, 64, 1, img);
            length -= 64;
        }
        current_table++;
    }

    return table;
}

uint8_t get_QT_amount_JPEG(void) {
    return current_table;
}
