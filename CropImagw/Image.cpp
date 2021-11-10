//https://www.youtube.com/c/CodeBreakChannel/about

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define BYTE_BOUND(value) value < 0 ? 0 : (value > 255 ? 255 : value)

#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

Image::Image(const char* filename) {
	if(read(filename)) {
		printf("Read %s\n", filename);
		size = w*h*channels;		
	}
	else {
		printf("Failed to read %s\n", filename);
	}
}

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
	size = w*h*channels;
	data = new uint8_t[size];
}

Image::Image(const Image& img) : Image(img.w, img.h, img.channels) {
	memcpy(data, img.data, size);
}

Image::~Image() {
	stbi_image_free(data);
}

bool Image::read(const char* filename) {
	data = stbi_load(filename, &w, &h, &channels, 0);
	return data != NULL;
}

bool Image::write(const char* filename) {
	ImageType type = get_file_type(filename);
	int success;
  switch (type) {
    case PNG:
      success = stbi_write_png(filename, w, h, channels, data, w*channels);
      break;
    case BMP:
      success = stbi_write_bmp(filename, w, h, channels, data);
      break;
    case JPG:
      success = stbi_write_jpg(filename, w, h, channels, data, 100);
      break;
    case TGA:
      success = stbi_write_tga(filename, w, h, channels, data);
      break;
  }
  return success != 0;
}

ImageType Image::get_file_type(const char* filename) {
	const char* ext = strrchr(filename, '.');
	if(ext != nullptr) {
		if(strcmp(ext, ".png") == 0) {
			return PNG;
		}
		else if(strcmp(ext, ".jpg") == 0) {
			return JPG;
		}
		else if(strcmp(ext, ".bmp") == 0) {
			return BMP;
		}
		else if(strcmp(ext, ".tga") == 0) {
			return TGA;
		}
	}
	return PNG;
}


Image& Image::crop(uint16_t cx, uint16_t cy, uint16_t cw, uint16_t ch) {
	size = cw * ch * channels;
	uint8_t* croppedImage = new uint8_t[size];
	memset(croppedImage, 0, size);

	for(uint16_t y = 0;y < ch;++y) {
		if(y + cy >= h) {break;}
		for(uint16_t x = 0;x < cw;++x) {
			if(x + cx >= w) {break;}
			memcpy(&croppedImage[(x + y * cw) * channels], &data[(x + cx + (y + cy) * w) * channels], channels);
		}
	}

	w = cw;
	h = ch;
	
	delete[] data;
	data = croppedImage;
	croppedImage = nullptr;

	return *this;
}

//Nandita
void Image::GetBoundingBox()
{
	vector<int> xVals;
	vector<int> yVals;
	//Find a center pixel
        //find the height
	//find the width
	for (uint16_t y = 0; y < h; ++y) {
		
		for (uint16_t x = 0; x < w; ++x) {
			
			//pixels with different colors 
			if (unsigned(data[(x + y * w) * channels] != (unsigned)255)) {
				xVals.push_back(x);
				yVals.push_back(y);
				break;
			}		
			
		}		
	}

	for (uint16_t y = h-1; y >= 1; --y) {

		for (uint16_t x = w-1; x >=1; --x) {
			
			if (unsigned(data[(x + y * w) * channels] != (unsigned)255)) {

				xVals.push_back(x);
				yVals.push_back(y);
				break;
			}
		}
	}
	
	auto maxX = *max_element(xVals.begin(), xVals.end());
	auto minX = *min_element(xVals.begin(), xVals.end());
	auto maxY = *max_element(yVals.begin(), yVals.end());
	auto minY = *min_element(yVals.begin(), yVals.end());

	//cout << maxX<<endl;
	//cout << minX<<endl;
	//cout << maxY << endl;
	//cout << minY<<endl;
	//Center or offset is (minX, minY)
	//height = maxY-minY
	//width = maxX-minX
	
	crop(minX, minY, maxX-minX, maxY-minY);
}





