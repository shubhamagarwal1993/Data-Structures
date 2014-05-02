/**
 * @file maze.h
*/

#ifndef MAZE_H
#define MAZE_H

#include "png.h"
#include <vector>
#include "dsets.h"
#include <cmath>

using std::vector;

class SquareMaze
{
	public:
		SquareMaze();
		void makeMaze(int width, int height);
		bool canTravel(int x, int y, int dir)const;
		void setWall(int x, int y, int dir, bool exists);
		vector< int > solveMaze();
		PNG * drawMaze()const;
		PNG * drawMazeWithSolution();
		
	private:
		class dualBool
		{
			public:
				dualBool();
				bool rightWalls;
				bool bottomWalls;
				
		};	
		
		DisjointSets a;

		int w;
		int h;
		dualBool** maze;
		
	//helper functions are declaration here
		void clear();

};

//#include "maze.cpp"

#endif

