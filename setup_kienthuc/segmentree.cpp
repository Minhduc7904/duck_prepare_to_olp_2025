#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct SegTree {
    int n;
    vector<ll> st, a;

    SegTree(int _n) {
        n = _n;
        st.assign(n * 4 + 5, 0);
        a.assign(n + 1, 0);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            st[id] = a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(id*2, l, mid);
        build(id*2+1, mid+1, r);
        st[id] = min(st[id*2], st[id*2+1]); 
    }

    ll get(int id, int l, int r, int u, int v) {
        if (r < u || v < l) return 1e18;
        if (u <= l && r <= v) return st[id];
        int mid = (l + r) / 2;
        return min(get(id*2, l, mid, u, v), get(id*2 + 1, mid + 1, r, u, v));
    }

    void update(int id, int l, int r, int pos, ll value) {
        if (l == r) {
            st[id] = value;
            a[pos] = value;
            return;
        } 
        int mid = (l + r) / 2;
        if (pos <= mid) update(id*2, l, mid, pos, value);
        else update(id*2+1, mid+1, r, pos, value);

        st[id] = min(st[id*2], st[id*2+1]);
    }

};