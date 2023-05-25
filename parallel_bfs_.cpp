

//  PREPROCESSING INSTRUCTIONS
#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <omp.h>

//using namespace std;


// Function to perform BFS from a given vertex
void bfs(int startVertex, std::vector<bool> &visited, std::vector< std::vector<int> > &graph)
{
    // Create a queue for BFS
    std::queue<int> q;

    // Mark the start vertex as visited and enqueue it
    visited[startVertex] = true;
    q.push(startVertex);

    // Loop until the queue is empty
    while (!q.empty())
    {
        // Dequeue a vertex from the queue
        int v = q.front();
        q.pop();

        // Enqueue all adjacent vertices that are not visited
        #pragma omp parallel for
        for (int i = 0; i < graph[v].size(); i++) 
        {
            int u = graph[v][i];
            #pragma omp critical
            {
               if (!visited[u])
               {
                  visited[u] = true;
                  q.push(u);
               }
            }
        }

        //
    }

    return;
}

// Parallel Breadth-First Search
void parallelBFS(std::vector<std::vector<int>> &graph, int numCores)
{
    int numVertices = graph.size();

    std::vector<bool> visited(numVertices, false); // Keep track of visited vertices

    double startTime = omp_get_wtime(); // Start timer

    // Perform BFS from all unvisited vertices using specified number of cores#pragma omp parallel for num_threads(numCores)
    for (int v = 0; v < numVertices; v++)
    {
        if (!visited[v])
        {
           bfs(v, visited, graph);
        }
    }

    double endTime = omp_get_wtime(); // End timer

    std::cout << "Number of cores used: " << numCores << std::endl;
    std::cout << "Time taken: " << endTime - startTime << " seconds" << std::endl;
    std::cout << "------------------------" << std::endl;

    return;
}


// ENTRY POINT OF MAIN FUNCTION
int main(void)
{

    // Generate a random graph with 10,000 vertices and 50,000 edges
    int numVertices = 10000;
    int numEdges = 50000;

    std::vector<std::vector<int>> graph(numVertices);
    srand(time(0));
    for (int i = 0; i < numEdges; i++)
    {
        int u = rand() % numVertices;
        int v = rand() % numVertices;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Array containing number of cores
    int numCoresArr[] = {1, 2, 3, 4, 5, 6, 7, 8};

    // Loop over different number of cores and execute parallel BFS
    for (int i = 0; i < sizeof(numCoresArr) / sizeof(numCoresArr[0]); i++)
    {
        int numCores = numCoresArr[i];
        std::cout << "Running parallel BFS with " << numCores << " core(s)..." << std::endl;
        parallelBFS(graph, numCores);
    }

    return 0;
}


