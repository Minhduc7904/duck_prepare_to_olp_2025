#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

const int N = 5000;
const int M = 20000;
int n, m;
ll dist[N + 1];
ll ways[N + 1];
vector<pair<int, int>> G[N + 1];
const ll INF = 1e18;

void dijkstra(int s) {
    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
        ways[i] = 0;
    }

    priority_queue<
    pair<ll, ll>,
    vector<pair<ll, ll>>,
    greater<pair<ll, ll>>
    > q;

    q.push({0, s});
    dist[s] = 0;
    ways[s] = 1;

    while (!q.empty()) {
        auto top = q.top(); q.pop();
        int u = top.se;
        int curDis = top.fi;

        if (curDis != dist[u]) continue;

        for (auto &e : G[u]) {
            int v = e.fi;
            int c = e.se;
            if (dist[v] > dist[u] + c) {
                dist[v] = dist[u] + c;
                ways[v] = ways[u];
                q.push({dist[v], v});
            }

            else if (dist[v] == dist[u] + c) {
                ways[v] += ways[u];
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int k; cin >> k;
        int u, v, l; cin >> u >> v >> l;
        G[u].push_back({v, l});
        if (k == 2) G[v].push_back({u, l});
    }

    dijkstra(1);

    cout << dist[n] << " " << ways[n];


    return 0;
}