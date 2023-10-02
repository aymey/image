#include "jpeg.h"

bool validate_JPEG(uint16_t signature) {
    switch(signature) {
        case SOI:
            return true;
        default:
            return false;
    }
}
