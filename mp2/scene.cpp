#include "scene.h"
#include "image.h"
#include "png.h"
#include "rgbapixel.h"
#include<iostream>

using namespace std;	
//***************************************************************
Scene::Scene(int size)
{
	max = size;						//'max' is a member variable
	
	array = new Image*[max];		//dymanic array
	
	x_array = new int[max];
	y_array  = new int[max];
	
	for (int i = 0; i < max; i++)	//make all NULL
	{
		array[i] = NULL;
	}
}
//*******************************************************************
Scene::Scene(const Scene & source)	
{
	copy(source);					//call helper function
}
//********************************************************************
const Scene & Scene::operator=	(const Scene & source)	
{
	if (this != &source)			//check for self assignment
	{					
		clear();					//delete everything that Scene has allocated
		copy(source);				//make Scene an independent copy of the source
		return (*this);
	 }
	else
	return (*this);					//return  a reference to the current instance
}
//**********************************************************************************
void Scene::changemaxlayers(int newmax)	
{
//we will have 2 conditions here
//1. if newmax<max 
//2. if newmax>=max 

//1. if newmax < max 
	if (newmax < max)
	{
		for (int i = newmax; i < max; i++)
		{
			if(array[i] != NULL)
			{
				cout << "invalid newmax" <<endl;//more images space in newmax 
				return;	
			}
			
			if(array[i] == NULL)
			{
				Image** size_change_array = new Image*[newmax];	//dymanic array
				int * size_change_x = new int[newmax];
				int * size_change_y = new int[newmax];
		
				for (int i = 0; i < newmax; i++)				//made new array NULL		
				{
					size_change_array[i] = NULL;
					size_change_x[i] = 0;
					size_change_y[i] = 0;
				}
		
				for (int i = 0; i < newmax; i++)				//copy over all elememnts
				{
					size_change_x[i] = x_array[i];
					size_change_y[i] = y_array[i];
			
					if (array[i] != NULL)
					{
						size_change_array[i] = array[i];
						array[i] = NULL;
					}		
					else
						size_change_array[i] = NULL;
				}		
		
				delete []x_array;
				delete []y_array;
				x_array = NULL;
				y_array = NULL;
				delete []array;
				array = NULL;	
		
				x_array = size_change_x;
				y_array = size_change_y;
				array = size_change_array;
				max = newmax;
				
			}

		}
	}			
//2. if newmax >= max 
	if (newmax >= max)
	{
		Image** size_change_array = new Image*[newmax];	//dymanic array
		int * size_change_x = new int[newmax];
		int * size_change_y = new int[newmax];
		
		for (int i = 0; i < newmax; i++)				//made new array NULL		
		{
			size_change_array[i] = NULL;
			size_change_x[i] = 0;
			size_change_y[i] = 0;
		}
		
		for (int i = 0; i < max; i++)		//copy over all elememnts
		{
			size_change_x[i] = x_array[i];
			size_change_y[i] = y_array[i];
			
			if (array[i] != NULL)
			{
				size_change_array[i] = array[i];
				array[i] = NULL;
			}		
			else
				size_change_array[i] = NULL;
		}		
		
		delete []x_array;
		delete []y_array;
		x_array = NULL;
		y_array = NULL;
		delete []array;
		array = NULL;	
		
		x_array = size_change_x;
		y_array = size_change_y;
		array = size_change_array;
		max = newmax;
	} 
}	
//***************************************************************************
void Scene::addpicture(const char * FileName, int index, int x1, int y1)
{
	if((index<0)||(index>=max))
	{
		cout<<"index out of bounds"<<endl;
	    return;
	}
	x_array[index]=x1;
	y_array[index]=y1;
    
	if(array[index] != NULL)
	{
       	delete array[index];
    }

	Image* temp_image=new Image;
  	temp_image->readFromFile(FileName);
    array[index] = temp_image;
	
}
//****************************************************************************

void Scene::changelayer	(int index, int newindex)
{
	
	if ((index < 0) || (index > max-1) || (newindex < 0)|| (newindex > max-1))
	{
		cout << "invalid index" << endl;			
		return;
	}
	
	if (index == newindex)
	{
		return;
	}			
	
	x_array[newindex] = x_array[index];	
	y_array[newindex] = y_array[index];
	
	if (array[newindex] != NULL)
	{
		delete array[newindex];
	}
		
	if (array[index] == NULL)
	{
		array[newindex] = NULL;
	}	

	else 
	{
		array[newindex] = array[index];
		array[index] = NULL;
	}
}
//**********************************************************************
void Scene::translate(int index, int xcoord, int ycoord)
{
	if ((index < 0) || (index > max-1) || (array[index] == NULL))
	{
		cout << "invalid index" << endl;
		return; 
	}
	else
	{
		x_array[index] = xcoord;
		y_array[index] = ycoord;		
	}
}
//***********************************************************************
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
		array[index] = NULL;
	}
}
//***********************************************************************
Image * Scene::getpicture(int index) const
{
	if ((index < 0) || (index > max-1)||array[index] == NULL)
	{
		cout << "invalid index" << endl;
		return NULL;
	}
	else
	{
		return (array[index]);		//return a pointer to the image
	}
}

//**************************************************************************
Image Scene::drawscene()const
{
	unsigned int final_height = 0;			//height of 1st image				
	unsigned int final_width = 0;			//width of 1st image

	for (int i = 0; i < max; i++)			//finding largest width
	{
		if (array[i] != NULL)
		{
			if (final_width < (x_array[i] + array[i]->width()))
			{
				final_width = x_array[i] + array[i]->width();
			}
		
			if (final_height < (y_array[i] + array[i]->height()))
			{
				final_height = y_array[i] + array[i]->height();
			}
		}
	}	
	
	Image final;
	final.resize(final_width, final_height);
	
	for (int i = 0; i < max; i++ )
	{
		if (array[i] != NULL)
		{
			for (size_t a = 0; a < array[i]->width(); a++)
			{
				for (size_t b = 0; b < array[i]->height(); b++)
				{
					final(a + x_array[i], b + y_array[i])->red = (*array[i])(a,b)->red; 
					final(a + x_array[i], b + y_array[i])->green = (*array[i])(a,b)->green; 
					final(a + x_array[i], b + y_array[i])->blue = (*array[i])(a,b)->blue; 
				}					
			}
		}
	}
	return final;
}
//***********************************************************************************
/*
 * copy helper function
 */
void Scene::copy(const Scene & other)		//deep copy
{
	max = other.max;
	x_array = new int [max];
	y_array = new int [max];
	array = new Image * [max];
	
	for (int i = 0; i < max; i++)					
	{
		x_array[i] = other.x_array[i];
		y_array[i] = other.y_array[i];

		if (other.array[i] != NULL)
		{
			array[i] = new Image (*other.array[i]);	
		}
		else 
		{
			array[i] = NULL;		
		}
	} 
}	
//********************************************************************************
/**
  *	Destructor operator clear helper function 	
  */
void Scene::clear()
{
	
	delete []x_array;
	x_array = NULL;
		
	delete []y_array;
	y_array = NULL;
	
	for (int i = 0; i < max; i++)
	{
		if (array[i] != NULL)
		{
			delete array[i];
			array[i] = NULL;	
		}
	}
	
	delete []array;
	array = NULL;
}
//**********************************************************************************
/**
  *	Scene destructor	
  */
Scene::~Scene()
{
	clear();
} 

