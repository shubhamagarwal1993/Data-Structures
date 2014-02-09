#include "scene.h"
#include "image.h"
#include "rgbapixel.h"
#include<iostream>

using namespace std;	

Scene::Scene(int size)
{
	max = size;								//'max' is a member variable
	Image** array = new Image*[max];		//dymanic array
	int* x_array = new int[max];
	int* y_array  = new int[max];
	
	for (int i = 0; i < max; i++)			//make all NULL
	{
		array[i] = NULL;
	}
}

Scene::Scene(const Scene & source)	
{
	copy(source);
}

const Scene & Scene::operator=	(const Scene & source)	
{
	if (this != &source)					//check for self assignment
	{					
		clear();							//delete everything that Scene has allocated
		copy(source);						//make Scene an independent copy of the source
	 }

	return *this;							//return  a reference to the current instance
}

void Scene::changemaxlayers(int newmax)	
{
	int size = 0;							//size is # of images. 
	while (array[size] != NULL)
	{
		size++;
	}
	
	if (newmax < size)
	{
		cout << "invalid newmax" <<endl;	//more images than space in newmax 
		return;						
	}
		
	if (newmax >= size)
	{
		Image** size_change_array = new Image*[newmax];			//dymanic array
		
		for (int i = 0; i < newmax; i++)						//make all NULL
		{
			size_change_array[i] = NULL;
		}
	//******copying null pointers*****************	
		
		for (int j = 0; j < max; j++)
		{
			if (array[j] != NULL)
			{
				size_change_array[j] = array[j];
			}
		}	
	delete []array;
	array = NULL;	
	*array = *size_change_array;
	size_change_array = NULL;
	}
}
	
void Scene::addpicture(const char * FileName, int index, int x, int y)
{
	if ((index < 0) || (index > max-1))	
	{
		cout << "index out of bounds" << endl;		//print statement
	}
	
	else 
	{
		if (array[index] != NULL)
		{
			delete array[index];
			array[index] = NULL;
			array[index]->readFromFile(FileName);	
			x_array[index] = x;
			y_array[index] = y;	
		}
		else
		{
			array[index]->readFromFile(FileName);	
			x_array[index] = x;
			y_array[index] = y;	
		}
	}	
}

void Scene::changelayer	(int index, int newindex)
{
	if ((index < 0) || (index > max-1) || (newindex < 0)|| (newindex > max-1))
	{
		cout << "invalid index" << endl;			
		return;
	}
	
	else
	{	
		if (index == newindex)
		{
			return;
		}			
	
		if (array[newindex] != NULL)
		{
			delete array[newindex];
			array[newindex] = NULL;
			array[newindex] = array[index];
			array[index] = NULL;
		}
	}
}

void Scene::translate(int index, int xcoord, int ycoord)
{
	if ((index < 0) || (index > max-1) || (array[index] == NULL))
	{
		cout << "invalid index" << endl;
		return; 
	}
	//storing "max" as a member variable.
	else
	{
		x_array[index] = xcoord;
		y_array[index] = ycoord;		
	}
}

void Scene::deletepicture(int index)
{
	if ((index < 0) || (index > max-1) || (array[index] == NULL))
	{
		cout << "invalid index" << endl;
		return;
	}
	
	else 
	{	
		delete array[index];
		array[index] == NULL;
	}
}

Image * Scene::getpicture(int index) const
{
	if ((index < 0) || (index > max-1))
	{
		cout << "invalid index" << endl;
		return NULL;
	}
	else
	{
		return (array[index]);		//return a pointer to the image
	}
}


Image Scene::drawscene()const
{
	int final_height = x_array[0] + array[0]->width();	//width of 1st image				
	int final_width = y_array[0] + array[0]->height();	//height of 1st image

	for (int i = 1; i < max; i++)			//finding largest width
	{
		if (final_width <= (x_array[i] + array[i]->width()))
		{
			final_width = (x_array[i]+array[i]->width());
		}
	}
		//final_width is width of final image
	
	for (int j = 1; j < max; j++)			//finding largest width
	{
		if (final_height <= (y_array[j] + array[j]->height()))
		{
			final_height = (y_array[j]+array[j]->height());
		}
	}
		//final_height is height of final image
	
	Image *final(int final_width,int final_height);
	
	for (int m = 0; m < max; m++ )
	{
		if (array[m] != NULL)
		{
			((*this)(final_width, final_height))->red = ((x_array[m]+array[m]->width()),y_array[m]+array[m]->height())->red;
			*final(final_width, final_height)->blue = ((x_array[m]+array[m]->width()),y_array[m]+array[m]->height())->blue;
			*final(final_width, final_height)->green = ((x_array[m]+array[m]->width()),y_array[m]+array[m]->height())->green;
		}
	}
	return final;
	
//*final(final_width, final_height)
}

/*
 * copy helper function
 */
void Scene::copy(const Scene & other)		//see if shallow & deep copy
{
	for (int i = 0; i < max; i++)					
	{
		array[i] = new Image (*(other.array[i]));	//would it be other->array[i]
		x_array[i] = other.x_array[i];
		y_array[i] = other.y_array[i];
	} 
}	

/**
  *	Destructor operator clear helper function 	
  */
void Scene::clear()
{
	if (array != NULL) 
	{
		delete []array;
		array = NULL;	
	
		delete []x_array;
		x_array = NULL;
		
		delete []y_array;
		y_array = NULL;
	}
}

/**
  *	Scene destructor	
  */
Scene::~Scene()
{
	clear();
} 

