
// PREPROCESSING INSTRUCTIONS
#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <omp.h>

//using namespace std;

// Function to perform DFS from a given vertex
void dfs(int startVertex, std::vector<bool> &visited, std::vector< std::vector<int> > &graph)
{
    // Create a stack for DFS
    std::stack<int> s;

    // Mark the start vertex as visited and push it onto the stack
    visited[startVertex] = true;
    s.push(startVertex);

    // Loop until the stack is empty
    while (!s.empty())
    {
        // Pop a vertex from the stack
        int v = s.top();
        s.pop();
        // Push all adjacent vertices that are not visited onto the stack
        #pragma omp parallel for
        for (int i = 0; i < graph[v].size(); i++)
        {
            int u = graph[v][i];
            #pragma omp critical
            {
                if (!visited[u])
                {
                   visited[u] = true;
                   s.push(u);
                }
            }
        }

        //
    }

    return;
}



// Parallel Depth-First Search
void parallelDFS(std::vector< std::vector<int> > &graph, int numCores)
{
    int numVertices = graph.size();

    std::vector<bool> visited(numVertices, false); // Keep track of visited vertices

    double startTime = omp_get_wtime(); // Start timer

    // Perform DFS from all unvisited vertices using specified number of cores#pragma omp parallel for num_threads(numCores)
    for (int v = 0; v < numVertices; v++)
    {
       if (!visited[v])
       {
          dfs(v, visited, graph);
       }
    }

    double endTime = omp_get_wtime(); // End timer

    std::cout << "Number of cores used: " << numCores << std::endl;
    std::cout << "Time taken: " << endTime - startTime << " seconds" << std::endl;
    std::cout << "------------------------" << std::endl;

    return;
}


//  ENTRY POINT OF MAIN FUNCTION
int main(void)
{
    // Generate a random graph with 10,000 vertices and 50,000 edges
    int numVertices = 10000;
    int numEdges = 50000;

    std::vector< std::vector<int> > graph(numVertices);
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

    // Loop over different number of cores and execute parallel DFS
    for (int i = 0; i < sizeof(numCoresArr) / sizeof(numCoresArr[0]); i++)
    {
        int numCores = numCoresArr[i];
        std::cout << "Running parallel DFS with " << numCores << " core(s)..." << std::endl;
        parallelDFS(graph, numCores);
    } 

    return 0;
}
