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
        st[id] = min(st[id * 2], st[id * 2 + 1]);
    }

    ll get(int id, int l, int r, int u, int v) {
        if (u > r || v < l) return 1e18;
        if (u <= l && r <= v) return st[id];
        int mid = (l + r) /2;
        return min(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
    }
};

int binarySearch(int a, vector<ll> &b) {
    int l = 0; int r = b.size() - 1; int ans = b.size();
    while (l <= r) {
        int mid = (l + r) / 2;
        if (b[mid] >= a) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    } 
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n, k;

    cin >> m >> n >> k;
    vector<ll> a(m + 1), b(n + 1);
    for (int i = 1; i <= m; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    sort(b.begin() + 1, b.end());

    // for (int i = 1; i <= n; i++) cout << b[i] << " ";
    // cout << endl;

    SegTree tree(m);

    for (int i = 1; i <= m; i++) {
        int idx = binarySearch(a[i], b);
        if (idx == n + 1) {
            tree.a[i] = abs(b[n] - a[i]);
        } else if (idx == 0 || idx == 1) {
            tree.a[i] = abs(b[1] - a[i]);
        } else {
            tree.a[i] = min(b[idx] - a[i], a[i] - b[idx - 1]); 
        }
        // cout << idx << " " << tree.a[i] << " ";
    }
    // cout << endl;

    tree.build(1, 1, m);

    while (k--) {
        int l, r;
        cin >> l >> r;
        cout << tree.get(1, 1, m, l, r) << endl;
    }

    return 0;
}