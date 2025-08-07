#include "img_manager.h"

#include <cstdint>

// ==== CLASS: LUMINANCE_VIEW ====

Luminance_View::Luminance_View(uint16_t height, uint16_t width) {
    this->height    = (uint32_t) height;
    this->width     = (uint32_t) width;
    uint32_t area   = this->height * this->width;
    this->luminance = new float[area];
}

// ==== CLASS: IMG_MANAGER ====

Img_Manager::Img_Manager(uint16_t height, uint16_t width) {
    this->height    = (uint32_t) height;
    this->width     = (uint32_t) width;
    uint32_t area   = this->width * this->height;
    this->r         = new uint8_t[area];
    this->g         = new uint8_t[area];
    this->b         = new uint8_t[area];
}

Img_Manager * Img_Manager::downsize(uint8_t height_downsize_ratio, uint8_t width_downsize_ratio) {
    // each pixel of the downsized image is map to its
    // height_downsize_ratio x width_downsize_ratio 
    // corresponding square.
    
    Img_Manager * downsized_image = new Img_Manager(
            this->height / height_downsize_ratio, this->width / width_downsize_ratio);
    uint32_t block_area = height_downsize_ratio * width_downsize_ratio;
    
    for (int i = 0; i < downsized_image->height; i++) {
        for (int j = 0; j < downsized_image->width; j++) {
            // for each downsized_image's pixel, we take the average of the
            // height_downsize_ratio x width_downsize_ratio pixel rgb values
            uint32_t starting_row       = i * height_downsize_ratio,
                     starting_column    = j * width_downsize_ratio;
            uint32_t r = 0, g = 0, b = 0;
            for (int curr_i = starting_row; curr_i < starting_row + height_downsize_ratio; curr_i++) {
                for (int curr_j = starting_column; curr_j < starting_column + width_downsize_ratio; curr_j++) {
                    uint32_t ind = curr_i * this->width + curr_j;
                    r += this->r[ind];
                    g += this->g[ind];
                    b += this->b[ind];
                }
            }
            uint32_t ind = i * downsized_image->width + j;
            downsized_image->r[ind] = (uint8_t) (r / block_area);
            downsized_image->g[ind] = (uint8_t) (g / block_area);
            downsized_image->b[ind] = (uint8_t) (b / block_area);
        }
    }

    return downsized_image;
}

Luminance_View * Img_Manager::luminance() {
    Luminance_View * luminance = new Luminance_View(this->height, this->width);
    
    float avr_luminance = 0;
    for (int i = 0; i < this->height * this->width; i++) {
        luminance->luminance[i] = (0.2126 * r[i] + 0.7152 * g[i] + 0.0722 * b[i]) / 255;
        avr_luminance += luminance->luminance[i];
    }

    return luminance;
}
