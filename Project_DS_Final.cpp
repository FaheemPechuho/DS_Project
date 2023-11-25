#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge
{
    int source;
    int destination;
    int weight;
    Edge(int s, int d, int w) : source(s), destination(d), weight(w) {}
};

void createGraph(vector<Edge> graph[], int V)
{
    for (int i = 0; i < V; i++)
    {
        graph[i] = vector<Edge>();
    }
    graph[0].push_back(Edge(0, 1, 2));
    graph[0].push_back(Edge(0, 2, 4));
    graph[1].push_back(Edge(1, 3, 7));
    graph[1].push_back(Edge(1, 2, 1));
    graph[2].push_back(Edge(2, 4, 3));
    graph[3].push_back(Edge(3, 5, 1));
    graph[4].push_back(Edge(4, 3, 2));
    graph[4].push_back(Edge(4, 5, 5));
}
void displayGraph(vector<Edge> graph[], int V)
{
    cout << "Adjacency List Representation:" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << "Vertex " << i << " --> ";
        for (Edge edge : graph[i])
        {
            cout << "(" << edge.destination << ", " << edge.weight << ") ";
        }
        cout << endl;
    }
}

struct Pair
{
    int node;
    int distance;
    Pair(int n, int d) : node(n), distance(d) {}
    bool operator<(const Pair &p2) const
    {
        if (distance > p2.distance)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

vector<int> dijkstra(vector<Edge> graph[], int source, int V)
{

    // Initialization of Priority Queue Starts Here
    priority_queue<Pair> priorqueue;
    vector<int> distance(V, 0);
    vector<bool> visited(V, false);

    // Priority Queue Compares two Pair and choose the one with shortest distance

    // Step 1: Initializng Every Node to infinity except the source node
    for (int i = 0; i < V; i++)
    {
        if (i != source)
        {
            distance[i] = INT_MAX;
        }
    }
    priorqueue.push(Pair(source, 0));
    // Initialization of Priority Queue Ends Here

    // Dijkstra algorithm similar to BFS
    while (!priorqueue.empty())
    {
        Pair curr = priorqueue.top(); // retrieve the pair with shortest distance
        priorqueue.pop();

        if (!visited[curr.node])
        {
            visited[curr.node] = true;

            // For Neighbor of That Node with shortest distance
            for (int i = 0; i < graph[curr.node].size(); i++) // graph[curr.node] give the list of neighbors
            {
                Edge edge = graph[curr.node].at(i);
                int u = edge.source;
                int v = edge.destination;
                if (distance[u] + edge.weight < distance[v]) // relaxation
                {
                    distance[v] = distance[u] + edge.weight;
                    priorqueue.push(Pair(v, distance[v]));
                }
            }
        }
    }
    return distance;
}
// void createGridFromGraph(vector<Edge> graph[], int V)
// {
//     vector<vector<int>> grid(V, vector<int>(V, INT_MAX));

//     // Initialize grid with INT_MAX indicating absence of edges
//     for (int i = 0; i < V; i++)
//     {
//         grid[i][i] = 0; // Set diagonal elements to 0 for self-edges
//         for (Edge edge : graph[i])
//         {
//             grid[edge.source][edge.destination] = edge.weight;
//         }
//     }

//     // Display the grid
//     cout << "Grid Representation:" << endl;
//     for (int i = 0; i < V; i++)
//     {
//         for (int j = 0; j < V; j++)
//         {
//             if (grid[i][j] == INT_MAX)
//             {
//                 cout << "X "; // Symbol representing absence of edge
//             }
//             else
//             {
//                 cout << grid[i][j] << " ";
//             }
//         }
//         cout << endl;
//     }
// }
void createGridFromGraph(vector<Edge> graph[], int V)
{
    vector<vector<int>> grid(V, vector<int>(V, INT_MAX)); // initializes a 2D vector called grid with V rows and V columns, with each cell initialized to INT_MAX

    for (int i = 0; i < V; i++)
    {
        vector<int> dist = dijkstra(graph, i, V);

        // Initializing the grid value with distance value in graph
        for (int j = 0; j < V; j++)
        {
            grid[i][j] = dist[j];
        }
    }

    cout << "Grid Representation:" << endl;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (grid[i][j] == INT_MAX)
            {
                cout << "X "; // X represent no edge therefore the distance would be infinicty
            }
            else
            {
                cout << grid[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main()
{
    const int sizeV = 6;
    vector<Edge> graph[sizeV];
    createGraph(graph, sizeV);
    displayGraph(graph, sizeV);
    cout << endl;
    createGridFromGraph(graph, sizeV);

    int source = 0;
    vector<int> dist = dijkstra(graph, source, sizeV);

    cout << "Shortest distances from source " << source << endl;
    for (int i = 0; i < sizeV; i++)
    {
        cout << dist[i] << " ";
    }
    cout << endl;

    return 0;
}
