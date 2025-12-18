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
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id] = max(st[id * 2], st[id * 2 + 1]); 
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
        st[id] = max(st[id * 2], st[id * 2 + 1]);
    }

    ll get(int id, int l, int r, int u, int v) {
        if (u > r || v < l) return LLONG_MIN;
        if (u <= l && r <= v) return st[id];
        int mid = (l + r) / 2;
        return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
    }
};

int main() {
    int n, k; cin >> n >> k;
    vector<ll> a(n + 1), dp(n + 1);

    SegTree tree(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    dp[1] = max(ll(0), a[1]);
    tree.build(1, 1, n);
    tree.update(1, 1, n, 1, dp[1]);


    ll ans = dp[1];
    for (int i = 2; i <= n; i++) {
        int back = max(1, i - k);
        ll pre_max = max((ll)0, tree.get(1, 1, n, back, i - 1));
        dp[i] = max((ll)0, pre_max + a[i]);
        
        tree.update(1, 1, n, i, dp[i]);
        ans = max(dp[i], ans);
    }

    cout << ans << endl;

    return 0;
}