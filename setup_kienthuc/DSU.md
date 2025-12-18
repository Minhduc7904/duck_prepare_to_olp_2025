
# 🔥 **DSU Template Chuẩn Competitive**

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]); // path compression
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a, b); // union by size
            parent[b] = a;
            sz[a] += sz[b];
        }
    }

    bool same_set(int a, int b) {
        return find_set(a) == find_set(b);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q; 
    
    DSU dsu(n);

    while (q--) {
        int type, u, v;
        cin >> type >> u >> v;

        if (type == 1) {
            dsu.union_sets(u, v);  // nối u và v
        } 
        else if (type == 2) {
            cout << (dsu.same_set(u, v) ? "YES\n" : "NO\n");
        }
    }

    return 0;
}
```

---

# 🎯 **Cách dùng**

* `DSU dsu(n)` → tạo DSU cho n đỉnh.
* `dsu.union_sets(a, b)` → nối hai đỉnh.
* `dsu.same_set(a, b)` → kiểm tra hai đỉnh chung tập.
* `find_set(x)` → trả về gốc.
---
* union by rank
* DSU rollback
* DSU có lưu extra info (sum, min, max size mỗi component)
* DSU 1-based hay 0-based
* template cho Kruskal
