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
        build(id*2, l, mid);
        build(id*2+1, mid+1, r);
        st[id] = max(st[id*2], st[id*2+1]);
    }

    ll get(int id, int l, int r, int u, int v){
        if (u > r || v < l) return 0;
        if (u <= l && r <= v) return st[id];
        int mid = (l + r) / 2;
        return max(get(id*2, l, mid, u, v), get(id*2+1, mid + 1, r, u, v));
    }

    void update(int id, int l, int r, int pos, ll val) {
        if (l == r) {
            st[id] = val;
            a[pos] = val;
            return;
        }

        int mid = (l + r) / 2;
        if (pos <= mid) update(id*2, l, mid, pos, val);
        else update(id*2+1, mid + 1, r, pos, val); 
        st[id] = max(st[2*id], st[2*id+1]);
    }
};

int main() {
    int n, k;
    cin >> n >> k;
    vector<ll> d(n + 1);

    SegTree tree(n);

    for (int i = 1; i <= n; i++) {
        cin >> d[i];
        tree.a[i] = d[i];
    }

    tree.build(1, 1, n);
    
    vector<ll> prefix_sum(n+1);
    for (int i = 1; i <= n; i++) prefix_sum[i] = prefix_sum[i-1] + d[i];

    int ans = 0;
    for (int i = k; i <= n; i++) {
        ll s = prefix_sum[i] - prefix_sum[i - k];
        ll max_d = tree.get(1, 1, n, i - k + 1, i);
        if (s > 2 * max_d) ans++;
    }

    cout << ans << endl;

    return 0;
}