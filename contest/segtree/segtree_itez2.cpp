#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    int n;
    vector<ll> st, a;

    SegTree(int _n) {
        n = _n;
        st.assign(4 * n + 5, 0);
        a.assign(n + 1, 0);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            st[id] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id] = st[id * 2] + st[id * 2 + 1];
    }

    void update(int id, int l, int r, int pos, ll val) {
        if (l == r) {
            st[id] = val;
            a[pos] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) update(id * 2, l, mid, pos, val);
        else update(id * 2 + 1, mid + 1, r, pos, val);
        st[id] = st[id * 2] + st[id * 2 + 1];
    }

    ll get(int id, int l, int r, int u, int v) {
        if (u > r || v < l) return 0;
        if (u <= l && r <= v) return st[id];
        int mid = (l + r) / 2;
        return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
    }
};

int main() {
    int n, q; cin >> n >> q;
    SegTree tree(n);
    tree.build(1, 1, n);

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int x, y; cin >> x >> y;
            tree.update(1, 1, n, x, y);
        } else {
            int l, r; cin >> l >> r;
            cout << tree.get(1, 1, n, l, r) << endl;
        }
    }

    return 0;
}