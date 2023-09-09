#include <stdint.h>
#include <stdbool.h>

#include "bitmap.h"

bool validate_BMP(uint16_t signature) {
    switch(signature) {
        case BM:
        case BA:
        case CI:
        case CP:
        case IC:
        case PT:
            return true;
        default:
            return false;
    }
}

void structure_BMP(uint16_t signature) {

}
