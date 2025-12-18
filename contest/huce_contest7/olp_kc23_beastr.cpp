#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    int n;
    string a;
    vector<vector<int>> st;

    SegTree (int _n) {
        n = _n;
        st.resize(n * 4 + 5);
        for (auto &e : st) {
            e.assign(26, 0);
        }
    }

    void build(int id, int l, int r) {
        if (l == r) {
            st[id][a[l] - 'a']++;
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        for (int i = 0; i < 26; i++) {
            st[id][i] = st[id * 2][i] + st[id * 2 + 1][i];
        }
    }

    vector<int> get(int id, int l, int r, int u, int v) {
        if (v < l || u > r) {
            vector<int> s(26, 0);
            return s;
        }
        if (u <= l && r <= v) return st[id];

        int mid = (l + r) / 2;
        vector<int> ans(26, 0);
        vector<int> left, right;
        left = get(id * 2 , l, mid, u, v);
        right = get(id * 2 + 1, mid + 1, r, u, v);
        for (int i = 0; i < 26; i++) {
            ans[i] = left[i] + right[i];
        }
        return ans;
    }
};

int main() {
    int n, Q;
    cin >> n >> Q;
    string S; cin >> S;
    // cout << S.substr(2, 3);
    SegTree tree(n);
    tree.a = '#' + S;
    tree.build(1, 1, n);

    while(Q--) {
        int l, r; 
        cin >> l >> r;
        vector<int> T = tree.get(1, 1, n, l + 1, r + 1);
        int odd = 0;
        for (auto &t : T) if (t % 2) odd++;
        cout << (odd % 2 ? (odd - 1) / 2 : odd / 2) << endl;
    }


    return 0;
}