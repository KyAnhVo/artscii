#include "png_decoder.h"

#include <string>
#include <stdio.h>

const uint8_t PNG_HEADER[8] = {0x89, 0x50, 0x4E, 0x47,0x0D, 0x0A, 0x1A, 0x0A};

Png::Png(std::string file_name) {
    FILE * file = fopen(file_name.c_str(), "r");

    
    // Confirm file is actually a PNG:

    while (file) {
        uint8_t curr_ind = 0;
        uint8_t curr_char = fgetc(file);
        
        if (PNG_HEADER[curr_ind] != curr_char) {
            throw 1;
        }

        curr_ind ++;
    }
}
