#include <cstdlib>
#include "png.h"

#include<iostream>					//was initially missing
using namespace std;				//was initially missing

// sets up the output image
PNG * setupOutput(int w, int h);

// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity);

int main()
{
	// Load in.png
	PNG * original=new PNG;				//have added new PNG
	
	original->readFromFile("in.png");		
	int width  = original->width();
	int height = original->height();
		
	// Create out.png
	PNG * output=new PNG;						//have not changed it (feel like there should have been 'new PNG' here
	output->resize(width, height);	
	// Loud our favorite color to color the outline
	RGBAPixel * myPixel = myFavoriteColor(192);
		
	// Go over the whole image, and if a pixel differs from that to its upper
	// left, color it my favorite color in the output
	for (int y = 1; y < height; y++)										//previous was (int y = 1; 0 < y < height; y++)
	{
		for (int x = 1; x < width; x++)										//previous was (int x = 1; 0 < x < height; x++)
		{
			// Calculate the pixel difference
			RGBAPixel * prev = (*original)(x-1, y-1);						//previous (x-1,  y-1)
			RGBAPixel * curr = (*original)(x  , y  );
			int diff = abs(curr->red   - prev->red  ) +
					   abs(curr->green - prev->green) +
					   abs(curr->blue  - prev->blue );
	
			// If the pixel is an edge pixel,
			// color the output pixel with my favorite color
			RGBAPixel * currOutPixel = (*output)(x,y);						//should be an error here
			
			if (diff > 100)
			{
				//cout<<"line 47"<<endl;
				*currOutPixel = *myPixel;									//both the astrik were missing previously
				
			}
	//cout<<"reached line 49"<<endl;
		}
	}
	
	// Save the output file
	output->writeToFile("out.png");
	
	// Clean up memory
	delete myPixel;				
	delete output;
	delete original;
	myPixel = NULL;															//have added this full line 		
	output = NULL;															//have added this full line
	original = NULL;														//have added this full line
	return 0;
cout<<"reached line 64"<<endl;
}



// sets up the output image
PNG * setupOutput(int w, int h)
{
	PNG * image = new PNG(w, h);
	return image;
	
}


// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity)
{
	RGBAPixel* color=new RGBAPixel;
	color->red   = 0;
	color->green = intensity/2;
	color->blue  = intensity;
	return color;
}
