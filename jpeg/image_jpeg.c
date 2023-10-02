#include <stdio.h>

#include "jpeg.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("supply and image path\n");
        return 1;
    }
    FILE *img = fopen(argv[1], "r");
    if(!img) {
        printf("unable to open image \"%s\"\n", argv[1]);

    }
    // if(!validate_JPEG())
    return 0;
}
