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
    quick_select(points, 0, (points.size()-1), (points.size()-1)/2, 0);
}

template<int Dim>
void KDTree<Dim>::quick_select(vector< Point<Dim> > & Points, int left, int right, int pivot, int dimension)
{
	if (left >= right)
		return;
	
	select(Points, left, right, pivot, dimension);

	dimension = (dimension+1) % Dim;

	quick_select(Points, left, pivot-1, ((left+pivot-1)/2), dimension);
	quick_select(Points, pivot+1, right, ((pivot+1+right)/2), dimension);
}

template<int Dim>
void KDTree<Dim>::select(vector< Point<Dim> > & Points, int left, int right, int pivot, int dimension)
{	
	if(left >= right)
		return;
		
	int new_pivot = partition(Points, left, right, pivot, dimension);
		
	if(new_pivot == pivot)
		return;	
		
	else if(pivot < new_pivot)
		select(Points, left, new_pivot-1, pivot, dimension);
		
	else
		select(Points, new_pivot+1, right, pivot, dimension);
}

template<int Dim>
int KDTree<Dim>::partition(vector< Point<Dim> > & Points, int left, int right, int pivot, int dimension)
{
	Point<Dim> pivot_val = Points[pivot];
	
	Point<Dim> temp = Points[pivot];
	Points[pivot] = Points[right];
	Points[right] = temp;
	
	int counter = left;
	
	for(int i = left; i < right; i++) 
	{
		if(smallerDimVal(Points[i], pivot_val, dimension))
		{
			Point<Dim> newtemp = Points[counter];
			Points[counter] = Points[i];
			Points[i] = newtemp;
			counter++;		
		}	
	} 

	temp = Points[right];
	Points[right] = Points[counter];
	Points[counter] = temp;
	return counter; 
}

//==========================================================================================

//   return Point<Dim>();

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
	Point< Dim> pnt = points[(points.size()-1)/2];
	if(points.size() != 0)
		findNearestNeighbor(query, 0, points.size()-1, pnt, 0);
	return pnt;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query, int left, int right, Point<Dim> &pnt, int dimension) const
{
	if(left >= right)
	{
		if(shouldReplace(query, pnt, points[left]))
			return points[left];
		return pnt;	
	}
	
//	int center = (left + right)/2;
	Point< Dim> final_pnt = pnt;
	dimension = (dimension+1)%Dim;
	

	if(shouldReplace(query, final_pnt, points[(left+right)/2]))
		final_pnt = points[(left+right)/2];


	if(smallerDimVal(query, points[(left+right)/2], dimension))//point smaller than mid, go left
	{
		final_pnt = findNearestNeighbor(query, left, ((left+right)/2)-1, final_pnt, dimension);
		if(dist(query, final_pnt) > pow((query[dimension]-points[(left+right)/2][dimension]), 2))
			return findNearestNeighbor(query, ((left+right)/2)+1, right, final_pnt, dimension); 		 		
	}
	
	else //if(smallerDimVal(points[(left+right)/2], query, dimension)) 
	{
		final_pnt = findNearestNeighbor(query, ((left+right)/2)+1, right, pnt, dimension);	
		if(dist(query, final_pnt) > pow((query[dimension]-points[(left+right)/2][dimension]),2))
			return findNearestNeighbor(query, left, ((left+right)/2)-1, final_pnt, dimension);
	}
	
	return final_pnt;
}
