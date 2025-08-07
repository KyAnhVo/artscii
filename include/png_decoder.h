#ifndef PNG_DECODER_H
#define PNG_DECODER_H

#include "img_manager.h"
#include <cstdint>
#include <string>


/**
 * @brief mandatory first 8 bytes of a PNG file
 */
extern const uint8_t PNG_HEADER[8];

class Png {
public:
    Img_Manager * img_manager;

    Png(std::string);
    std::string gen_artscii();
};

#endif
