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
     * @brief show the artscii file over Vulkan window
     */
    std::string gen_artscii();

    
};

#endif
