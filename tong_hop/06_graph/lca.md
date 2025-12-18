# LCA (LOWEST COMMON ANCESTOR)

## LCA với Binary Lifting

```cpp
const int MAXN = 1e5 + 5;
const int LOG = 20;
int up[MAXN][LOG];  // up[u][i] = tổ tiên 2^i của u
int depth[MAXN];
vector<int> adj[MAXN];

void dfs(int u, int parent) {
    up[u][0] = parent;
    
    for (int i = 1; i < LOG; i++) {
        up[u][i] = up[up[u][i-1]][i-1];
    }
    
    for (int v : adj[u]) {
        if (v != parent) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    
    // Đưa u lên cùng level với v
    int diff = depth[u] - depth[v];
    for (int i = 0; i < LOG; i++) {
        if ((diff >> i) & 1) {
            u = up[u][i];
        }
    }
    
    if (u == v) return u;
    
    // Binary search để tìm LCA
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    
    return up[u][0];
}

int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}
```

## LCA với Sparse Table (RMQ)

```cpp
const int MAXN = 1e5 + 5;
const int LOG = 20;

int euler[2 * MAXN];   // Euler tour
int first[MAXN];       // Vị trí đầu tiên trong euler tour
int height[2 * MAXN];  // Độ sâu tại mỗi vị trí
int idx = 0;

int st[2 * MAXN][LOG];
int logTable[2 * MAXN];

void eulerTour(int u, int parent, int h) {
    first[u] = idx;
    euler[idx] = u;
    height[idx] = h;
    idx++;
    
    for (int v : adj[u]) {
        if (v != parent) {
            eulerTour(v, u, h + 1);
            euler[idx] = u;
            height[idx] = h;
            idx++;
        }
    }
}

void buildSparseTable() {
    // Tính log trước
    logTable[1] = 0;
    for (int i = 2; i < 2 * MAXN; i++) {
        logTable[i] = logTable[i / 2] + 1;
    }
    
    // Build sparse table
    for (int i = 0; i < idx; i++) {
        st[i][0] = i;
    }
    
    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i + (1 << j) <= idx; i++) {
            int left = st[i][j-1];
            int right = st[i + (1 << (j-1))][j-1];
            st[i][j] = (height[left] < height[right]) ? left : right;
        }
    }
}

int queryRMQ(int l, int r) {
    int len = r - l + 1;
    int k = logTable[len];
    int left = st[l][k];
    int right = st[r - (1 << k) + 1][k];
    return (height[left] < height[right]) ? left : right;
}

int lca(int u, int v) {
    int left = first[u];
    int right = first[v];
    if (left > right) swap(left, right);
    
    int pos = queryRMQ(left, right);
    return euler[pos];
}
```

## K-th ancestor

```cpp
int kthAncestor(int u, int k) {
    for (int i = 0; i < LOG; i++) {
        if ((k >> i) & 1) {
            u = up[u][i];
        }
    }
    return u;
}
```

## Khoảng cách giữa hai đỉnh

```cpp
int distance(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}
```

## Đỉnh trên đường đi

```cpp
bool isOnPath(int a, int b, int c) {
    // Kiểm tra c có nằm trên đường đi a-b không
    return lca(a, c) == c && lca(c, b) == c;
}

int nodeOnPath(int u, int v, int k) {
    // Tìm đỉnh thứ k trên đường đi u -> v
    int l = lca(u, v);
    int distU = depth[u] - depth[l];
    int distV = depth[v] - depth[l];
    
    if (k <= distU) {
        return kthAncestor(u, k);
    } else {
        k = distU + distV - k;
        return kthAncestor(v, k);
    }
}
```

## LCA của nhiều đỉnh

```cpp
int lcaMultiple(vector<int>& nodes) {
    if (nodes.empty()) return -1;
    
    int result = nodes[0];
    for (int i = 1; i < nodes.size(); i++) {
        result = lca(result, nodes[i]);
    }
    return result;
}
```

## Subtree queries với LCA

```cpp
int timeIn[MAXN], timeOut[MAXN];
int timer = 0;

void dfsTime(int u, int parent) {
    timeIn[u] = ++timer;
    
    up[u][0] = parent;
    for (int i = 1; i < LOG; i++) {
        up[u][i] = up[up[u][i-1]][i-1];
    }
    
    for (int v : adj[u]) {
        if (v != parent) {
            depth[v] = depth[u] + 1;
            dfsTime(v, u);
        }
    }
    
    timeOut[u] = ++timer;
}

bool isAncestor(int u, int v) {
    return timeIn[u] <= timeIn[v] && timeOut[u] >= timeOut[v];
}
```

## Path queries với LCA

```cpp
long long pathValue[MAXN];

void updatePath(int u, int v, long long val) {
    int l = lca(u, v);
    
    // Update u -> l
    while (u != l) {
        pathValue[u] += val;
        u = up[u][0];
    }
    
    // Update v -> l
    while (v != l) {
        pathValue[v] += val;
        v = up[v][0];
    }
    
    pathValue[l] += val;
}

long long queryPath(int u, int v) {
    int l = lca(u, v);
    long long sum = 0;
    
    // Query u -> l
    while (u != l) {
        sum += pathValue[u];
        u = up[u][0];
    }
    
    // Query v -> l
    while (v != l) {
        sum += pathValue[v];
        v = up[v][0];
    }
    
    sum += pathValue[l];
    return sum;
}
```

## Preprocessing và độ phức tạp

```cpp
void preprocess(int root, int n) {
    depth[root] = 0;
    dfs(root, root);
}

// Độ phức tạp:
// - Preprocessing: O(n log n)
// - Query LCA: O(log n)
// - Kth ancestor: O(log n)
// - Distance: O(log n)
```

## Lưu ý
- up[u][0] là cha trực tiếp của u
- up[u][i] là tổ tiên thứ 2^i của u
- Cần khởi tạo up[root][0] = root
- LOG thường chọn = 20 (đủ cho 2^20 = 1,048,576 đỉnh)
