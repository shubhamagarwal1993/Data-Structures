// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;
//**********************		CONSTRUCTORS	**************************************************
	/**
 	 * no argument constructor
 	 * takes no arguments, produces an empty Quadtree object, 
 	 * i.e. no associated QuadtreeNode objects, and in which root is NULL.
 	*/
 	Quadtree::Quadtree()
 	{
 		root = NULL;
 	}
 	
 	/**
	 * 2 argument constructor
	 * source : The source image to base this Quadtree on.
	 * resolution : The width, height of image 
	*/
	Quadtree::Quadtree(const PNG & source1, int resolution1)
	{	
		root=NULL;
		
		buildTree(source1, resolution1);
	}	
		
	/*
	 *	constructor for QuadtreeNode 
	*/ 
	Quadtree::QuadtreeNode::QuadtreeNode()
	{
		nwChild = NULL;
		neChild = NULL;
		swChild = NULL;
		seChild = NULL;
		element= RGBAPixel();
	}
	
	
//***************************************************************************************************

//*************************		BIG THREE	********************************************************
	/**
	 * Copy constructor
	 */
	Quadtree::Quadtree(Quadtree const & other)
	{
		root = copy_tree(other.root);				//check
		resolution = other.resolution;				//check
	}
	
	/*
	 *	helper function for copy constructor
	*/ 
	Quadtree::QuadtreeNode * Quadtree::copy_tree(QuadtreeNode * subRoot)
	{
		if (subRoot != NULL)
		{	
		
		QuadtreeNode * leafNode = new QuadtreeNode();
		leafNode->element = subRoot->element;
		leafNode->nwChild=leafNode->neChild=leafNode->swChild=leafNode->seChild = NULL;
		
		leafNode->nwChild = copy_tree(subRoot->nwChild);
			
		leafNode->neChild = copy_tree(subRoot->neChild);
		
		leafNode->swChild = copy_tree(subRoot->swChild);
		
		leafNode->seChild = copy_tree(subRoot->seChild);
		
		return leafNode;
		}
		
		else return NULL;	
	}	
	

	/**
	 * Destructor.
	*/
	Quadtree::~Quadtree()
	{
		clear_tree(root);
		resolution=0;
	}
	 
	/**
	* helper function for destructor
	* 
	*/
	void Quadtree::clear_tree(QuadtreeNode * &subRoot)
	{
		if(subRoot==NULL)
			return;
		clear_tree(subRoot->nwChild);
		clear_tree(subRoot->neChild);
		clear_tree(subRoot->swChild);
		clear_tree(subRoot->seChild);
		delete subRoot;
		subRoot=NULL;
//cout<<"all leaves have been deleted"<<endl;
//cout<<subRoot->nwChild<<endl;
//cout<<"dfG"<<endl;
	}
	
	/**
	 * operator =
	*/
/*	Quadtree const & Quadtree::operator=(Quadtree const & other)
	{
		if (this != &other)
		{
			clear_tree(root);
			resolution = 0;
			if (other.root != NULL)
			{
				root = new QuadtreeNode();
				copy_tree(other.root);				
				resolution = other.resolution;
			}
		}
		
		return * this;	
	}
*/	
	
Quadtree const & Quadtree::operator=(Quadtree const & other	)	
{
	if(this!=&other)
	{
		clear_tree(root);
		root=NULL;
		resolution=0;
		if(other.root!=NULL)
		{
			
			root = copy_tree(other.root);
			resolution=other.resolution;
		}
		
	}
	return *this;
}	
	 
	 
	 
	 
//**************************************************************************************************	 	

//*************************		The buildTree Function**********************************************
	void Quadtree::buildTree(PNG const & source1, int resolution1)
	{
		clear_tree(root);
	
		int x_coord = 0;
		int y_coord = 0;

		resolution=resolution1;
		make_tree(root, x_coord, y_coord, resolution, source1);	
	}
	
	
	void Quadtree::make_tree(QuadtreeNode * &subRoot,int x_coord, int y_coord, int resolution1, PNG const & source1)
	{
		subRoot = new QuadtreeNode();
//		if(resolution1 == 64)
//			cout << resolution1 << endl;
		
//		cout<<resolution1<<endl;
		if (resolution1 == 1)
		{
			subRoot->element = *source1(x_coord, y_coord);
			return;
		}
		
		make_tree(subRoot->nwChild, x_coord, y_coord, resolution1/2, source1);
		
//		make_tree(subRoot->neChild, x_coord, y_coord+(resolution1/2), resolution1/2, source1);
//		make_tree(subRoot->swChild, x_coord+(resolution1/2), y_coord, resolution1/2, source1);
		
		
		make_tree(subRoot->neChild, x_coord+(resolution1/2), y_coord, resolution1/2, source1);
		make_tree(subRoot->swChild, x_coord, y_coord+(resolution1/2), resolution1/2, source1);
		make_tree(subRoot->seChild, x_coord+(resolution1/2),y_coord+(resolution1/2), resolution1/2, source1);

		(subRoot->element).red = (((subRoot->nwChild->element).red) + ((subRoot->neChild->element).red) + ((subRoot->swChild->element).red) + ((subRoot->seChild->element).red))/4;	
		(subRoot->element).blue = (((subRoot->nwChild->element).blue) + ((subRoot->neChild->element).blue) + ((subRoot->swChild->element).blue) + ((subRoot->seChild->element).blue))/4;	
		(subRoot->element).green = (((subRoot->nwChild->element).green) + ((subRoot->neChild->element).green) + ((subRoot->swChild->element).green) + ((subRoot->seChild->element).green))/4;
	
	}
	
	
