// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"
#include <ostream>

class Quadtree
{
	public:
		/**
 		 * no argument constructor	-	mp 5.1
 		*/
 		Quadtree();
		
		/**
 		 * 2 argument constructor	-	mp 5.1
 		*/
 		Quadtree(const PNG & source1, int resolution1);
	
	
		/**
	 	* Copy constructor	-	mp 5.1
	 	*/
		Quadtree(Quadtree const & other);

		/**
		 * Destructor	-	mp 5.1
		*/
		~Quadtree();
		
			/**
		 * operator =	-	mp 5.1
		*/
		Quadtree const & operator=(Quadtree const & other);
		
		/**
		 * The buildTree Function 	-	mp 5.1
		*/
		void buildTree(PNG const & source1, int resolution1);
		
		
		/**
		 * The getPixel Function	-	mp 5.1
		*/
		RGBAPixel getPixel(int x, int y)const;
		
		
		/**
		 * The decompress Function	-	mp 5.1
		*/
		PNG decompress()const;
		
		/**
		 * The clockwiseRotate Function	-	mp 5.1
		*/
		void clockwiseRotate();	

		/**
		 * The prune Function	-	mp 5.1
		*/
		void prune(int tolerance);	
		/**
		 * The pruneSize Function	-	mp 5.1
		*/
		int pruneSize(int tolerance)const;
		/**
		 * The idealPrune Function	-	mp 5.1
		*/
		int idealPrune(int numLeaves)const;
		
	
		
		
		private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"

		/**
		 * The Constructor for QuadtreeNode class
		*/
		QuadtreeNode();
		
	};
	
		/**
	 	* pointer to root of quadtree
		*/
		QuadtreeNode* root;   

		/**
		 * the size of the image - 'd'
		*/
		int resolution; 
		
			
		/**
		 * helper function for copy
		*/
		QuadtreeNode * copy_tree(QuadtreeNode * subRoot);
		
		/**
		 * helper function for destructor	
		*/
		void clear_tree(QuadtreeNode * &subRoot);
			 
		/**
		 * helper function for getPixel 
		*/
		RGBAPixel getPixel_helper(int x, int y,QuadtreeNode * subRoot, int resolution1) const;
		
		void make_tree(QuadtreeNode * &subRoot,int x_coord, int y_coord, int resolution1, PNG const &source1);
		
		
	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
