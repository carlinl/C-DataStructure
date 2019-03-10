//
//  Graph.h
//  Assignment2
//
//  Created by JIHUI LIANG on 21/1/19.
//  Copyright © 2019 JIHUI LIANG. All rights reserved.
//

#ifndef Graph_h
#define Graph_h
#include <stdbool.h>

typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
    Vertex v;
    Vertex w;
} Edge;

Graph newGraph(int);
void  insertEdge(Graph, Edge);
void  removeEdge(Graph, Edge);
bool  adjacent(Graph, Vertex, Vertex);
void  showGraph(Graph);
void  freeGraph(Graph);

#endif /* Graph_h */
