#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
const int N = 2e5;
vector<ll> h(N + 1);



int main() {
    int n, t;
    cin >> n >> t;

    for (int i = 1; i <= n; i++) cin >> h[i];
    vector<ll> g[n + 1];

    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[v].push_back(u);
        g[u].push_back(v);
    }

    




}