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

//=============================================================================================================
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
		sum = sum + ((target[i] - temp[i])*(target[i] - temp[i]));
	return sum;	
}

//====================	CONSTRUCTOR	===========================================================
template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    points = newPoints;
    int size = points.size()-1;
    int left = 0;
    int right = 0;
    int center = 0;
    constHelp(points, left, size, (size)/2, center);
}

template<int Dim>
void KDTree<Dim>::constHelp(vector< Point<Dim> > & Points, int left, int right, int pivotIndex, int dim)
{
	if (left >= right)
    {
    	return;
	}

    select(points, left, right, pivotIndex, dim);

    dim = (dim + 1) % Dim;
    constHelp(points, left, pivotIndex-1, (left+pivotIndex-1)/2, dim);
    constHelp(points, pivotIndex+1, right, (pivotIndex+1+right)/2, dim);
}

template<int Dim>
int KDTree<Dim>::partition(vector< Point<Dim> > & Points, int left, int right, int pivotIndex, int dim)
{
	Point<Dim> pivotValue = points[pivotIndex];

    Point<Dim> temp = points[pivotIndex];
    points[pivotIndex] = points[right];
    points[right] = temp;

    int storeIndex = left;

    for(int i=left; i<right; i++)
    	if (smallerDimVal(points[i], pivotValue, dim))
        {
        	Point<Dim> tem = points[storeIndex];
            points[storeIndex] = points[i];
            points[i] = tem;

            storeIndex++;
		}

        temp = points[right];
        points[right] = points[storeIndex];
        points[storeIndex] = temp;

        return storeIndex;
}

template<int Dim>
Point<Dim> KDTree<Dim>::select(vector< Point<Dim> > & newPoints, int left, int right, int k, int dim)
{
	if (left>= right)
    	return newPoints[left];

	int pivotNewIndex = partition(newPoints, left, right, k, dim);
	int pivotDist = pivotNewIndex;
	
	if(pivotDist == k)
		return newPoints[pivotNewIndex];
	
	else if(k < pivotDist)
    	return select(newPoints, left, pivotNewIndex - 1, k, dim);
    else
    	return select(newPoints, pivotNewIndex + 1, right, k, dim);
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
		retval=find_helper(query,left,med-1,(dim+1)%Dim);
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
