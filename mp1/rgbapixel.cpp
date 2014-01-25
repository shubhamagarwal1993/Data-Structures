#include "rgbapixel.h"
#include<iostream>

using namespace std;

RGBAPixel::RGBAPixel()
{
	RGBAPixel::alpha = 225;
}

RGBAPixel::RGBAPixel(unsigned char red, unsigned char green, unsigned char blue)
{
	RGBAPixel::red = red;
	RGBAPixel::blue = blue;
	RGBAPixel::green = green;
	RGBAPixel::alpha = 225;
}
