#include "graph.h"

Graph::Graph()
{
    adj = new list<int>[2*V];
    index = 0;
}

void Graph::addEdge(int v, int w, int weight)
{
    // split all edges of weight 2 into two
    // edges of weight 1 each.  The intermediate
    // vertex number is maximum vertex number + 1,
    // that is V.
    if (weight==2)
    {
        adj[v].push_back(v+V);
        adj[v+V].push_back(w);
    }
    else // Weight is 1
        adj[v].push_back(w); // Add w to v’s list.
}

// To print the shortest path stored in parent[]
int* Graph::printShortestPath(int parent[], int s, int d)
{
    static int level = 0;

    // If we reached root of shortest path tree
    if (parent[s] == -1)
    {
        shortPath[index] = s;
        index++;
        return shortPath;
    }

    printShortestPath(parent, parent[s], d);

    level++;
    if (s < V){
        shortPath[index] = s;
        index++;}

    return shortPath;
}

// This function mainly does BFS and prints the
// shortest path from src to dest. It is assumed
// that weight of every edge is 1
int* Graph::findShortestPath(int src, int dest)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[2*V];
    int *parent = new int[2*V];

    // Initialize parent[] and visited[]
    for (int i = 0; i < 2*V; i++)
    {
        visited[i] = false;
        parent[i] = -1;
    }

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[src] = true;
    queue.push_back(src);

    // 'i' will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        int s = queue.front();

        if (s == dest)
            return printShortestPath(parent, s, dest);

        queue.pop_front();

        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it
        // visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
                parent[*i] = s;
            }
        }
    }
}
