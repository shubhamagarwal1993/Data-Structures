/**
 * @file dsets.cpp
 * Implementation of Disjoint Sets class.
*/

#include "dsets.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>

using namespace std;

//=========================================================================
void DisjointSets::addelements(int num)
{
	for(int i = 0; i < num; i++)
	{
		vec.push_back(-1);
	}
}	

//==========================================================================
int DisjointSets::find(int elem)
{
	if(vec[elem] < 0)
		return elem;
	
	else
		return vec[elem] = find(vec[elem]);
}

//===========================================================================
void DisjointSets::setunion(int a, int b)
{
	if((a < 0) || (b < 0) || (a > vec.size()-1) || (b > vec.size()-1))
		return;
	
	else	
	{
		int root1 = find(a);
		int root2 = find(b);
		
		int newSize = vec[root1] + vec[root2];

		if(isBigger(vec[root1], vec[root2]))
		{
			vec[root1] = root2;
			vec[root2] = newSize;
		}	
		else
		{
			vec[root2] = root1;
			vec[root1] = newSize;
		}
	}
}			

bool DisjointSets::isBigger(int a, int b)
{
	if(a > b)
		return true;
		
	return false;	
}
//=============================================================================

