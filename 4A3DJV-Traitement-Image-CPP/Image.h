#ifndef _IMAGE_H_        	    	  	  
#define _IMAGE_H_        	    	  	  
#include <iostream>
#include <stdio.h>   	  	  
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <jpeglib.h>

class Image {
private:
    std::string src, dst;
    const char* srcc;

    typedef struct {
        uint8_t* data;   // raw data
        uint32_t width;
        uint32_t height;
        uint32_t ch;     // color channels
    } ImageInfo;

public:

    Image(std::string src, std::string dst, const char* srcc);

    int readImg(std::string src, const char* srcc);
    int writeImg(const char* srcc);

    std::string getSrc() const;
    std::string getDst() const;
};
#endif    

