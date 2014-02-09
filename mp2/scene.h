#ifndef SCENE_H
#define SCENE_H
#include "image.h"
#include "png.h"
#include "rgbapixel.h"
#include<ostream>


class Scene{
public:
 	
 	
 	Scene(int max);
 
	/**
      *	Scene destructor	
	  */
	~Scene();
 
 	Scene (const Scene &source);
 	
 	const Scene & operator= (const Scene &source);
 	
 	void changemaxlayers (int newmax);
 	
 	void addpicture (const char *FileName, int index, int x, int y);
 	
 	
 	void changelayer (int index, int newindex);
 	
 	void translate (int index, int xcoord, int ycoord);
 
	void 	deletepicture (int index);

	Image * getpicture (int index) const;
	
	Image drawscene () const;

	/**
	 * copy helper function
	 */
	void copy(const Scene & other);
	
	/**
 	  *	Destructor 	
	*/
	void clear();
	
	
	/**
	 *	holds 'max' number of images. 
	 */
	int max;								

	/**
	 *	holds pointers of images 
	 */
	Image** array;
	
	/*
	 *	new array to copy over the images
	 */
	 Image** size_change_array;
	 
	 int * size_change_x;
	 
	 int * size_change_y;
	 
	/**
	 *	holds x coordinates of images 
	 */
	int* x_array;

	/**
	 *	holds pointers of images 
	 */
	int* y_array;

};
#endif




































