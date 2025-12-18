# DIJKSTRA & SHORTEST PATH

## Dijkstra cơ bản

```cpp
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
```

## Floyd-Warshall

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int N = 101;
vector<vector<ll>> dist(N + 1, vector<ll>(N + 1, INF)); 
vector<vector<ll>> adj(N + 1, vector<ll>(N + 1));
int n, m;

void floydWarshall() {
    for (int k = 1; k <= n; k++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v]);
            }
        }
    }
}

int main() {
    int M;
    cin >> n >> M;

    vector<int> a(M);
    for (int i = 0; i < M; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> adj[i][j];
        }
    }


    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (u == v) dist[u][v] = 0;
        }
    }    

    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            dist[u][v] = min(dist[u][v], adj[u][v]);
        }
    }   

    floydWarshall();

    int result = dist[1][a[0]];

    for (int i = 1; i < M; i++) {
        result += dist[a[i-1]][a[i]];
    }

    cout << result;
    return 0;
}
```

## Độ phức tạp
- **Dijkstra**: O((V + E) log V)
- **Floyd-Warshall**: O(V³)
- **Bellman-Ford**: O(VE)
- **SPFA**: O(VE) worst case, thường nhanh hơn
