#ifndef _IMAGE_H_                            
#define _IMAGE_H_  

#include <turbojpeg.h>
#include <stdint.h>
#include <filesystem>

class Image
{
private:
	uint8_t* data;
	uint32_t width;
	uint32_t height;
	uint32_t output_components;

public:

	Image(uint32_t width, uint32_t height, uint32_t output_components=3) {
		this->width = width;
		this->height = height;
		this->output_components = output_components;
		
		this->data = new uint8_t[width * height * output_components];
	}

	Image(std::filesystem::path p) {

		this->width;
		this->height;
		this->output_components;
		this->data;
	}

	~Image()
	{
		delete[] this->data;
	};

};

#endif
