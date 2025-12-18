#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct SegTree {
    int n;
    vector<ll> st, a, lazy;

    SegTree(int _n) {
        n = _n;
        st.assign(n * 4 + 5, 0);
        a.assign(n + 1, 0);
        lazy.assign(n * 4 + 5, 0);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            st[id] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id] = max(st[2 * id], st[2 * id + 1]);
    }

    void push(int id) {
        if (lazy[id] != 0) {
            st[id * 2] += lazy[id];
            st[id * 2 + 1] += lazy[id];
            lazy[id * 2] += lazy[id];
            lazy[id * 2 + 1] += lazy[id];
            lazy[id] = 0;
        }
    }

    void update(int id, int l, int r, int x, int y, ll val) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            st[id] += val;
            lazy[id] += val;
            return;
        }
        push(id);
        int mid = (l + r) / 2;
        update(id * 2, l, mid, x, y, val);
        update(id * 2 + 1, mid + 1, r, x, y, val);
        st[id] = max(st[id * 2], st[id * 2 + 1]);
    }

    ll get(int id, int l, int r, int u, int v) {
        if (u > r || v < l) return LLONG_MIN;
        if (u <= l && r <= v) return st[id];
        push(id);
        int mid = (l + r) / 2;
        return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    
    SegTree tree(n);

    for (int i = 1; i <= n; i++) {
        cin >> tree.a[i];
    }

    tree.build(1, 1, n);
    int q; cin >> q;
    while(q--) {
        int t; cin >> t;

        if (t == 1) {
            int x, y;
            ll val;
            cin >> x >> y >> val;
            tree.update(1, 1, n, x, y, val);
        } else {
            int l, r;
            cin >> l >> r;
            cout << tree.get(1, 1, n, l, r) << endl;
        }
    }

    return 0;
}