#include <iostream>
#include <stdexcept>
#include <string>

#include "png_decoder.h"

int main(int argc, char ** argv) {
    if (argc != 2 && argc != 3 && argc != 4) {
        std::cerr << "require './artscii <file_name>'" << std::endl;
        return 1;
    }
    
    uint8_t scale_down;
    float   gamma;

    if (argc == 2) 
        scale_down = 1;

    else {
        std::cout << "downscale = " << argv[2] << std::endl;
        scale_down = std::stoi(argv[2]);
    }
    
    if (argc < 4)
        gamma = 1.0f;
    else
        gamma = std::stof(argv[3]);
    
    Png * img;
    try {
        img = new Png(argv[1]);
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    Img_Manager * img_manager = img->read_image();
    img_manager->downsize(scale_down, scale_down);
    img_manager->downsize(2, 1);

    Luminance_View * lum = img_manager->luminance(255, 255, 255);
    lum->gamma_correction(gamma);
    char * text = lum->gen_artscii();

    uint64_t ind = 0;
    for (int i = 0; i < img_manager->height; i++) {
        for (int j = 0; j < img_manager->width; j++) {
            std::cout << text[ind];
            ind++;
        }
        std::cout << std::endl;
    }
}
