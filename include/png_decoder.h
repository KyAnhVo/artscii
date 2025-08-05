#ifndef PNG_DECODER_H
#define PNG_DECODER_H

#include <cstdint>

class Image_PNG {
public:
    uint32_t height, width;
    uint8_t * r, * g, * b;
    float * greyscale;

    Image_PNG(uint16_t height, uint16_t width) {
        this->height = (uint32_t) height, this->width = (uint32_t) width;
        uint32_t area   = this->height * this->width;
        this->r         = new uint8_t[area];
        this->g         = new uint8_t[area];
        this->b         = new uint8_t[area];
        this->greyscale = new float[area];
    }

    /**
     * @brief Downscales the image, each 8x8 square mapped to a pixel
     */
    Image_PNG * downscale() {
        Image_PNG * downscaled_image = new Image_PNG(this->height / 8, this->width / 8);

        for (int i = 0; i < downscaled_image->height; i++) {
            for (int j = 0; j < downscaled_image->width; j++) {
                // for each pixel, take the 64 corresponding pixels in the original image
                // and take its r_avr, g_avr, b_avr, and set it as downscaled_image's
                // RGB values

                uint32_t r = 0, g = 0, b = 0;
                for (int curr_i = 8 * i; curr_i < 8 * (i + 1); curr_i++) {
                    for (int curr_j = 8 * j; curr_j < 8 * (j + 1); curr_j++) {
                        uint32_t index = this->width * curr_i + curr_j;
                        r += this->r[index];
                        g += this->g[index];
                        b += this->b[index];
                    }
                }

                r /= 64;
                g /= 64;
                b /= 64;
                
                uint32_t ind = i * downscaled_image->width + j;
                downscaled_image->r[ind]            = (uint8_t) r;
                downscaled_image->g[ind]            = (uint8_t) g;
                downscaled_image->b[ind]            = (uint8_t) b;
                downscaled_image->greyscale[ind]    = (0.2126 * r + 0.7152 * g + 0.0722 * b);
            }
        }

        return downscaled_image;
    }
};


#endif
