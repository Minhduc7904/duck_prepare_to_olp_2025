#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<ll> prefix_sum(n + 1);

    for (int i = 1; i <= n; i++) {
        prefix_sum[i] += prefix_sum[i-1] + a[i];
    }

    while (q--) {
        int l;
        int r;
        cin >> l >> r;
        cout << prefix_sum[r] - prefix_sum[l-1] << endl;
    }

    return 0;
}