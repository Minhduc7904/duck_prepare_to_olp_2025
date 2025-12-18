#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 2*1e5;

struct SegTree {
    int n;
    vector<ll> st, a;

    SegTree(int _n){
        n = _n;
        st.assign(n * 4 + 1, 0);
        a.resize(n + 1);
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    // vector<ll> a(n + 1);
    SegTree tree(n);

    for (int i = 1; i <= n; i++) {
        cin >> tree.a[i];
    }

    tree.build(1, 1, n);

    vector<vector<bool>> S(N+1, vector<bool> (10, 0));

    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= 9; k++){
            if (i % k == 0) S[i][k] = true;
        }

        string s_i = to_string(i);
        for (char c : s_i){
            S[i][c - '0'] = true;
        }
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int i, c; cin >> i >> c;
            tree.update(1, 1, n, i, c);
        } else {
            int L, R, k; cin >> L >> R >> k;
            ll ans = tree.get(1, 1, n, L, R);
            if (k == 1) {
                ans *= 2;
            }
            else {
                for (int i = L; i <= R; i++) {
                    if (S[i][k]) {
                        ans += tree.a[i];
                        // cout << i << "-" << tree.a[i];
                    }
                }
            }
            // cout << endl;
            cout << ans << endl;
        }
    }



    return 0;
}