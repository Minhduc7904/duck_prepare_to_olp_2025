# BFS & DFS

## BFS (Breadth-First Search)

```cpp
const int MAXN = 1e5 + 5;
vector<int> adj[MAXN];
int dist[MAXN];
bool visited[MAXN];

void BFS(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    dist[start] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}
```

## DFS (Depth-First Search)

```cpp
vector<int> adj[MAXN];
bool visited[MAXN];

void DFS(int u) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            DFS(v);
        }
    }
}
```

## DFS với thời gian vào/ra

```cpp
int timeIn[MAXN], timeOut[MAXN];
int timer = 0;

void DFS(int u, int parent = -1) {
    visited[u] = true;
    timeIn[u] = ++timer;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            DFS(v, u);
        }
    }
    
    timeOut[u] = ++timer;
}

bool isAncestor(int u, int v) {
    return timeIn[u] <= timeIn[v] && timeOut[u] >= timeOut[v];
}
```

## Tìm đường đi BFS

```cpp
vector<int> parent[MAXN];

vector<int> findPath(int start, int target) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    parent[start] = -1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        if (u == target) break;
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    
    // Reconstruct path
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    
    return path;
}
```

## 0-1 BFS (Deque)

```cpp
vector<pair<int, int>> adj[MAXN];  // {node, weight (0 or 1)}
int dist[MAXN];

void bfs01(int start) {
    deque<int> dq;
    fill(dist, dist + MAXN, INT_MAX);
    
    dist[start] = 0;
    dq.push_front(start);
    
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                
                if (w == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }
}
```

## Multi-source BFS

```cpp
void multiSourceBFS(vector<int>& sources) {
    queue<int> q;
    
    for (int src : sources) {
        q.push(src);
        visited[src] = true;
        dist[src] = 0;
    }
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}
```

## BFS trên lưới

```cpp
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
int dist[1005][1005];
bool visited[1005][1005];

void gridBFS(int sx, int sy, int n, int m) {
    queue<pair<int, int>> q;
    q.push({sx, sy});
    visited[sx][sy] = true;
    dist[sx][sy] = 0;
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                visited[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}
```

## Tìm thành phần liên thông

```cpp
int componentId[MAXN];
int numComponents = 0;

void DFS(int u, int id) {
    componentId[u] = id;
    
    for (int v : adj[u]) {
        if (componentId[v] == 0) {
            DFS(v, id);
        }
    }
}

void findComponents(int n) {
    for (int i = 1; i <= n; i++) {
        if (componentId[i] == 0) {
            numComponents++;
            DFS(i, numComponents);
        }
    }
}
```

## Kiểm tra đồ thị hai phía (Bipartite)

```cpp
int color[MAXN];

bool isBipartite(int u, int c) {
    color[u] = c;
    
    for (int v : adj[u]) {
        if (color[v] == -1) {
            if (!isBipartite(v, 1 - c)) {
                return false;
            }
        } else if (color[v] == c) {
            return false;
        }
    }
    
    return true;
}

bool checkBipartite(int n) {
    memset(color, -1, sizeof(color));
    
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            if (!isBipartite(i, 0)) {
                return false;
            }
        }
    }
    
    return true;
}
```

## Tìm chu trình với DFS

```cpp
int parent[MAXN];
bool hasCycle = false;

void DFS(int u, int p) {
    visited[u] = true;
    parent[u] = p;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            DFS(v, u);
        } else if (v != p) {
            hasCycle = true;
            // In chu trình
            int curr = u;
            while (curr != v) {
                cout << curr << " ";
                curr = parent[curr];
            }
            cout << v << "\n";
        }
    }
}
```

## Độ phức tạp
- **BFS/DFS**: O(V + E)
- **0-1 BFS**: O(V + E)
- **Multi-source BFS**: O(V + E)
