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
    
    // for the 4 for loops, consider that a picture's array of (h, w) image
    // looks like a (h, 4w) 2d array, with is then expressed as a 4wh 1d array.
    // where rows in the 2d are added together.
    
    for (uint32_t downsized_row = 0; downsized_row < downsized_image->height; downsized_row++) {
        for (uint32_t downsized_column = 0; downsized_column < downsized_image->width; downsized_column++) {
            
            // for each downsized pixel, we get the average weighted rgb value (weighted by a).
            // a is max(a), to preserve bordering.

            uint32_t starting_row = downsized_row * height_downsize_ratio,
                     starting_column = downsized_column * width_downsize_ratio;
            uint64_t r_tot = 0, g_tot = 0, b_tot = 0, a_tot = 0;
            uint8_t max_a = 0;

            for (uint32_t row = starting_row; row < starting_row + height_downsize_ratio; row++) {
                for (uint32_t col = starting_column; col < starting_column + width_downsize_ratio; col++) {
                    uint64_t ind = (this->width * row + col) * 4;

                    uint8_t curr_r = this->rgba[ind + 0],
                            curr_g = this->rgba[ind + 1],
                            curr_b = this->rgba[ind + 2],
                            curr_a = this->rgba[ind + 3];

                    max_a = max_a < curr_a ? curr_a : max_a;

                    r_tot += curr_r * curr_a;
                    g_tot += curr_g * curr_a;
                    b_tot += curr_b * curr_a;
                    a_tot += curr_a;
                }
            }

            uint64_t downsized_ind = (downsized_row * downsized_image->width + downsized_column) * 4;

            if (max_a > 0) {
                downsized_image->rgba[downsized_ind + 0] = static_cast<uint8_t>(r_tot / a_tot);
                downsized_image->rgba[downsized_ind + 1] = static_cast<uint8_t>(g_tot / a_tot);
                downsized_image->rgba[downsized_ind + 2] = static_cast<uint8_t>(b_tot / a_tot);
            }
            else {
                downsized_image->rgba[downsized_ind + 0] = 0;
                downsized_image->rgba[downsized_ind + 1] = 0;
                downsized_image->rgba[downsized_ind + 2] = 0;
            }

            downsized_image->rgba[downsized_ind + 3] = max_a;
        }
    }

    return downsized_image;
}

Luminance_View * Img_Manager::luminance(uint8_t r, uint8_t g, uint8_t b) {
    Luminance_View * luminance = new Luminance_View(this->height, this->width);

    for (uint32_t i = 0; i < this->height * this->width * 4; i += 4) {
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

char * Luminance_View::gen_artscii() {
    char * artscii = new char[this->width * this->height];
    for (uint64_t i = 0; i < this->width * this->height; i++) {
        uint8_t brightness_level = static_cast<uint8_t>(this->luminance[i] * 15.999f);
        artscii[i] = Luminance_View::artscii_chars[brightness_level];
    }
    return artscii;
}
