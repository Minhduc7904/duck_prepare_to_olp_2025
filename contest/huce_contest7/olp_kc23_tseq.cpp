#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int dis(int a, int b, int m) {
    if (b >= a) return b - a;
    else return b + m - a;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) cin >> b[i];

    ll ans = LLONG_MAX;
    for (int x = 0; x < m; x++) {
        ll s = 0;
        for (int i = 1; i < n; i++) {
            s += min(dis(b[i], b[i+1], m), dis(x, b[i+1], m) + 1);
        }
        ans = min(ans, s);
    }

    cout << ans << endl;

    return 0;
}