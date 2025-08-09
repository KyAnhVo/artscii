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

    img->read_image();
    img->downscale(scale_down, scale_down);
    std::cout << img->img_manager->height << 'x' << img->img_manager->width << std::endl << std::endl;
    img->downscale(2, 2);
    char* text = img->to_ascii(gamma);


    uint64_t ind = 0;
    for (int i = 0; i < img->img_manager->height; i++) {
        for (int j = 0; j < img->img_manager->width; j++) {
            std::cout << text[ind];
            ind++;
        }
        std::cout << std::endl;
    }
}
