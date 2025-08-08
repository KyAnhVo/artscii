#include "img_manager.h"

#include <cstdint>

// ==== CLASS: LUMINANCE_VIEW ====

Luminance_View::Luminance_View(uint32_t height, uint32_t width) {
    this->height    = height;
    this->width     = width;
    uint64_t area   = static_cast<uint64_t>(height) * static_cast<uint64_t>(width); 
    this->luminance = new float[area];
}

// ==== CLASS: IMG_MANAGER ====

Img_Manager::Img_Manager(uint32_t height, uint32_t width) {
    this->height    = height;
    this->width     = width;
    uint64_t area   = static_cast<uint64_t>(height) * static_cast<uint64_t>(width);
    this->rgba      = new uint8_t[area * 4]; // because r, g, b, a is 4 vals.
}

Img_Manager * Img_Manager::downsize(uint8_t height_downsize_ratio, uint8_t width_downsize_ratio) {
    // each pixel of the downsized image is map to its
    // height_downsize_ratio x width_downsize_ratio 
    // corresponding square.
    
    Img_Manager * downsized_image = new Img_Manager(
            this->height / height_downsize_ratio, this->width / width_downsize_ratio);
    uint64_t block_area = height_downsize_ratio * width_downsize_ratio;
    
    for (uint32_t downsized_row = 0; downsized_row < downsized_image->height; downsized_row++) {
        for (uint32_t downsized_column = 0; downsized_column < downsized_image->width; downsized_column++) {

        }
    }

    return downsized_image;
}

Luminance_View * Img_Manager::luminance(uint8_t r, uint8_t g, uint8_t b) {
    Luminance_View * luminance = new Luminance_View(this->height, this->width);

    for (uint32_t i = 0; i < this->height * this->width; i += 4) {
        float alpha = this->rgba[i + 3] / 255.0;
        float not_alpha = 1 - alpha;

        float pixel_luminance = 
            (0.2126f * rgba[i] + 0.7152f * rgba[i + 1] + 0.0722f * rgba[i + 2]) / 255;
        float background_luminance =
            (0.2126f * r + 0.7152f * g + 0.0722f * b) / 255;

        luminance->luminance[i / 4] = alpha * pixel_luminance + not_alpha * background_luminance;
    }

    return luminance;
}
