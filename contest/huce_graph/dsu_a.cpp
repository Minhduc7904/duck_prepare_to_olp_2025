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