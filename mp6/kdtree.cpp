/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include "kdtree.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
using namespace std;
//=============================================================================================================
template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
	if (first[curDim] < second[curDim])
		return true;
		
	else if ((first[curDim] == second[curDim]) && (first < second))
		return true;
			
	else
		return false;	
}
//===================================================================================================

template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
	if(dist(potential, target) < dist(currentBest, target))
		return true;
		
	else if	((dist(potential, target) == dist(currentBest, target)) && (potential < currentBest))	
		return true;

    return false;
}

template<int Dim>
int KDTree<Dim>::dist(const Point<Dim> & temp, const Point<Dim> & target) const
{
	int sum = 0;
	for(int i = 0; i < Dim; i++)
	{
		sum += ((target[i] - temp[i])*(target[i] - temp[i]));
	}

	return sum;	
}

//====================	CONSTRUCTOR	===========================================================
template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    points = newPoints;
    constHelp(points, 0, (points.size()-1), (points.size()-1)/2, 0);
}

template<int Dim>
void KDTree<Dim>::constHelp(vector< Point<Dim> > & Points, int left, int right, int center, int dimension)
{
	if (left< right)
	{
    	get_val(points, left, right, center, dimension);

	    dimension = (dimension+1) % Dim;

	    constHelp(points, left, center-1, (left+center-1)/2, dimension);
	    constHelp(points, center+1, right, (center+1+right)/2, dimension);
	}
}

template<int Dim>
Point<Dim> KDTree<Dim>::get_val(vector< Point<Dim> > & newPoints, int left, int right, int avg, int dimension)
{
	if (left>= right)
    	return newPoints[left];

	int val = avg;
	Point<Dim> temp_val = newPoints[val];

    Point<Dim> temp = newPoints[val];
    newPoints[val] = newPoints[right];
    newPoints[right] = temp;

    int temp_left = left;

    for(int i=left; i<right; i++)
    	if (smallerDimVal(newPoints[i], temp_val, dimension))
        {
        	Point<Dim> tem = newPoints[temp_left];
            newPoints[temp_left] = newPoints[i];
            newPoints[i] = tem;

            temp_left++;
		}

        temp = newPoints[right];
        newPoints[right] = newPoints[temp_left];
        newPoints[temp_left] = temp;


	int set_val = temp_left;
	int len = set_val;
	
	if(len == avg)
		return newPoints[set_val];
	
	else if(avg < len)
    	return get_val(newPoints, left, set_val - 1, avg, dimension);
    else
    	return get_val(newPoints, set_val + 1, right, avg, dimension);
}

//=============================================================================================



template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
	return find_helper(query, 0, points.size()-1, 0);	
}	

template<int Dim>
Point<Dim> KDTree<Dim>::find_helper(const Point<Dim> & query, int left, int right, int dim) const
{
	Point<Dim> retval;
	Point<Dim> x;
	int med = (left + right)/2;
	
	if(left>=right)
	{
		retval=points[left];
		return retval;
	}
	
	if(smallerDimVal(query,points[med],dim%Dim))
	{
		int a=0;
		if(shouldReplace(query,retval,points[med]))
			retval=points[med];
		for (int i=0;i<Dim;i++)
			a=a+pow(query[i]-retval[i],2);
		if(pow(points[med][dim%Dim]-query[dim%Dim],2)<=a)
		{
			Point<Dim> y;
			y=find_helper(query,med+1,right,(dim+1)%Dim);
			if(shouldReplace(query,retval,y))
			{
				retval=y;
			}
		}
	}
	
	else
	{
		retval=find_helper(query,med+1,right,(dim+1)%Dim);

		int a=0;
		if(shouldReplace(query,retval,points[med]))
			retval=points[med];
		for (int i=0;i<Dim;i++)
			a=a+pow(query[i]-retval[i],2);
		if(pow(points[med][dim%Dim]-query[dim%Dim],2)<=a)
		{
			Point<Dim> y;
			y=find_helper(query,left,med-1,(dim+1)%Dim);
			if(shouldReplace(query,retval,y))
			{
				retval=y;
			}
		}
	}
	return retval;	
}
