#include "bitmap.h"

bool validate_BMP(uint16_t signature) {
    return signature == BM ? true : false;
}
