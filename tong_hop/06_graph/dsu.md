# DSU (DISJOINT SET UNION) - UNION FIND

## DSU cơ bản

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct DSU {
    vector<int> parent, sz;
    
    DSU(int n) {
        parent.resize(n+1);
        sz.resize(n+1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int findset(int v) {
        if (v == parent[v]) return v;
        return parent[v] = findset(parent[v]);
    }

    void union_sets(int a, int b) {
        a = findset(a);
        b = findset(b);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
        }
    }

    bool same_set(int a, int b){
        return findset(a) == findset(b);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    DSU dsu(n);

    while(m--) {
        string t;
        int u, v;
        cin >> t >> u >> v;
        if (t == "union") {
            dsu.union_sets(u, v);
        } else if ( t == "get") {
            cout << (dsu.same_set(u, v) ? "YES" : "NO") << endl;
        }
    }

    return 0;
}
```

## DSU với kích thước tập hợp

```cpp
struct DSU {
    vector<ll> parent, sz, mn, mx;
    DSU (int n){
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        mn.resize(n + 1);
        mx.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            mx[i] = i;
            mn[i] = i;
        }
    }

    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_set(int u, int v) {
        int a = find_set(u);
        int b = find_set(v);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
            mx[a] = max(mx[a], mx[b]);
            mn[a] = min(mn[a], mn[b]); 
        }
    }
    bool same_set(int a, int b) {
        return find_set(a) == find_set(b);
    }
};
```

## Đếm số thành phần liên thông

```cpp
int countComponents(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (findSet(i) == i) {
            count++;
        }
    }
    return count;
}
```

## DSU với rollback (Undo)

```cpp
struct DSU {
    vector<int> parent, rank;
    stack<pair<int, int>> history;
    
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    
    int find(int u) {
        if (u != parent[u]) {
            return find(parent[u]);  // Không dùng path compression
        }
        return u;
    }
    
    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        
        if (u == v) return false;
        
        if (rank[u] < rank[v]) swap(u, v);
        
        history.push({v, parent[v]});
        parent[v] = u;
        
        if (rank[u] == rank[v]) {
            history.push({-u, rank[u]});
            rank[u]++;
        }
        
        return true;
    }
    
    void rollback() {
        if (history.empty()) return;
        
        auto [node, val] = history.top();
        history.pop();
        
        if (node < 0) {
            rank[-node] = val;
        } else {
            parent[node] = val;
        }
    }
};
```

## Kiểm tra chu trình trong đồ thị vô hướng

```cpp
bool hasCycle(vector<pair<int, int>>& edges, int n) {
    makeSet(n);
    
    for (auto [u, v] : edges) {
        if (findSet(u) == findSet(v)) {
            return true;  // Tìm thấy chu trình
        }
        unionSet(u, v);
    }
    
    return false;
}
```

## Đếm số cạnh cần thêm để liên thông

```cpp
int minEdgesToConnect(int n) {
    int components = countComponents(n);
    return components - 1;
}
```

## DSU với persistent (lưu lịch sử)

```cpp
struct PersistentDSU {
    vector<int> parent, rank;
    vector<vector<pair<int, int>>> versions;
    
    PersistentDSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
        versions.push_back({});
    }
    
    int find(int u, int version = -1) {
        if (version == -1) version = versions.size() - 1;
        
        if (u != parent[u]) {
            return find(parent[u], version);
        }
        return u;
    }
    
    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        
        if (u == v) {
            versions.push_back({});
            return;
        }
        
        vector<pair<int, int>> changes;
        
        if (rank[u] < rank[v]) swap(u, v);
        
        changes.push_back({v, parent[v]});
        parent[v] = u;
        
        if (rank[u] == rank[v]) {
            changes.push_back({-u, rank[u]});
            rank[u]++;
        }
        
        versions.push_back(changes);
    }
    
    void rollbackTo(int version) {
        while (versions.size() > version + 1) {
            for (auto [node, val] : versions.back()) {
                if (node < 0) {
                    rank[-node] = val;
                } else {
                    parent[node] = val;
                }
            }
            versions.pop_back();
        }
    }
};
```

## Ứng dụng: Kruskal MST

```cpp
struct Edge {
    int u, v, w;
    bool operator < (const Edge& other) const {
        return w < other.w;
    }
};

long long kruskal(vector<Edge>& edges, int n) {
    sort(edges.begin(), edges.end());
    makeSet(n);
    
    long long mstWeight = 0;
    int edgeCount = 0;
    
    for (auto [u, v, w] : edges) {
        if (unionSet(u, v)) {
            mstWeight += w;
            edgeCount++;
            if (edgeCount == n - 1) break;
        }
    }
    
    return mstWeight;
}
```

## Độ phức tạp
- **Find**: O(α(n)) ≈ O(1) với path compression
- **Union**: O(α(n)) ≈ O(1) với union by rank
- **α(n)** là hàm Ackermann nghịch đảo, rất nhỏ trong thực tế
