#include <iostream>

#include "img_manager.h"

int main(int argc, char ** argv) {
    Img_Manager * img = new Img_Manager(4, 4);

    uint8_t test_data[64] = {
        // Row 0: Dark block (2 pixels) | Light block (2 pixels)
        10,  10,  10, 255,    20,  20,  20, 255,    240, 240, 240, 255,    250, 250, 250, 255,
        // Row 1: Dark block (2 pixels) | Light block (2 pixels)
        15,  15,  15, 255,    25,  25,  25, 255,    245, 245, 245, 255,    255, 255, 255, 255,
        // Row 2: Mixed 1 (2 pixels) | Mixed 2 (2 pixels)
        200, 50,  50, 255,    100, 150, 200, 255,    30,  200, 30, 255,     180, 100, 50, 255,
        // Row 3: Mixed 1 (2 pixels) | Mixed 2 (2 pixels)
        60,  180, 60, 255,    220, 100, 180, 255,    150, 50,  200, 255,    40,  160, 220, 255
    };
    
    for (int i = 0; i < 64; i++) {
        img->rgba[i] = test_data[i];
    }

    // test shrink image
    Img_Manager * shrinked = img->downsize(2, 2);

    // test lum

    Luminance_View * lum = shrinked->luminance(255, 255, 255);

    // test artscii
    char * artscii = lum->gen_artscii();
    for (int i =  0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << artscii[i * 2 + j];
        }
        std::cout << std::endl;
    }
    
    delete img;
    delete shrinked;
    delete lum;
    delete[] artscii;
}
