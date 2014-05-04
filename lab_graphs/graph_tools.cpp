/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  	vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
  if(graph.getEdges().size()==0) return 0;
  
    queue<Vertex> vq;
    Vertex v = start;

    graph.setVertexLabel(v, "VISTED");
    vq.push(v);

    std::map <Vertex, Vertex> gmap;
    std::vector<Vertex> adj;

    while(!vq.empty())
    {
    	v=vq.front();
    	vq.pop();

    	adj=graph.getAdjacent(v);

    	for(int i=0; i<adj.size(); i++)
    	{
    		Vertex w = adj[i];
    		if(graph.getVertexLabel(w).compare("")==0)
    		{
    			gmap[w]=v;
    			graph.setEdgeLabel(v,w, "DISCOVERY");
    			graph.setVertexLabel(w, "VISTED");
    			vq.push(w);
    		}
    		else if(graph.getEdgeLabel(v,w).compare("")==0)
    		{
    			graph.setEdgeLabel(v,w,"CROSS");
    		}
    	}
    }
    int counter=0;
    while(end!=start)
    {
    	graph.setEdgeLabel(end, gmap[end], "MINPATH");
    	end = gmap[end];
    	counter++;
    }

    return counter;
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
	Vertex start = graph.getStartingVertex();
	
	queue<Vertex> vq;
    Vertex v = start;
    int min = 99999999;
    
    graph.setVertexLabel(v, "VISTED");
    vq.push(v);
    
    std::map <Vertex, Vertex> gmap;
    std::vector<Vertex> adj;
    
    Vertex min1, min2;
    
    while(!vq.empty())
    {
    	v=vq.front();
    	vq.pop();

    	adj=graph.getAdjacent(v);

    	for(int i=0; i<adj.size(); i++)
    	{
    		Vertex w = adj[i];
    		if(graph.getVertexLabel(w).compare("")==0)
    		{
    			gmap[w]=v;
    			graph.setEdgeLabel(v,w, "DISCOVERY");
    			graph.setVertexLabel(w, "VISTED");
    			vq.push(w);
    		}
    		else if(graph.getEdgeLabel(v,w).compare("")==0)
    		{
    			graph.setEdgeLabel(v,w,"CROSS");
    		}
    		if(graph.getEdgeWeight(v,w)<=min)
    		{
    			min=graph.getEdgeWeight(v,w);
    			min1=v;
    			min2=w;
    		}
    	}
    }
    graph.setEdgeLabel(min1,min2, "MIN");
    return min;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
	int a, b;
	DisjointSets x;
	
	x.addelements(graph.getVertices().size());
	
	std::vector<Edge> edges=graph.getEdges();
	sort(edges.begin(), edges.end());
	
	for (int i = 0; i < edges.size(); i++)
	{
		a=x.find(edges[i].source);
		b=x.find(edges[i].dest);

		if(a!=b)
		{
			graph.setEdgeLabel(edges[i].source, edges[i].dest, "MST");
			x.setunion(a,b);
		}
	}
}
