#include <stdio.h>

#include "jpeg.h"

void callback(int offset, uint16_t segment, FILE *img) {
    if(IS_MARKER_APP(segment)) {
        uint16_t length = 0;
        fread(&length, MARKER_SIZE, 1, img);
        endian16_JPEG(&length);
        fseek(img, length, SEEK_CUR);
    }
    if(segment == DQT) {
        Quantization_Table *table = load_DQT_JPEG(img);
        for(int j = 0; j < get_QT_amount_JPEG(); j++) {
            for(int i = 0; i < 64; i++) {
                if(i % 8 == 0)
                    printf("\n");
                printf("%d ", table[j].table[i]);
            }
            printf("\n\n");
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
