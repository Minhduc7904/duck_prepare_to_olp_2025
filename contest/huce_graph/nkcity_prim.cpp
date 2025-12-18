#include <bits/stdc++.h>

using namespace std;
#define fi first
#define se second
typedef long long ll;
const int N = 1000, M = 10000;
vector<pair<ll, ll>> G[N + 1];
int n, m;
const ll INF = 1e18;
vector<ll> dis(N + 1, INF);

ll prim(int s) {
    ll ret = 0;
    priority_queue<
    pair<ll, ll>,
    vector<pair<ll, ll>>,
    greater<pair<ll, ll>>
    > q;

    dis[s] = 0;
    q.push({0, s});

    while(!q.empty()) {
        auto top = q.top(); q.pop();
        int u = top.se;
        int curDis = top.fi;

        if (curDis != dis[u]) continue;
        
        ret = max(dis[u], ret);
        dis[u] = -INF;

        for (auto &e : G[u]) {
            ll v = e.fi;
            ll w = e.se;

            if (dis[v] > w) {
                dis[v] = w;
                q.push({dis[v], v});
            }
        }
    }
    return ret;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        ll u, v; cin >> u >> v;
        ll t;
        cin >> t;
        G[u].push_back({v, t});
        G[v].push_back({u, t});
    }

    cout << prim(1) << endl;

    return 0;
}