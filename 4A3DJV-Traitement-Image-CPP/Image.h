#ifndef _IMAGE_H_        	    	  	  
#define _IMAGE_H_        	    	  	  
#include <iostream>
#include <stdio.h>   	  	  
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <jpeglib.h>
#include <filesystem>

typedef struct {
    uint8_t* data;   // raw data
    uint32_t width;
    uint32_t height;
    uint32_t ch;     // color channels
    std::filesystem::path path;
} ImageInfo;

class Image {
private:
    ImageInfo* images;
    std::string src, dst;
    int nbImages;
    const char* srcc;
    const char* dstc;
    std::filesystem::path fsp;



public:

    Image(std::filesystem::path p = "") :fsp(p) {};

    ImageInfo readImg();
    int cop(ImageInfo image);
    int getBackground();

    std::filesystem::path getSRC() const;
    void setSRC(std::filesystem::path);

    ImageInfo& getImages() const;
    void setImages(ImageInfo* images);

    int getNBImages() const;
    void setNBImages(int nbImages);

};
#endif     	    	  