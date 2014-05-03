/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

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
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
	             if(graph.getEdges().size() == 0) return 0;
 
        vector<Vertex> allV = graph.getVertices();
        vector<Edge> allE = graph.getEdges();
        for(int i = 0; i < allV.size(); i++)
                graph.setVertexLabel(allV[i], "UNEXPLORED");
        for(int i = 0; i < allE.size(); i++)
                graph.setEdgeLabel(allE[i].source,allE[i].dest, "UNEXPLORED");
 
        queue<Vertex> vertexes;
        Vertex v = start;
        graph.setVertexLabel(v, "VISITED");
        vertexes.push(v);
        unordered_map<Vertex, Vertex> plot;
 
        vector<Vertex> adjacent;
        bool done = false;
 
        while(!vertexes.empty() && !done){
                v = vertexes.front();
                vertexes.pop();
                adjacent = graph.getAdjacent(v);
                for(int i = 0; i < adjacent.size() && !done; i++){             
                        if(adjacent[i] == end){
                                done = true;
                        }
                        else if(graph.getVertexLabel(adjacent[i]) == "UNEXPLORED"){
                                graph.setEdgeLabel(v,adjacent[i], "DISCOVERY");
                                graph.setVertexLabel(adjacent[i], "VISITED");
                                vertexes.push(adjacent[i]);
                                plot[adjacent[i]] = v;
                        }
                        else if(graph.getEdgeLabel(v,adjacent[i]) == "UNEXPLORED")
                                graph.setEdgeLabel(v,adjacent[i], "CROSS");
                }
        }
 
        graph.setEdgeLabel(v,end, "CROSS");
        int c = 1;
        graph.setEdgeLabel(v, end, "MINPATH");
        while(v != start){
                Vertex u = plot[v];
                graph.setEdgeLabel(v, u, "MINPATH");
                v = u;
                c++;
        }
 
        return c;
 
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
	  set< pair<Vertex, Vertex> > seen;
    vector<Vertex> vs = graph.getVertices();
 
        int min = 999999;
        Vertex su, sv;
   
    for(int j = 0; j < vs.size(); j++)
    {
                Vertex u = vs[j];
        vector<Vertex> adj = graph.getAdjacent(u);
        for(size_t i = 0; i < adj.size(); ++i)
        {
            Vertex v = adj[i];
            if(seen.find(make_pair(u, v)) == seen.end())
            {
                                Edge e = graph.getEdge(u, v);
                                if(e.weight < min) {
                                        min = e.weight;
                                        su = u;
                                        sv = v;
                                }
 
                seen.insert(make_pair(u, v));
                seen.insert(make_pair(v, u));
            }
        }
    }
 
        graph.setEdgeLabel(su, sv, "MIN");
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
	 int pu, pv;
        DisjointSets set;
        set.addelements(graph.getVertices().size());
        vector<Edge> edges = graph.getEdges();
        sort(edges.begin(), edges.end());
        for(int i = 0; i < edges.size(); i++) {
                pu = set.find(edges[i].source);
                pv = set.find(edges[i].dest);
                if(pu != pv) {
                        graph.setEdgeLabel(edges[i].source, edges[i].dest, "MST");
                        set.setunion(pu, pv);
                }
        }
}
