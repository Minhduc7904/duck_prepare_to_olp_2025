# CÂY KHUNG NHỎ NHẤT (MST)

## Kruskal Algorithm

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Edge {
    int u, v, c;
    Edge(int _u, int _v, int _c): u(_u), v(_v), c(_c) {};
};

int n, m, maxWeight = 0;
vector<Edge> edges;

struct DSU {
    vector<int> parent, sz;

    DSU (int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;        
    }

    int findset(int v) {
        if (v == parent[v]) return v;
        return parent[v] = findset(parent[v]);
    }

    bool union_sets(int u, int v) {
        int a = findset(u);
        int b = findset(v);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
            return true;
        }
        return false;
    }
};

bool sort_cost(Edge &x, Edge &y) {
    return x.c < y.c;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        Edge edge(u, v, c);
        edges.push_back(edge);
    }
    DSU dsu(n);
    sort(edges.begin(), edges.end(), sort_cost);

    for (auto e : edges) {
        if (!dsu.union_sets(e.u, e.v)) continue;

        maxWeight = max(e.c, maxWeight);
    }

    cout << maxWeight << endl;
}
```

## Prim Algorithm

```cpp
#include <bits/stdc++.h>

using namespace std;
#define fi first
#define se second
typedef long long ll;
const int N = 1000, M = 10000;
vector<pair<ll, ll>> G[N + 1];
int n, m;
const ll INF = 1e18;
vector<ll> dis(N + 1, INF);

ll prim(int s) {
    ll ret = 0;
    priority_queue<
    pair<ll, ll>,
    vector<pair<ll, ll>>,
    greater<pair<ll, ll>>
    > q;

    dis[s] = 0;
    q.push({0, s});

    while(!q.empty()) {
        auto top = q.top(); q.pop();
        int u = top.se;
        int curDis = top.fi;

        if (curDis != dis[u]) continue;
        
        ret = max(dis[u], ret);
        dis[u] = -INF;

        for (auto &e : G[u]) {
            ll v = e.fi;
            ll w = e.se;

            if (dis[v] > w) {
                dis[v] = w;
                q.push({dis[v], v});
            }
        }
    }
    return ret;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        ll u, v; cin >> u >> v;
        ll t;
        cin >> t;
        G[u].push_back({v, t});
        G[v].push_back({u, t});
    }

    cout << prim(1) << endl;

    return 0;
}
```

## Prim với distance array

```cpp
long long dist[MAXN];

long long primSimple(int start, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        inMST[i] = false;
    }
    
    dist[start] = 0;
    long long mstWeight = 0;
    
    for (int i = 0; i < n; i++) {
        int u = -1;
        
        // Tìm đỉnh chưa trong MST có khoảng cách nhỏ nhất
        for (int v = 1; v <= n; v++) {
            if (!inMST[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }
        
        if (dist[u] == INF) break;  // Đồ thị không liên thông
        
        inMST[u] = true;
        mstWeight += dist[u];
        
        // Cập nhật khoảng cách
        for (auto [v, w] : adj[u]) {
            if (!inMST[v] && w < dist[v]) {
                dist[v] = w;
            }
        }
    }
    
    return mstWeight;
}
```

## Kiểm tra MST duy nhất

```cpp
bool hasUniqueMST(vector<Edge>& edges, int n) {
    sort(edges.begin(), edges.end());
    makeSet(n);
    
    map<long long, int> weightCount;
    long long mstWeight = 0;
    int edgeCount = 0;
    
    // Tìm MST và đếm cạnh cùng trọng số
    for (auto e : edges) {
        if (unionSet(e.u, e.v)) {
            mstWeight += e.w;
            weightCount[e.w]++;
            edgeCount++;
            
            if (edgeCount == n - 1) break;
        }
    }
    
    // Kiểm tra xem có cạnh nào khác cùng trọng số có thể thay thế không
    makeSet(n);
    for (auto e : edges) {
        if (weightCount[e.w] > 1) {
            if (unionSet(e.u, e.v)) {
                return false;  // MST không duy nhất
            }
        }
    }
    
    return true;
}
```

## MST với cạnh bắt buộc/cấm

```cpp
long long mstWithConstraints(vector<Edge>& edges, 
                             vector<int>& required,
                             vector<int>& forbidden,
                             int n) {
    makeSet(n);
    long long weight = 0;
    int count = 0;
    
    // Thêm các cạnh bắt buộc
    for (int i : required) {
        auto e = edges[i];
        if (unionSet(e.u, e.v)) {
            weight += e.w;
            count++;
        } else {
            return -1;  // Không thể tạo MST
        }
    }
    
    // Đánh dấu cạnh cấm
    set<int> forbiddenSet(forbidden.begin(), forbidden.end());
    
    // Chạy Kruskal bình thường với các cạnh còn lại
    sort(edges.begin(), edges.end());
    
    for (int i = 0; i < edges.size(); i++) {
        if (forbiddenSet.count(i)) continue;
        if (find(required.begin(), required.end(), i) != required.end()) continue;
        
        auto e = edges[i];
        if (unionSet(e.u, e.v)) {
            weight += e.w;
            count++;
            
            if (count == n - 1) break;
        }
    }
    
    return count == n - 1 ? weight : -1;
}
```

## Cây khung lớn nhất (Maximum Spanning Tree)

```cpp
pair<long long, vector<Edge>> maxSpanningTree(vector<Edge>& edges, int n) {
    // Sắp xếp giảm dần
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w > b.w;
    });
    
    makeSet(n);
    
    long long mstWeight = 0;
    vector<Edge> mstEdges;
    int edgeCount = 0;
    
    for (auto e : edges) {
        if (unionSet(e.u, e.v)) {
            mstWeight += e.w;
            mstEdges.push_back(e);
            edgeCount++;
            
            if (edgeCount == n - 1) break;
        }
    }
    
    return {mstWeight, mstEdges};
}
```

## Second-best MST (MST thứ hai)

```cpp
long long secondBestMST(vector<Edge>& allEdges, int n) {
    // Tìm MST đầu tiên
    auto [mstWeight, mstEdges] = kruskal(allEdges, n);
    
    long long secondBest = INF;
    
    // Thử xóa từng cạnh trong MST và thêm cạnh khác
    for (auto removedEdge : mstEdges) {
        makeSet(n);
        long long weight = 0;
        int count = 0;
        
        for (auto e : allEdges) {
            if (e.u == removedEdge.u && e.v == removedEdge.v && e.w == removedEdge.w) {
                continue;  // Bỏ qua cạnh này
            }
            
            if (unionSet(e.u, e.v)) {
                weight += e.w;
                count++;
                
                if (count == n - 1) break;
            }
        }
        
        if (count == n - 1) {
            secondBest = min(secondBest, weight);
        }
    }
    
    return secondBest;
}
```

## Độ phức tạp
- **Kruskal**: O(E log E)
- **Prim với priority queue**: O((V + E) log V)
- **Prim simple**: O(V²)
