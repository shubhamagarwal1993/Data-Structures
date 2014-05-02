/**
 * @file maze.cpp
*/

#include "maze.h"
#include "dsets.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

//=================== NO PARAMETER CONSTRUCTOR =============================

SquareMaze::SquareMaze()	
{
	
}
//==========================================================================
SquareMaze::dualBool::dualBool()
	: rightWalls(true), bottomWalls(true)
{}

//=========================== MAKE MAZE ====================================
void SquareMaze::makeMaze(int width, int height)
{

	//we have to clear all that was present;
	//	clear();

	w = width;
	h = height;	
	int size = width*height;
					
	maze = new dualBool*[width];		
	for(int i = 0; i < width; i++)
		maze[i] = new dualBool[height];
		
		
	//true - if the wall is present
	//false - if the wall is absent 
	//all the walls are present in the beginning
		
		
	a.addelements(size);
	int counter = 0;	
	
	int x, y;
	srand(time(NULL));
	

	
	while(counter != (size-1))
	{
		x = rand()%width;
		y = rand()%height;
		bool flag = rand()%2;
		
		if(flag && (x+1 < width))
		{
			if((a.find(x*height + y) != a.find((x+1)*height + y))) 
			{
				a.setunion(a.find(x*height + y), a.find((x+1)*height + y));
				counter++;
				maze[x][y].rightWalls = false;
			}
		}
		else if(!flag && (y+1 < height))
		{
			if((a.find(x*height + y) != a.find(x*height + y + 1)))
			{
				a.setunion(a.find(x*height + y), a.find(x*height + y + 1));
				counter++;
				maze[x][y].bottomWalls = false;
			}
		}
	}
}	

//==========================  CAN TRAVEL ====================================		
bool SquareMaze::canTravel(int x, int y, int dir)const
{
//	0	-	rightward 
//	1	-	downward
//	2	-	leftward
//	3	-	upward

	if(dir == 0)			
	{
		if(x == w-1)
			return false;
		else if(maze[x][y].rightWalls)
			return false;
		else 
			return true;			
	}
	else if(dir == 1)
	{
		if(y == h-1)
			return false;
		else if(maze[x][y].bottomWalls)
			return false;
		else 
			return true;		
	}
	else if(dir == 2)
	{
		if(x == 0)
			return false;
		else if(maze[x-1][y].rightWalls)
			return false;
		else 
			return true;		
	}
	else if(dir == 3)
	{
		if(y == 0)
			return false;
		else if(maze[x][y-1].bottomWalls)
			return false;
		else 
			return true;		
	}
	else
		return false;
}

//==========================  SET WALL ====================================		
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{		//Sets whether or not the specified wall exists
//	dir 	-	0		-	right	
//	dir		-	1		-	down
//	
//	exists	-	true	-	setting the wall to exist	
//	exists	-	false	-	setting the wall to not exist


	//	do we have to care about copying the side walls	-	am i already raking that into picture??????????
	
	
	if(dir == 0)
	{
		maze[x][y].rightWalls = exists;
	}	

	else if(dir == 1)
	{
		maze[x][y].bottomWalls = exists;
	}
}		

//==========================  SOLVE MAZE ====================================		
vector< int > SquareMaze::solveMaze()
{
	/*
	int length = 0;							//counts the number of steps
	int final_length = 0;					//keeps the final lengh
	int x = 0;								//stores the x coordinate of the e;;
	for(int i = 0; i < width; i++)			//checks all the bottom cells
	{
		maze[i][height-1];
		
	}
	*/
	
	vector< int > temp;
	return temp;
}	

//==========================  DRAW MAZE ====================================
PNG * SquareMaze::drawMaze()const			//have to edit this function in own way = in the end
{
	
	PNG * output = new PNG();
	output->resize(w*10+1,h*10+1);

	unsigned int i,j,k;

	for(i = 0; i < h*10+1; i++)
	{
		(*output)(0,i)->red=0;
		(*output)(0,i)->green=0;
		(*output)(0,i)->blue=0;
	}
	
	for(i = 10; i < w*10+1; i++)
	{
		(*output)(i,0)->red=0;
		(*output)(i,0)->green=0;
		(*output)(i,0)->blue=0;
	}
	
	for(i = 0;i < w; i++)
	{
		for(j = 0;j < h; j++)
		{
			if(maze[i][j].rightWalls)
			{
				for(k = 0;k <= 10; k++)
				{
					 (*output)((i+1)*10,j*10+k)->red=0;
					 (*output)((i+1)*10,j*10+k)->green=0;
					 (*output)((i+1)*10,j*10+k)->blue=0;
				}
			}
			if(maze[i][j].bottomWalls)
			{
				for(k=0;k<=10;k++)
				{
					 (*output)(i*10+k,(j+1)*10)->red=0;
					 (*output)(i*10+k,(j+1)*10)->green=0;
					 (*output)(i*10+k,(j+1)*10)->blue=0;
				}
			}
		}
	}
	return output;
}

/*
	PNG * temp = new PNG();
	temp->resize(w*10+1, h*10+1);

	for(int i = 0; i < w; i++)
	{
		temp(w,0)->red = 0;
		temp(w,0)->green = 0;
		temp(w,0)->blue = 0;
	}
	
	for(int i = 0; i < h; i++)
	{
		temp(0,h)->red = 0;
		temp(0,h)->green = 0;
		temp(0,h)->blue = 0;
	}
	
	return temp;

*/




//==========================  DRAW MAZE WITH SOLUTION =============================
PNG * SquareMaze::drawMazeWithSolution()
{
	PNG * temp;
	return temp;
}	


//=====================================================================
//				HELPER FUNCTIONS
//=====================================================================
void SquareMaze::clear()
{

}

























