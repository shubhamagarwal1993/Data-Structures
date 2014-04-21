/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;
    /**
     * @todo Implement this function!
     */

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
	
	int row = theSource.getRows();
	int col = theSource.getColumns();
	
	MosaicCanvas *image = new MosaicCanvas(row, col);
	
	vector<Point<3> >blocks;
	
	map< Point<3>, TileImage > block_map;
	
	for(int i = 0; i < theTiles.size(); i++)
	{
		RGBAPixel temp = theTiles[i].getAverageColor();
		Point<3> a(temp.red, temp.blue, temp.green);
		block_map[a] = theTiles[i];
		blocks.push_back(a);
	} 
	
	KDTree<3> tree(blocks);
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			RGBAPixel temp = theSource.getRegionColor(i, j);
			Point<3> query(temp.red, temp.blue, temp.green);
			Point<3> output = tree.findNearestNeighbor(query);
			
			TileImage final = block_map[output];
			image->setTile(i, j, final);
		}
	}
return image;
}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

		
		
		
		
		
		
		
		
		
		
		

