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
#include <queue>
#include <map>
using namespace std;

//=================== NO PARAMETER CONSTRUCTOR =============================

SquareMaze::SquareMaze()	
{}

//==========================================================================
SquareMaze::dualBool::dualBool()
	: rightWalls(true), bottomWalls(true), haveVisited(false)
{}
//==========================================================================
SquareMaze::~SquareMaze()
{
	for(int i=0;i<w;i++)
		delete []maze[i];
	delete []maze;
}
//=========================== MAKE MAZE ====================================
void SquareMaze::makeMaze(int width, int height)
{

	//we have to clear all that was present;
//	if(maze != NULL)
//	{
//		delete maze;
//		maze = NULL;
//	}
	
	DisjointSets a;
	
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

	if(dir == 0)
		maze[x][y].rightWalls = exists;
	
	else if(dir == 1)
		maze[x][y].bottomWalls = exists;
}		

//==========================  SOLVE MAZE ====================================		

vector< int > SquareMaze::solveMaze()
{

	for(int m = 0; m < w; m++)
		for(int n = 0; n < h; n++)
			maze[m][n].haveVisited = false;

	
	
	vector<int> pred(w*h, -1);
	vector<int> dist(w*h, 0);
	
	queue<int> temp;
	temp.push(0);
	
	maze[0][0].haveVisited = true;
	
	int x = 0;
	int y = 0;
	 
//	cout << "start of loop" <<endl;
	 
	int front; 
	while(!temp.empty())
	{
		front = temp.front();
		temp.pop();	

		//x = front/h;									//check
		//y = front%h;									//check
		x = front%h;									//check
		y = front/h;									//check

		if(/*(x < w-1)*/ canTravel(x, y, 0) && maze[x+1][y].haveVisited==0)				//if there is a right path
		{
			pred[front+1] = front;		
			dist[front+1] = dist[front]+1;

			maze[x+1][y].haveVisited = true;

			temp.push(front+1);						
		}	
	
		if(/*(y < h-1)*/ canTravel(x, y, 1) && maze[x][y+1].haveVisited == 0)			//if there is a down path
		{
			pred[h+front] = front;		
			dist[h+front] = dist[front]+1;
			maze[x][y+1].haveVisited = true;
			temp.push(front+h);	
		}
		
		
		if(/*(x > 0)*/ canTravel(x, y, 2) && maze[x-1][y].haveVisited == 0)				//if there is a left path
		{
			pred[front-1] = front;		
			dist[front-1] = dist[front]+1;
			maze[x-1][y].haveVisited = true;
			temp.push(front-1);						
		}

		if(/*(y > 0)*/ canTravel(x, y, 3) && maze[x][y-1].haveVisited == 0)				//if there is a up path
		{
			pred[front-h] = front;		
			dist[front-h] = dist[front]+1;
			maze[x][y-1].haveVisited = true;
			temp.push(front-h);						
		}
	}
	
/*	for(int i = 0; i < w*h; i++)
	{
		cout <<" "<< dist[i];
	}
	cout << endl;
	for(int i = 0; i < w*h; i++)
	{
		cout <<" "<< pred[i];
	}
*/	
	
	int max = w*h-w;
	
	for(int i = 1; i < w; i++)
	{
		if(dist[(w*h)-w + i] > dist[max])
		{
			max = (w*h)- w + i;
		}	
	}
	
//	int new_x;
//	for(int i = (w*h)-w; i <= w*h-1; i++)
//	{
//		if(dist[i] == max)
//		{
//			new_x = i;
//			break;
//		}
//	}	
	
//	cout << " end " << endl;  
		
	int follow = max;
	vector<int> direction;
	while(pred[follow] != -1)
	{
		if(pred[follow] == follow+1)						//right
		{
			direction.insert(direction.begin(), 2);
			follow = pred[follow];
			continue;
		}
		
		x = front/h;									//check
		y = front%h;									//check
		if(pred[follow] == follow-1)						//left
		{
			direction.insert(direction.begin(), 0);
			follow = pred[follow];
			continue;
		}
		
		if(pred[follow] == follow + h)						//down
		{
			direction.insert(direction.begin(), 3);
			follow = pred[follow];
			continue;
		}
		
		if(pred[follow] == follow - h)						//up
		{
			direction.insert(direction.begin(), 1);
			follow = pred[follow];
			continue;
		}
	}
	maximum = max;
	
//	cout << "size of vector: " << direction.size() <<endl;
//	cout << "end of loop" << endl;		
	return direction;
}
//==========================  DRAW MAZE ====================================
PNG * SquareMaze::	drawMaze()const			//have to edit this function in own way = in the end
{
	PNG * temp = new PNG();
	temp->resize(w*10+1,h*10+1);

	unsigned int i,j,k;

	for(i = 0; i < h*10+1; i++)
	{
		(*temp)(0,i)->red=0;
		(*temp)(0,i)->green=0;
		(*temp)(0,i)->blue=0;
	}
	
	for(i = 10; i < w*10+1; i++)
	{
		(*temp)(i,0)->red=0;
		(*temp)(i,0)->green=0;
		(*temp)(i,0)->blue=0;
	}
	
	for(i = 0;i < w; i++)
	{
		for(j = 0;j < h; j++)
		{
			if(maze[i][j].rightWalls)
			{
				for(k = 0;k <= 10; k++)
				{
					 (*temp)((i+1)*10,j*10+k)->red=0;
					 (*temp)((i+1)*10,j*10+k)->green=0;
					 (*temp)((i+1)*10,j*10+k)->blue=0;
				}
			}
			if(maze[i][j].bottomWalls)
			{
				for(k=0;k<=10;k++)
				{
					 (*temp)(i*10+k,(j+1)*10)->red=0;
					 (*temp)(i*10+k,(j+1)*10)->green=0;
					 (*temp)(i*10+k,(j+1)*10)->blue=0;
				}
			}
		}
	}
	
	return temp;
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
	PNG* out = drawMaze();

	vector<int> path = solveMaze();

//	cout << "size of path:  " <<path.size() << endl;

	int x, y, i, j;
	x = y = 5;

//	cout << "size of path: " << path.size() << "\n";
//	cout << "before while\n";

	while(!path.empty())
	{
		switch (path[0])
		{
			case 0://right
				for(i = 0; i < 11; i++)
				{
					(*out)(x+i, y)->red = 255;
					(*out)(x+i, y)->green = (*out)(x+i, y)->blue  = 0;
				}
//								cout << "value of i: " << i << '\n';
				x += (i-1);
				break;
			case 1://down
				for(j = 0; j < 11; j++){
					(*out)(x, y+j)->red = 255;
					(*out)(x, y+j)->green = (*out)(x, y+j)->blue  = 0;
				}
				y += (j-1);
				break;
			case 2://left
				for(i = 0; i < 11; i++){
					(*out)(x-i, y)->red = 255;
					(*out)(x-i, y)->green = (*out)(x-i, y)->blue  = 0;
				}
				x -= (i-1);
				break;
			case 3://up
				for(j = 0; j < 11; j++){
					(*out)(x, y-j)->red = 255;
					(*out)(x, y-j)->green = (*out)(x, y-j)->blue  = 0;
				}
				y -= (j-1);
				break;
			default:
				break;
		}
		path.erase(path.begin());
	}
//	cout << "after while\n";
	for(int k = 0; k < 9; k++)
		(*out)(x-4+k,y+5)->red = (*out)(x-4+k,y+5)->green = (*out)(x-4+k,y+5)->blue = 255;
	return out;
}

//=====================================================================
//				HELPER FUNCTIONS
//=====================================================================
void SquareMaze::clear()
{
	for(int i = 0 ; i < w; i++)
 	{
 		delete[] maze[i];
 	}	 
 	delete[] maze;
}	


//=================================================================================


