#ifndef _IMAGE_H_                            
#define _IMAGE_H_  

#define _CRT_SECURE_NO_WARNINGS

#include <jpeglib.h>
#include <vector>
#include <turbojpeg.h>
#include <string>
#include <stdint.h>
#include <filesystem>

class Image
{
private:
	uint8_t* data;
	uint32_t width;
	uint32_t height;
	uint32_t outputComponents;

public:

	Image(uint32_t width, uint32_t height, uint32_t outputComponents=3) {
		this->width = width;
		this->height = height;
		this->outputComponents = outputComponents;
		
		this->data = new uint8_t[width * height * outputComponents];
	}

	Image(const std::string& p) {
		FILE* fp;

		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;

		cinfo.err = jpeg_std_error(&jerr);
		jpeg_create_decompress(&cinfo);

		const char* src = p.c_str();

		if ((fp = fopen(src, "rb")) == NULL) {
			printf("Error: failed to open %s\n", src);
			exit(1);
		}
		else {
			printf("File Open");
		}

		jpeg_stdio_src(&cinfo, fp);
		jpeg_read_header(&cinfo, true);
		jpeg_start_decompress(&cinfo);

		this->width = cinfo.image_width;
		this->height = cinfo.image_height;
		this->outputComponents= cinfo.output_components;
		this->data = new uint8_t[this->width * this->height * this->outputComponents];

		uint8_t* row = this->data;
		const uint32_t stride =this->width * this->outputComponents;

		for (uint32_t y = 0; y < this->height; y++) {
			jpeg_read_scanlines(&cinfo, &row, 1);
			row += stride;
		}
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);

		fclose(fp);
	}

	~Image()
	{
		delete[] this->data;
	};

	uint8_t* getData();
	void setData(uint8_t* data);

	uint32_t getWidth();
	void setWidth(uint32_t width);

	uint32_t getHeight();
	void setHeight(uint32_t height);

	uint32_t getOutputComponents();
	void setOutputComponents(uint32_t outputComponents);

	void save(const std::string& p);

};

#endif