//**************************************************************************************************	 	

//*************************		The getPixel Function***********************************************
	RGBAPixel Quadtree::getPixel(int x, int y)const
	{
	
		if ((x<resolution) && (x >= 0) && (y < resolution) && (y >= 0) && (root != NULL))
		{
			return getPixel_helper(x, y, root, resolution);
		}	
		
			 RGBAPixel temp;			
			 return temp;
	}
	
	RGBAPixel Quadtree::getPixel_helper(int x, int y, QuadtreeNode * subRoot, int resolution1)const
	{
		if (subRoot->nwChild == NULL)
		{
			return subRoot->element;
		}
		
		if ((x < resolution1/2) && (y < resolution1/2))
		{
			/*if (subRoot->nwChild == NULL)
				return subRoot->element;
			else*/
				return getPixel_helper(x, y, subRoot->nwChild, resolution1/2);	
		}
		
		else if (x >= resolution1/2 && y < resolution1/2)
		{
			/*if (subRoot->neChild == NULL)
				return subRoot->element;
			else*/
				return getPixel_helper(x-resolution1/2, y, subRoot->neChild, resolution1/2);	
		}

		else if (x < resolution1/2 && y >= resolution1/2)
		{
			/*if (subRoot->swChild == NULL)
				return subRoot->element;
			else*/
				return getPixel_helper(x, y-resolution1/2, subRoot->swChild, resolution1/2);	
		}

		else //if (x >= resolution1/2 && y >= resolution1/2)
		{
			/*if (subRoot->seChild == NULL)
				return subRoot->element;
			else*/
				return getPixel_helper(x-resolution1/2, y-resolution1/2, subRoot->seChild, resolution1/2);	
		}
//	RGBAPixel temp;
//	return temp;	
		
	}
		
//*************************************************************************************************** 	

//*************************		The decompress Function***********************************************
	PNG Quadtree::decompress()const
	{
		if (root != NULL)
		{
			PNG temp(resolution, resolution);
			
			for (int i = 0; i < resolution; i++)
			{
				for (int j = 0; j < resolution; j++)
				{
					*temp(i, j) = getPixel(i, j);
				} 
			}
			
			return temp;	
		}
		
		return PNG();
			
		
	}

//**************************************************************************************************************	 	



//**************************	***************		********************************************************************
//	=+=+=+=+=+=+=+=+=+=+=+=+=+=			MP 5.2			+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//**************************	***************		********************************************************************



//*************************		The clockwiseRotate Function**********************************************************
	void Quadtree::clockwiseRotate()
	{
		if (root != NULL)
			rotate(root);	
	}
	
	void Quadtree::rotate(QuadtreeNode * subRoot)
	{
	
		if (subRoot == NULL)
			return;
					
		QuadtreeNode* temp = subRoot->nwChild;
		subRoot->nwChild = subRoot->swChild;
		subRoot->swChild = subRoot->seChild;
		subRoot->seChild = subRoot->neChild;
		subRoot->neChild = temp;
		temp = NULL;
		
		rotate(subRoot->nwChild);
		rotate(subRoot->neChild);
		rotate(subRoot->swChild);
		rotate(subRoot->seChild);
		
	}
	
//**************************************************************************************************************	 	

//*************************		The prune Function**********************************************************

	void Quadtree::prune(int tolerance)	
	{
		return;
		prune_helper(root, tolerance);
	}
	
	void Quadtree::prune_helper(QuadtreeNode * subRoot, int tolerance)
	{
		if(subRoot == NULL)
			return;

		if (diff_prune(subRoot, subRoot->element, tolerance))
		{
			clear_tree(subRoot->nwChild);
			clear_tree(subRoot->neChild);
			clear_tree(subRoot->swChild);
			clear_tree(subRoot->seChild);
//			cout<<"after clear"<<endl;
//			cout<<subRoot<<endl;
			return; 
		}
		
		prune_helper(subRoot->nwChild, tolerance);
		prune_helper(subRoot->neChild, tolerance);
		prune_helper(subRoot->swChild, tolerance);
		prune_helper(subRoot->seChild, tolerance);
	}
//================================================================================================	
	bool Quadtree::diff_prune(QuadtreeNode * subRoot, RGBAPixel temp, int tolerance)
	{
		if(subRoot == NULL)
		{
			return false;
		}

		if (subRoot->nwChild == NULL)
		{
			int my_tol =  pow((subRoot->element.red - temp.red), 2) + pow((subRoot->element.green - temp.green), 2) + pow((subRoot->element.blue - temp.blue), 2);
			if (my_tol <= tolerance)
				return true;
			else
				return false;
		}
		
		return diff_prune(subRoot->nwChild, temp, tolerance) && diff_prune(subRoot->neChild, temp, tolerance) && diff_prune(subRoot->swChild, temp, tolerance) && diff_prune(subRoot->seChild, temp, tolerance);
	}

//**************************************************************************************************************

//*************************		The pruneSize Function**********************************************************

	int Quadtree::pruneSize(int tolerance)const
	{
		return tolerance;
	}
//**************************************************************************************************************

//*************************		The idealPrune Function**********************************************************

	int Quadtree::idealPrune(int numLeaves)const
	{
		return numLeaves;	
	}	
//**************************************************************************************************************

