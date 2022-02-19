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
        std::string src, dst;
        size_t nbImages;
        const char* srcc;
        const char* dstc;

        
        	    	  	  
    public:        	    	  	  
        	    	  	  
        //Image(const char* dstc,const char* srcc);
        Image(const char* s = "") :srcc(s) {};

        /*~Image()
        {
            for (uint32_t i = 0; i < nbImages; i++)
            {
                freeImage(images[i]);
            }
            std::cout << "image manager deconstructor called" << std::endl;
            delete[] images;
        };
        
        ImageInfo getBackground() const;
        void freeImage(ImageInfo& image) const;

        size_t getNBImages() const;
        void setNBImages(size_t nbImages);

        ImageInfo& getImages() const;
        void setImages(ImageInfo* listPath);*/

        ImageInfo readImg();
        int cop(ImageInfo image,const char* copy);
        int writeImg(const char* dstc);

        const char* getSRC() const;
        void setSRC(const char* srcc);

        ImageInfo& getImages() const;
        //void setImages(ImageInfo* images);

};        	    	  	   
#endif     	    	  	  
