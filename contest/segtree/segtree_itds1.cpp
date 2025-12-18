#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    int n;
    vector<ll> a;
    vector<multiset<ll>> st;

    SegTree(int _n) {
        n = _n;
        st.assign(n * 4 + 1, {});
        a.assign(n + 1, 0);
    }

    void build(int id, int l, int r, int pos, ll val) {
        st[id].insert(val);
        if (l == r) return;
        int mid = (l + r) / 2;
        if (pos <= mid) build(id * 2, l, mid, pos, val);
        else build(id * 2 + 1, mid + 1, r, pos, val);
    }

    void update(int id, int l, int r, int pos, ll oldval, ll newval) {
        auto it = st[id].find(oldval);
        if (it != st[id].end()) st[id].erase(it);
        st[id].insert(newval);
        if (l == r) return;
        int mid = (l + r) / 2;
        if (pos <= mid) update(id * 2, l, mid, pos, oldval, newval);
        else update(id * 2 + 1, mid + 1, r, pos, oldval, newval);
    }

    ll get(int id, int l, int r, int u, int v, ll k) {
        if (u > r || v < l) return LLONG_MAX;
        if (u <= l && r <= v) {
            auto it = st[id].lower_bound(k);
            if (it == st[id].end()) return LLONG_MAX;
            return *it;
        }
        int mid = (l + r) / 2;
        return min(
            get(id * 2, l, mid, u, v, k),
            get(id * 2 + 1, mid + 1, r, u, v, k)
        );
    }

};

int main() {
    int n, m;
    cin >> n >> m;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SegTree tree(n);
    for (int i = 1; i <= n; i++) {
        tree.build(1, 1, n, i, a[i]);
    }

    while(m--) {
        int t;
        cin >> t; 
        if (t == 1) {
            int i, v; cin >> i >> v;
            tree.update(1, 1, n, i, a[i], v);
            a[i] = v;
        } else {
            int L, R; ll K;
            cin >> L >> R >> K;
            ll ans = tree.get(1, 1, n, L, R, K);
            cout << (ans == LLONG_MAX ? -1 : ans) << endl;
        }
    }

    return 0;
}