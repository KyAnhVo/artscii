#include <iostream>
#include <stdexcept>

#include "png_decoder.h"

int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "require './artscii <file_name'" << std::endl;
        return 1;
    }
    
    Png * img;
    try {
        img = new Png(argv[1]);
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    img->read_image();
    std::cout << img->img_manager->height << 'x' << img->img_manager->width << std::endl << std::endl;
    char* text = img->to_ascii();
    uint64_t ind = 0;
    for (int i = 0; i < img->img_manager->height; i++) {
        for (int j = 0; j < img->img_manager->width; j++) {
            std::cout << text[ind];
            ind++;
        }
        std::cout << "END_ROW" << std::endl;
    }
}
