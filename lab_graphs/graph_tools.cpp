/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 *
 * @param graph - the graph to search
 * @return the minimum edge weight
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    // TODO
    // 1. Label all edges and vertices as unexplored. You will need
    //    to look in graph.h for the right functions.

    // 2. Use the BFS function in graph_tools to find the minimum edge.
    //    Don't forget to label it.

    
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge> edges = graph.getEdges();
    for (Vertex v : vertices) {
        graph.setVertexLabel(v, "UNEXPLORED");
    }
    for (Edge e : edges) {
        graph.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }

   
    Vertex start = vertices[0];
    Edge minEdge = BFS(graph, start);

    
    graph.setEdgeLabel(minEdge.source, minEdge.dest, "MIN");

   
    return minEdge.weight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
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
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    unordered_map<Vertex, Vertex> parent;

    // TODO
    // 1. Set all vertices as unexplored

    // 2. Do a modified BFS. See the BFS function below as a guideline, but
    //    your BFS here only needs to populate the "parent" map and stop once the short-
    //    est path has been found.

    // 3. Use the unordered map to trace from a path from the end to the start,
    //    counting edges. You should set edges to "minpath" here too.

   
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge> edges = graph.getEdges();
    for (Vertex v : vertices) {
        graph.setVertexLabel(v, "UNEXPLORED");
    }
    for (Edge e : edges) {
        graph.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }

    
    queue<Vertex> q;
    unordered_map<Vertex, bool> visited;


    
    graph.setVertexLabel(start, "VISITED");
    visited[start] = true;
    q.push(start);

    bool foundEnd = false;

   
    while (!q.empty() && !foundEnd) {
        Vertex current = q.front();
        q.pop();

     
        vector<Vertex> adj = graph.getAdjacent(current);
        for (Vertex & neighbor : adj) {
        
            if (graph.getVertexLabel(neighbor) == "UNEXPLORED") {
                graph.setVertexLabel(neighbor, "VISITED");
                graph.setEdgeLabel(current, neighbor, "DISCOVERY");
                parent[neighbor] = current;
                q.push(neighbor);

                if (neighbor == end) {
                    foundEnd = true;
                    break;
                }
            }
          
            else if (graph.getEdgeLabel(current, neighbor) == "UNEXPLORED") {
                graph.setEdgeLabel(current, neighbor, "CROSS");
            }
        }
    }

    // 3. Now we use the parent map to trace back from 'end' to 'start'
    //    and label each edge along this path as "MINPATH".
    //    Also count the edges to get the distance.
    if (!foundEnd) {
    
        return -1;
    }

    int distance = 0;
    Vertex current = end;
  
    while (current != start) {
        Vertex p = parent[current];
 
        graph.setEdgeLabel(current, p, "MINPATH");
        current = p;
        distance++;
    }

    return distance;
}

/**
 * Finds a minimal spanning tree on a graph.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class given in dsets.cpp to help you with
 *  Kruskal's algorithm.
 *
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
  
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge> edges = graph.getEdges();
    for (Vertex v : vertices) {
        graph.setVertexLabel(v, "UNEXPLORED");
    }
    for (Edge e : edges) {
        graph.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }

    std::sort(edges.begin(), edges.end(), [](const Edge & a, const Edge & b) {
        return a.weight < b.weight;
    });

   
    unordered_map<Vertex, int> vertexIndex;
    for (size_t i = 0; i < vertices.size(); i++) {
        vertexIndex[vertices[i]] = (int)i;
    }

    DisjointSets ds;
    ds.addelements(vertices.size());

   
    int edgesAdded = 0;
    int needed = (int)vertices.size() - 1;  

    for (Edge & e : edges) {
        int root1 = ds.find(vertexIndex[e.source]);
        int root2 = ds.find(vertexIndex[e.dest]);
        
        if (root1 != root2) {
            ds.setunion(root1, root2);
            graph.setEdgeLabel(e.source, e.dest, "MST");
            edgesAdded++;
            if (edgesAdded == needed)
                break;
        }
    }
}

/**
 * Does a BFS of a graph, keeping track of the minimum
 *  weight edge seen so far.
 * @param g - the graph
 * @param start - the vertex to start the BFS from
 * @return the minimum weight edge
 */
Edge GraphTools::BFS(Graph& graph, Vertex start)
{
    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    Edge min;
    min.weight = INT_MAX;

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        vector<Vertex> adj = graph.getAdjacent(v);
        for (size_t i = 0; i < adj.size(); ++i) {
            if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "DISCOVERY");
                graph.setVertexLabel(adj[i], "VISITED");
                q.push(adj[i]);
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            } else if (graph.getEdgeLabel(v, adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "CROSS");
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            }
        }
    }
    return min;
}
