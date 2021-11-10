#include "Image.h"

int main(int argc, char** argv) {
	Image test("Images/fozzie-in.bmp");
	test.write("Images/test.bmp");
	
	//Image copyImg("Images/test.bmp"); 
	//copyImg.crop(20,20,80, 80); // required bounding box
	//copyImg.write("Images/croptest.bmp");

	Image copyImg("Images/test.bmp");
	//Image copyImg = test;
	
	copyImg.GetBoundingBox();
	copyImg.write("Images/croptest.bmp");
	return 0;
}
