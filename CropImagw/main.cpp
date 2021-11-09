#include "Image.h"


int main(int argc, char** argv) {
	Image test("Images/fozzie-in.bmp");
	test.write("Images/test.bmp");
	
	//Image copyImg("Images/test.bmp"); 
	//copyImg.crop(20,20,80, 80); // required bounding box
	//copyImg.write("Images/croptest.bmp");

	Image copyImg("Images/test.bmp");
	//copyImg.crop(20, 20, 80, 80);
	copyImg.GetBoundingBox();
	copyImg.write("Images/croptest.bmp");
	/*
	
		Add your own code here to do some cool stuff with images!
		https://www.youtube.com/playlist?list=PLG5M8QIx5lkzdGkdYQeeCK__As6sI2tOY
		
	*/




	return 0;
}
