#include "artscii_processor.h"
#include "img_manager.h"

#include <iostream>
#include <math.h>

uint8_t Artscii_Processor::bitmap_created = 0;

Artscii_Processor::Artscii_Processor(uint32_t height, uint32_t width) {
    this->height    = height;
    this->width     = width;
    uint64_t area   = static_cast<uint64_t>(height) * static_cast<uint64_t>(width); 
    this->luminance = new float[area];
}

Artscii_Processor::~Artscii_Processor() {
    delete[] this->luminance;
}

void Artscii_Processor::gamma_correction(float gamma) {
    if (gamma < 0) {
        std::cerr << "gamma must be more than or equal to 0, reset to 1" << std::endl;
        return;
    }
    for (uint64_t i = 0; i < this->width * this->height; i++) {
        this->luminance[i] = std::pow(this->luminance[i], 1 / gamma);
    }
}

char * Artscii_Processor::gen_artscii() {
    char * artscii = new char[this->width * this->height];
    for (uint64_t i = 0; i < this->width * this->height; i++) {
        uint8_t brightness_level = static_cast<uint8_t>(this->luminance[i] * 7.999f);
        artscii[i] = Artscii_Processor::artscii_chars[brightness_level];
    }
    return artscii;
}

Img_Manager * Artscii_Processor::gen_artscii_bitmap() {
    if (!bitmap_created) Artscii_Processor::gen_artscii_bitmap();

    char * artscii_arr = this->gen_artscii();
    Img_Manager * artscii_img = new Img_Manager(this->height * 8, this->width * 8);
    
    for (uint32_t row = 0; row < this->height; row++) {
        for (uint32_t col = 0; col < this->width; col++) {
            uint32_t starting_row = row * 8, starting_col = col * 8;
            for (uint32_t i = 0; i < 8; i++) {
                uint32_t row_starting_pixel = 
                    (starting_row + i) * artscii_img->width + starting_col;
                for (uint32_t j = 0; j < 8; j++) {
                    
                }
            }

        }
    }

    return artscii_img;
}
