# QUY HOẠCH ĐỘNG TRÊN DAG

## Đường đi dài nhất trên DAG

```cpp
const int MAXN = 1e5 + 5;
vector<int> adj[MAXN];
int dp[MAXN];
bool visited[MAXN];

int longestPath(int u) {
    if (visited[u]) return dp[u];
    visited[u] = true;
    dp[u] = 0;
    
    for (int v : adj[u]) {
        dp[u] = max(dp[u], 1 + longestPath(v));
    }
    
    return dp[u];
}

int solve(int n) {
    int maxPath = 0;
    for (int i = 1; i <= n; i++) {
        maxPath = max(maxPath, longestPath(i));
    }
    return maxPath;
}
```

## Số đường đi từ nguồn đến đích

```cpp
const long long MOD = 1e9 + 7;
vector<int> adj[MAXN];
long long dp[MAXN];
bool visited[MAXN];

long long countPaths(int u, int target) {
    if (u == target) return 1;
    if (visited[u]) return dp[u];
    
    visited[u] = true;
    dp[u] = 0;
    
    for (int v : adj[u]) {
        dp[u] = (dp[u] + countPaths(v, target)) % MOD;
    }
    
    return dp[u];
}
```

## Đường đi có trọng số lớn nhất

```cpp
struct Edge {
    int v, w;
};

vector<Edge> adj[MAXN];
long long dp[MAXN];
bool visited[MAXN];

long long maxWeightPath(int u) {
    if (visited[u]) return dp[u];
    visited[u] = true;
    dp[u] = 0;
    
    for (auto [v, w] : adj[u]) {
        dp[u] = max(dp[u], w + maxWeightPath(v));
    }
    
    return dp[u];
}
```

## Sắp xếp tô-pô (Topological Sort) với DP

```cpp
vector<int> adj[MAXN];
int indegree[MAXN];
int dp[MAXN];

void topologicalDP(int n) {
    queue<int> q;
    
    // Tìm các đỉnh không có cạnh vào
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
            dp[i] = 0;
        }
    }
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            dp[v] = max(dp[v], dp[u] + 1);
            indegree[v]--;
            
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }
}
```

## Longest Increasing Path trong ma trận

```cpp
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
int dp[505][505];
int matrix[505][505];
int n, m;

int dfs(int x, int y) {
    if (dp[x][y] != -1) return dp[x][y];
    
    dp[x][y] = 1;
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && matrix[nx][ny] > matrix[x][y]) {
            dp[x][y] = max(dp[x][y], 1 + dfs(nx, ny));
        }
    }
    
    return dp[x][y];
}

int longestIncreasingPath() {
    memset(dp, -1, sizeof(dp));
    int maxPath = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            maxPath = max(maxPath, dfs(i, j));
        }
    }
    
    return maxPath;
}
```

## Đếm số cách đi với K bước

```cpp
const long long MOD = 1e9 + 7;
vector<int> adj[MAXN];
long long dp[MAXN][105];  // dp[u][k] = số cách đến u với k bước

long long countKSteps(int start, int n, int K) {
    memset(dp, 0, sizeof(dp));
    dp[start][0] = 1;
    
    for (int k = 0; k < K; k++) {
        for (int u = 1; u <= n; u++) {
            if (dp[u][k] == 0) continue;
            
            for (int v : adj[u]) {
                dp[v][k + 1] = (dp[v][k + 1] + dp[u][k]) % MOD;
            }
        }
    }
    
    long long total = 0;
    for (int u = 1; u <= n; u++) {
        total = (total + dp[u][K]) % MOD;
    }
    
    return total;
}
```

## Đường đi nhỏ nhất trên DAG

```cpp
const long long INF = 1e18;
vector<pair<int, long long>> adj[MAXN];  // {v, weight}
long long dp[MAXN];
bool visited[MAXN];

long long minPath(int u, int target) {
    if (u == target) return 0;
    if (visited[u]) return dp[u];
    
    visited[u] = true;
    dp[u] = INF;
    
    for (auto [v, w] : adj[u]) {
        dp[u] = min(dp[u], w + minPath(v, target));
    }
    
    return dp[u];
}
```

## Tìm đường đi trong lưới DAG

```cpp
int dp[1005][1005];
int grid[1005][1005];
int n, m;

int gridDAG(int x, int y) {
    if (x == n - 1 && y == m - 1) return grid[x][y];
    if (dp[x][y] != -1) return dp[x][y];
    
    dp[x][y] = grid[x][y];
    int maxNext = 0;
    
    // Chỉ đi xuống hoặc sang phải
    if (x + 1 < n) maxNext = max(maxNext, gridDAG(x + 1, y));
    if (y + 1 < m) maxNext = max(maxNext, gridDAG(x, y + 1));
    
    return dp[x][y] += maxNext;
}
```

## Kiểm tra có chu trình không (DFS)

```cpp
const int WHITE = 0, GRAY = 1, BLACK = 2;
int color[MAXN];

bool hasCycle(int u) {
    color[u] = GRAY;
    
    for (int v : adj[u]) {
        if (color[v] == GRAY) return true;  // Tìm thấy chu trình
        if (color[v] == WHITE && hasCycle(v)) return true;
    }
    
    color[u] = BLACK;
    return false;
}

bool isDAG(int n) {
    memset(color, WHITE, sizeof(color));
    
    for (int i = 1; i <= n; i++) {
        if (color[i] == WHITE) {
            if (hasCycle(i)) return false;
        }
    }
    
    return true;
}
```

## Lưu ý
- DAG = Directed Acyclic Graph (đồ thị có hướng không chu trình)
- Luôn có thể sắp xếp tô-pô
- DP trên DAG luôn chạy đúng vì không có chu trình
- Độ phức tạp: O(V + E)
