#pragma warning(disable:4996)

#include "Image.h"
#include <iostream>
#include <sstream>
#include <stdio.h> 
#include <iomanip>
#include <setjmp.h>

Image::Image(std::string src, const char* dstc, const char* srcc) {
    //std::cout << src << " ";
    //std::cout << dst << " ";

    this->dstc = dstc;
    this->srcc = srcc;

    readImg(srcc);
    writeImg(dstc);
}


std::string Image::getSrc() const {
    return this->src;
}

std::string Image::getDst() const {
    return this->dst;
}

int convertColor(int color) {

    std::stringstream ss;
    unsigned int valhex;
    ss << std::hex << (int)color;
    ss >> valhex;
    return valhex;
}

unsigned char* raw_image = NULL;

int widthImg;
int heightImg;

int Image::readImg(const char* srcc) {

    //std::cout << src <<"There is nothing !\n";

    //cinfo.err = jpeg_std_error(jerr);

    //FILE* fp;
    //errno_t err;


    /*if ((err = fopen_s(&fp, "C:/Users/kidom/OneDrive/Bureau/3djv/c++/Images/bantha.png", "rb")) != 0) {
        printf("Error: failed to open %s\n", "C:/Users/kidom/OneDrive/Bureau/3djv/c++/Images/bantha.png");
        return false;
    }
    else {
        printf("no error\n");
    }*/

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    JSAMPROW row_pointer[1];

    FILE* fp; 
    unsigned long location = 0;
    int i = 0;

    if ((fp = fopen(srcc, "rb"))== NULL) {
        printf("Error: failed to open %s\n", srcc);
        return false;
    }
    else {
        printf("no error");
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, fp);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    printf("\ncomponents = %d\n", cinfo.num_components);

    raw_image = (unsigned char*)malloc(cinfo.output_width * cinfo.output_height * cinfo.num_components);
    row_pointer[0] = (unsigned char*)malloc(cinfo.output_width * cinfo.num_components);

    while (cinfo.output_scanline < cinfo.image_height)
    {
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
        for (i = 0; i < cinfo.image_width * cinfo.num_components; i++)
            raw_image[location++] = row_pointer[0][i];
    }
    widthImg = cinfo.image_width;
    heightImg = cinfo.image_height;

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    free(row_pointer[0]);

    fclose(fp);

    /*if (std::rename(srcc, "C:/Users/kidom/OneDrive/Bureau/3djv/c++/Images/grogu.jpg") != 0)
        perror("Error renaming file");
    else
        std::cout << "File renamed successfully";*/
    cop(this->dstc);
    return 0;
}

int Image::cop(const char* copy)
{
    int width = widthImg;
    int height = heightImg;
    int bytes_per_pixel = 3;   /* or 1 for GRACYSCALE images */
    int color_space = JCS_RGB;

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    JSAMPROW row_pointer[1];
    FILE* outfile;
    if ((outfile = fopen(copy, "wb")) == NULL) {
        printf("Error: failed to open %s\n", copy);
        return -1;
    }
    else {
        printf("no error");
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    int widthd = cinfo.image_width;

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = bytes_per_pixel;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);

    jpeg_start_compress(&cinfo, TRUE);


    for (int i = 0; i < cinfo.image_height; i++) {
        for (int j = 0; j < cinfo.image_width; j++) {
            // Pixel (i,j)
            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0] = 255;
            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 1] = 255;
            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 2] = 255;

            int red = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0]);
            int green = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 1]);
            int blue = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 2]);
        }
    }

    while (cinfo.next_scanline < cinfo.image_height)
    {

        row_pointer[0] = &raw_image[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);

    return 1;
}

int Image::writeImg(const char* dstc)
{

    int width = widthImg;
    int height = heightImg;
    int bytes_per_pixel = 3;   /* or 1 for GRACYSCALE images */
    int color_space = JCS_RGB;

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    JSAMPROW row_pointer[1];
    FILE* outfile;
    if ((outfile = fopen(dstc, "wb")) == NULL) {
        printf("Error: failed to open %s\n", dstc);
        return -1;
    }
    else {
        printf("no error");
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    int widthd = cinfo.image_width;

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = bytes_per_pixel;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);

    jpeg_start_compress(&cinfo, TRUE);

    /*int a_red = 255;
    int b_red = 0;

    int a_green = 255;
    int b_green = 0;

    int a_blue = 255;
    int b_blue = 0;

    for (int i = 0; i < cinfo.image_height; i++) {
        for (int j = 0; j < cinfo.image_width; j++) {
            int red = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0]);
            int v_red = red;

            if (v_red < a_red) {
                a_red = v_red;
            }
            if (v_red > b_red) {
                b_red = v_red;
            }

            int green = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0]);
            int v_green = green;

            if (v_green < a_green) {
                a_green = v_green;
            }
            if (v_green > b_green) {
                b_green = v_green;
            }

            int blue = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0]);
            int v_blue = blue;

            if (v_blue < a_blue) {
                a_blue = v_blue;
            }
            if (v_blue > b_blue) {
                b_blue = v_blue;
            }
        }
    }

    int A_red = a_red - 100;
    int B_red = b_red + 100;

    int A_green = a_green - 100;
    int B_green = b_green + 100;

    int A_blue = a_blue - 100;
    int B_blue = b_blue + 100;

    for (int i = 0; i < cinfo.image_height; i++) {
        for (int j = 0; j < cinfo.image_width; j++) {
            int red = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0]);
            int v_red = red;
            
            int green = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0]);
            int v_green = green;

            int blue = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0]);
            int v_blue = blue;

            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0] = A_red + (B_red - A_red) * (v_red - a_red) / (b_red - a_red);
            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 1] = A_green + (B_green - A_green) * (v_green - a_green) / (b_green - a_green);
            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 2] = A_blue + (B_blue - A_blue) * (v_blue - a_blue) / (b_blue - a_blue);
            
        }
    }*/


    for (int i = 0; i < cinfo.image_height; i++) {
        for (int j = 0; j < cinfo.image_width; j++) {
            // Pixel (i,j)
            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0] = raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0]-50; // Red Pixel
            
            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 1] = raw_image[(i * cinfo.image_width * 3) + (j * 3) + 1]-50; // Green Pixel
            
            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 2] = raw_image[(i * cinfo.image_width * 3) + (j * 3) + 2]+10; // Blue Pixel
            
            int red = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0]);
            int green = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 1]);
            int blue = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 2]);

            //std::cout << "red :" << red << " green: " << green << " blue : " << blue << " " << std::endl;
        }
    }

    while (cinfo.next_scanline < cinfo.image_height)
    {

        row_pointer[0] = &raw_image[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);

    return 1;
}