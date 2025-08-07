#include "png_decoder.h"

#include <string>
#include <stdio.h>
#include <stdexcept>

const uint8_t PNG_HEADER[8] = {0x89, 0x50, 0x4E, 0x47,0x0D, 0x0A, 0x1A, 0x0A};

Png::Png(std::string file_name) {
    FILE * file = fopen(file_name.c_str(), "r");

    // Confirm file is actually a PNG:

    uint8_t byte;
    for (uint8_t ind = 0; ind < 8; ind++) {
        size_t read_bytes = fread(&byte, 1, 1, file);
        if (read_bytes != 1) {
            throw new std::runtime_error("image reading failed");
        }
        if (byte != PNG_HEADER[ind]) {
            throw new std::runtime_error("image is either not png or corrupted");
        }
    }

    // Read IHDR chunk (IHDR = image header)
    //


}
