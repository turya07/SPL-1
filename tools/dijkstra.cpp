#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>
#include <stack>
#include <unordered_map>
using namespace std;

// Structure to represent a cell in the grid
struct Cell {
    int row, col;
    int dist;
    
    Cell(int r, int c, int d) : row(r), col(c), dist(d) {}
    
    // Comparison operator for priority queue
    bool operator>(const Cell& other) const {
        return dist > other.dist;
    }
};

// Function to check if a cell is valid (within grid bounds and not blocked)
bool isValid(int row, int col, int m, int n, const vector<vector<int>>& grid) {
    return row >= 0 && row < m && col >= 0 && col < n && grid[row][col] != -1;
}

// Function to perform Dijkstra's algorithm and print the path
void dijkstraPath(const vector<vector<int>>& grid, pair<int, int> src, pair<int, int> dest) {
    int m = grid.size();
    if (m == 0) return;
    int n = grid[0].size();
    
    // Directions for moving up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    // Priority queue for Dijkstra's algorithm
    priority_queue<Cell, vector<Cell>, greater<Cell>> pq;
    
    // Distance matrix
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    
    // Parent matrix to reconstruct path
    vector<vector<pair<int, int>>> parent(m, vector<pair<int, int>>(n, {-1, -1}));
    
    // Initialize source
    dist[src.first][src.second] = 0;
    pq.push(Cell(src.first, src.second, 0));
    
    while (!pq.empty()) {
        Cell curr = pq.top();
        pq.pop();
        
        // If we've reached the destination
        if (curr.row == dest.first && curr.col == dest.second) {
            break;
        }
        
        // If we found a better path already, skip
        if (curr.dist > dist[curr.row][curr.col]) {
            continue;
        }
        
        // Explore all 4  that is up, right, left, down directions
        for (int i = 0; i < 4; i++) {
            int newRow = curr.row + dr[i];
            int newCol = curr.col + dc[i];
            
            if (isValid(newRow, newCol, m, n, grid)) {
                int newDist = curr.dist + 1; // All edges have weight 1 in this problem
                
                if (newDist < dist[newRow][newCol]) {
                    dist[newRow][newCol] = newDist;
                    parent[newRow][newCol] = {curr.row, curr.col};
                    pq.push(Cell(newRow, newCol, newDist));
                }
            }
        }
    }
    
    // Check if destination is reachable
    if (dist[dest.first][dest.second] == INT_MAX) {
        cout << "No path exists from (" << src.first << "," << src.second 
             << ") to (" << dest.first << "," << dest.second << ")" << endl;
        return;
    }
    
    // Reconstruct the path from destination to source
    stack<pair<int, int>> path;
    pair<int, int> curr = dest;
    
    while (curr != make_pair(-1, -1)) {
        path.push(curr);
        curr = parent[curr.first][curr.second];
    }
    
    // Print the path in source to destination order
    bool first = true;
    while (!path.empty()) {
        pair<int, int> node = path.top();
        path.pop();
        
        if (!first) {
            cout << " -> ";
        }
        cout << "(" << node.first << "," << node.second << ")";
        first = false;
    }
    cout << endl;
}

int main() {
    int m,n;
    cin >> m >> n;
    vector<vector<int>> grid(m, vector<int>(n));

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin >> grid[i][j];
            cout << (grid[i][j] == -1 ? "X" : "O") << " ";
        }
        cout << endl;
    }
    pair<int, int> src = {0, 2};  // (i1, j1)
    pair<int, int> dest = {3, 4}; // (i2, j2)
    int i=2;
    while(i--){
        int x,y;
        cin >> x >> y;
        if(i==1) src = {x,y};
        else dest = {x,y};
    }
    
    cout << "Path from (" << src.first << "," << src.second << ") to (" 
         << dest.first << "," << dest.second << "):" << endl;
    dijkstraPath(grid, src, dest);
    
    return 0;
}