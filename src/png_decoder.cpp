#include "png_decoder.h"
#include "img_manager.h"

#include <cstdio>
#include <png.h>
#include <string>
#include <stdio.h>
#include <stdexcept>


Png::Png(std::string file_name) {
    // open file

    this->fp = fopen(file_name.c_str(), "rb");

    if (!this->fp) {
        throw std::runtime_error("Cannot read file");
    }

    // check if file is actually png

    uint8_t header[8];
    size_t read_size = fread(header, 1, 8, fp);
    if (read_size != 8) {
        fclose(this->fp);
        throw std::runtime_error("File is too small");
    }

    uint8_t is_not_png = png_sig_cmp(header, 0, 8);
    if (is_not_png) {
        fclose(this->fp);
        throw std::runtime_error("File is not png");
    }

    // initialize png_struct and png_info

    this->img_ptr   = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!this->img_ptr) {
        fclose(this->fp);
        throw std::runtime_error("Cannot create PNG struct");
    }
    this->info_ptr = png_create_info_struct(this->img_ptr);
    if (!this->info_ptr) {
        png_destroy_read_struct(&this->img_ptr, &this->info_ptr, nullptr);
        fclose(this->fp);
        throw std::runtime_error("Cannot create PNG info");
    }

    // error handling hook, destroy the read structs, close fp, throw error

    if (setjmp(png_jmpbuf(this->img_ptr))) {
        png_destroy_read_struct(&this->img_ptr, &this->info_ptr, nullptr);
        fclose(this->fp);
        throw std::runtime_error("Fatal libpng error");
    }

    // initiate I/O
    png_init_io(this->img_ptr, this->fp);
    png_set_sig_bytes(this->img_ptr, 8); // the 8 png header bytes
    png_read_info(this->img_ptr, this->info_ptr);

    // load metadata to ram
    uint32_t width, height;
    int bit_depth, color_type;
    png_get_IHDR(this->img_ptr, this->info_ptr, 
            &width, &height, (int* ) &bit_depth, (int *) &color_type, 
            nullptr, nullptr, nullptr);

    // change format if necessary


    this->bit_depth = static_cast<uint8_t>(bit_depth);
    this->color_type = static_cast<uint8_t>(color_type);
    this->img_manager = new Img_Manager(height, width);
    
}
