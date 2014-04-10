/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

//#include "kdtree.h"
#include <iostream>
//#include <math.h>
//#include <cmath>
//#include <array>
#include <vector>
using namespace std;

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

//	if ((first.size() = 0) || (second.size() == 0))
//		return false;
	
//	else if(curDim < 0 || (first.size() < curDim) || (second.size() < curDim))
//		return false;
		
	if (first[curDim] <= second[curDim])
		return true;
		
	else
		return false;	
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
    return false;
}
//====================	CONSTRUCTOR	===========================================================
template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
}
    /**
     * @todo Implement this function!
     */
	
/*	clear(root);						//make root NULL in clear function
	root = new Point();
	root = newPoints[floor(newPoints.size()/2)];
	int nodes = Dim;
	buildhelper(root, nodes, newPoints, 0);
			
}

//helper

void KDTree<Dim>::build_helper(* &subRoot, int nodes, vector< Point<Dim> > & vec, int i;)
{
	if(vec.empty())
		return;
	
		//check if 'i' is proper
	if(smallerDimVal(a,b, i))
	{
		
	}
	
	else
	build_helper();
	
	
	
	
	build_helper();


}
*/
//=============================================================================================
template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
   return Point<Dim>();
}
