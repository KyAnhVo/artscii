#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

#include <stdlib.h>

#include "png_decoder.h"

void print_help_message();

int main(int argc, char ** argv) {
    if (argc != 2 && argc != 4 && argc != 6) {
        std::cerr << "Invalid input. Use -h or --help to see usage." << std::endl;
        return 1;
    }
    
    if (argc == 2 &&  (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_help_message();
        return 0;
    }

    float gamma = 1;
    float zoom = 1;
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--brightness") == 0) {
            i += 1;
            gamma = std::stof(argv[i]);
        }
        else if (strcmp(argv[i], "-z") == 0 || strcmp(argv[i], "--zoom") == 0) {
            i += 1;
            zoom = std::stof(argv[i]);
        }
        else {
            std::cerr << "Invalid input. Use -h or --help to see usage." << std::endl;
            return 1;
        }
    }

    // manage files output char properly
    char * fname = argv[1];
    std::string fname_std;
    if (strlen(fname) < 4) {
        std::cerr   << "only accepts image files (eg. endings .jpeg, .jpg, .png, .webp)" 
                    << std::endl;
        return 1;
    }
    char * fname_end = fname + strlen(fname);   // fname_end is at nullptr
    if (strcmp(fname_end - 4, ".png") != 0) {   // if fname doesn't end with .png, we transfer it to png
        std::string ffmpeg_cmd = "ffmpeg -loglevel error -y -i \"";
        ffmpeg_cmd += fname;
        ffmpeg_cmd += "\" /tmp/artscii_converted_output.png";
        int ffmpeg_status = system(ffmpeg_cmd.c_str());
        if (ffmpeg_status != 0) {
            std::cerr << "Conversion to png failed" << std::endl;
            return 1;
        }
        fname_std = "/tmp/artscii_converted_output.png";
    }
    else {
        fname_std = fname;
    }

    Png_Input * img;
    try {
        img = new Png_Input(fname_std.c_str());
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    Img_Manager * img_manager = img->read_image();
    img_manager->downsize(zoom, zoom);
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

    delete img;
    delete img_manager;
    delete lum;
}

void print_help_message() {
    std::cout << "Artscii v.1.0" << std::endl 
        << "prints artscii-ized picture to terminal" << std::endl << std::endl
        << "get help" << std::endl
        << "--help, -h" << std::endl << std::endl
        << "image options" << std::endl
        << "--zoom, -z" << std::endl
        << '\t' << "Zoom out the image by a factor of n (n >= 1). n = 1 doesn't do anything." << std::endl
        << "--brightness, -b" << std::endl
        << '\t' << "Change the brightness, ranging from 0.2 to 3 (design decision)." << std::endl
        << '\t' << "1 is default, less than 1 gets dark, more than 1 gets bright. Log scaled." << std::endl;
}
