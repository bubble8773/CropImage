#include <stdint.h>
#include <cstdio>

enum ImageType {
	PNG, JPG, BMP, TGA
};

struct Image {
	uint8_t* data = NULL;
	size_t size = 0;
	int w;
	int h;
	int channels;

	Image(const char* filename);
	Image(int w, int h, int channels);
	Image(const Image& img);
	~Image();

	bool read(const char* filename);
	bool write(const char* filename);

	ImageType get_file_type(const char* filename);
	Image& crop(uint16_t cx, uint16_t cy, uint16_t cw, uint16_t ch);
	void GetBoundingBox();
	
};



