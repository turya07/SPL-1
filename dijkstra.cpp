#include <iostream>
#include <vector>

#define INT short int
#define INF 32767

using namespace std;
int main()
{
    short int n, m;
    cout << "Enter the number of nodes: ";
    cin >> n;
    vector<vector<INT>> graph;
    graph.resize(n, vector<INT>(n));

    cout << "Enter the number of edges: ";
    cin >> m;

    cout << "Enter the edge (u, v) and weight: " << endl;
    for (INT i = 0; i < m; i++)
    {
        INT u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w;
    }

    for (INT i = 0; i < n; i++)
    {
        cout << (i) << ": ";
        for (INT j = 0; j < n; j++)
        {
            if (graph[i][j] > 0)
            {
                cout << (j) << "(" << graph[i][j] << ") ";
            }
        }
        cout << endl;
    }

    vector<INT> dist(n, INF);
    vector<INT> parent(n, -1);
    vector<bool> visited(n, false);

    dist[0] = 0;
    for (INT i = 0; i < n; i++)
    {
        INT min_dist = INF;
        INT min_index = -1;
        for (INT j = 0; j < n; j++)
        {
            if (!visited[j] && dist[j] < min_dist)
            {
                min_dist = dist[j];
                min_index = j;
            }
        }

        visited[min_index] = true;

        for (INT j = 0; j < n; j++)
        {
            if (!visited[j] && graph[min_index][j] > 0 && dist[j] > dist[min_index] + graph[min_index][j])
            {
                dist[j] = dist[min_index] + graph[min_index][j];
                parent[j] = min_index;
            }
        }
    }

    // Print the shortest path
    for (INT i = 0; i < n; i++)
    {
        cout << "Shortest path from 1 to " << i + 1 << " is: ";
        INT j = i;
        while (j != -1)
        {
            cout << j + 1 << " ";
            j = parent[j];
        }
        cout << "with cost: " << dist[i] << endl;
    }
    return 0;
}