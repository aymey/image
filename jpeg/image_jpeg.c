#include <stdio.h>

#include "jpeg.h"

void callback(int offset, uint16_t segment, FILE *img) {
    if(IS_MARKER_APP(segment)) {
        uint16_t length = 0;
        fread(&length, MARKER_SIZE, 1, img);
        endian16_JPEG(&length);
        fseek(img, length, SEEK_CUR);
    } else if(segment == DQT) {
        Quantization_Table *table = load_DQT_JPEG(img);
        printf("=================DQT================");
        for(int j = 0; j < get_QT_amount_JPEG(); j++) {
            printf("\nTable %d:", j);
            for(int i = 0; i < 64; i++) {
                if(i % 8 == 0)
                    printf("\n");
                printf("%d ", table[j].table[zigzag_map[i]]);
            }
            printf("\n");
        }
    } else if(segment == SOF0) {
        Frame frame = load_SOF0_JPEG(img);
        printf("\n================SOF0================\n");
        printf("marker: %X\n", frame.marker);
        printf("length: %d\n", frame.length);
        printf("precision: %d\n", frame.precision);
        printf("width: %d\n", frame.width);
        printf("height: %d\n", frame.height);
        printf("components: %d\n", frame.components);
        for(int i = 0; i < frame.components; i++) {
            printf("id %d: %d\n", i, frame.component_info[i].id);
            printf("sampling_factor %d: %d\n", i, frame.component_info[i].sampling_factor);
            printf("table %d: %d\n", i, frame.component_info[i].table);
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("supply and image path\n");
        return 1;
    }
    FILE *img = fopen(argv[1], "r");
    if(!img) {
        printf("unable to open image \"%s\"\n", argv[1]);
        return 1;
    }
    if(!validate_JPEG(load_signature(img))) {
        printf("\"%s\" was not recognised as a jpeg file\n", argv[1]);
        fclose(img);
        return 1;
    }
    scanfor_JPEG(APP1, &callback, img);

    fclose(img);
    return 0;
}
