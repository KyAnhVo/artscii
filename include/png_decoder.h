#ifndef PNG_DECODER_H
#define PNG_DECODER_H

#include "img_manager.h"
#include <string>
#include <png.h>

class Png {
public:
    Img_Manager *   img_manager;
    FILE * fp;
    png_structp     img_ptr;
    png_infop       info_ptr;

    uint8_t bit_depth, color_type;
    
    /**
     * @brief create a Png wrapper for a file given its path
     *
     * @param file_name the path to the file
     */
    Png(std::string);

    /**
     * @brief read image to this->img_manager
     */
    void read_image();

    /**
     * Downscale the image in img_manager
     */
    void downscale(uint8_t, uint8_t);

    /**
     *
     */
    char* to_ascii(float);
};

#endif
