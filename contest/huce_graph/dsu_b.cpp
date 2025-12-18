#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

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


int main() {
    int n, m; cin >> n >> m;
    DSU dsu(n);
    while (m--) {
        string t; cin >> t;
        if (t == "union") {
            int u, v; cin >> u >> v;
            dsu.union_set(u, v);
        } else {
            int u; cin >> u;
            int root = dsu.find_set(u);
            cout << dsu.mn[root] << " " << dsu.mx[root] << " " << dsu.sz[root] << endl;
        }
    }

    return 0;
}