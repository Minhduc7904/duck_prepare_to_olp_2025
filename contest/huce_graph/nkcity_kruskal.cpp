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