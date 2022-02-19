#ifndef _IMAGE_H_        	    	  	  
#define _IMAGE_H_        	    	  	  
#include <iostream>
#include <stdio.h>   	  	  
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <jpeglib.h>

typedef struct {
    uint8_t* data;   // raw data
    uint32_t width;
    uint32_t height;
    uint32_t ch;     // color channels
} ImageInfo;

class Image{        	    	  	  
    private:        	
        ImageInfo* images;
        std::string src;
        std::string dst;
        size_t nbImages;
        const char* srcc;
        const char* dstc;

        
        	    	  	  
    public:        	    	  	  
        	    	  	  
        Image(const char* s = " ") :srcc(s) {};

        /*~Image()
        {
            for (uint32_t i = 0; i < nbImages; i++)
            {
                freeImage(images[i]);
            }
            std::cout << "image manager deconstructor called" << std::endl;
            delete[] images;
        };*/
        	    	  	  
        int readImg(const char* srcc);
        int cop(const char* copy);
        int writeImg(const char* dstc);
        	    	  	  
        std::string getSrc() const;        	    	  	  
        std::string getDst() const;
};        	    	  	   
#endif     	    	  	  
