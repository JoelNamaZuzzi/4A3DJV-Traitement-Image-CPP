#include "Image.h"

uint8_t* Image::getData() {
	return this->data;
}

void Image::setData(uint8_t* data) {
	delete[] this->data;
	this->data = data;
}

uint32_t Image::getWidth() {
	return this->width;
}

void Image::setWidth(uint32_t width) {
	this->width = width;
}

uint32_t Image::getHeight() {
	return this->height;
}

void Image::setHeight(uint32_t height) {
	this->height = height;
}

uint32_t Image::getOutputComponents() {
	return this->outputComponents;
}

void Image::setOutputComponents(uint32_t outputComponents) {
	this->outputComponents = outputComponents;
}

void Image::save(const std::string& p) {
	FILE* fp;

	struct jpeg_error_mgr jerr;
	struct jpeg_compress_struct cinfo;

	const char* dest = p.c_str();

	jpeg_create_compress(&cinfo);

	cinfo.err = jpeg_std_error(&jerr);

	fp = fopen(dest, "wb");

	if (fp == NULL) {
		printf("Error: failed to open %s\n", dest);
		exit(1);
	}

	jpeg_stdio_dest(&cinfo, fp);

	cinfo.image_width = this->width;
	cinfo.image_height = this->height;
	cinfo.input_components = this->outputComponents;
	cinfo.in_color_space = JCS_RGB;
	jpeg_set_defaults(&cinfo);

	jpeg_start_compress(&cinfo, true);

	uint8_t* row = this->data;
	const uint32_t stride = this->width * this->outputComponents;

	for (uint32_t y = 0; y < this->height; y++) {
		jpeg_write_scanlines(&cinfo, &row, 1);
		row += stride;
	}

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	fclose(fp);

}