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

        st[id] = min(st[id*2], st[id*2 + 1]);
    }

    void update(int id, int l, int r, int pos, ll val) {
        if (l == r) {
            st[id] = val;
            a[pos] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) update(id*2, l, mid, pos, val);
        else update(id*2+1, mid+1, r, pos, val);
        st[id] = min(st[id*2], st[id*2 + 1]);
    }

    ll get(int id, int l, int r, int u, int v) {
        if (u > r || v < l) return 1e18;
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        return min(get(id*2, l, mid, u, v), get(id*2+1, mid + 1, r, u, v));
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<ll> prefix_sum(2 * n + 1);

    for (int i = 1; i <= n; i++) prefix_sum[i] = prefix_sum[i-1] + a[i];

    for (int i = n + 1; i <= 2 * n; i++) prefix_sum[i] = prefix_sum[i-1] + a[i - n];

    SegTree tree(2 * n);

    for (int i = 1; i <= 2*n; i++) tree.a[i] = prefix_sum[i];

    tree.build(1, 1, 2 * n);

    int counts = 0;
    for (int j = 1; j <= n; j++) {
        if (tree.get(1, 1, 2 * n, j, j + n - 1) - prefix_sum[j-1] > 0) counts++;
    }

    cout << counts << endl;
    return 0;
}