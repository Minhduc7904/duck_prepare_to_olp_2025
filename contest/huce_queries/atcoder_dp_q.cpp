#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegTree {
    int n;
    vector<ll> st, a;

    SegTree (int _n) {
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
        if (u > r || v < l) return 0;
        if (u <= l && r <= v) return st[id];
        int mid = (l + r) / 2;
        return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
    }

};

int main() {
    int n;
    cin >> n;
    vector<int> H(n + 1);
    vector<ll> a(n + 1);

    for (int i = 1; i <= n; i++) cin >> H[i];
    for (int i = 1; i <= n; i++) cin >> a[i]; 

    SegTree tree(n);
    tree.build(1, 1, n);

    vector<ll> dp(n + 1);
    dp[H[1]] = a[1];
    tree.update(1, 1, n, H[1], dp[H[1]]);

    ll ans = dp[H[1]];

    for (int i = 2; i <= n; i++) {
        int h = H[i];
        int A = a[i];
        dp[h] = tree.get(1, 1, n, 1, h-1) + A;
        ans = max(ans, dp[h]);
        tree.update(1, 1, n, H[i], dp[h]);
    }
    cout << ans << endl;


    return 0;
}