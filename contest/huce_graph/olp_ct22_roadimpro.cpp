#include <bits/stdc++.h>

using namespace std;

int n, m, q;
const int N = 2001;
vector<pair<int, int>> g[N];
const int INF = 1e9;
vector<vector<int>> dis(N, vector<int>(N, INF));
vector<vector<int>> cost(N + 1, vector<int> (N + 1));

void dijkstra(int s, vector<int> &dist) {
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > q;

    dist[s] = 0;
    q.push({0, s});

    while(!q.empty()) {
        auto top = q.top(); q.pop();
        int curDis = top.first;
        int u = top.second;

        if (curDis != dist[u]) continue;

        for (auto &e : g[u]) {
            int v = e.first;
            int w = e.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                q.push({dist[v], v});
            }
        }

    }

}

void floydWarshall() {
    for (int k = 1; k <= n; k++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                dis[u][v] = min(dis[u][k] + dis[k][v], dis[u][v]);
            }
        }
    }
}


int main() {
    cin >> n >> m >> q;

    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        g[u].push_back({v, c});
        dis[u][v] = c;
    }

    floydWarshall();

    // vector<int> dist(n + 1, INF);
    // dijkstra(1, dist);

    // for (int i = 1; i <= n; i++) {
    //     cout << dist[i] << " ";
    // }
    // cout << endl;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j ++) {
            // cout << dis[i][j] << " ";
            if (i == j) dis[i][j] = 0;
        }
        // cout << endl;
    }

    while (q--) {
        int end, t;
        cin >> end >> t;
        // vector<int> dist_e(n + 1, INF);
        // dijkstra(e, dist_e);
        int ans = dis[1][end];
        for (int u = 1; u <= n; u++) {
            for (auto &e : g[u]) {
                int v = e.first;
                int c = e.second;
                // cout << u << " " << v << " " << dis[1][u] << " " << dis[v][end] << " " << dis[1][u] + dis[v][end] + t << " " << ans << " " << endl;
                // cout << ans << endl;
                ans = min(dis[1][u] + dis[v][end] + t, ans);
                
            }
        }
        cout << ans << endl;
    }

    return 0;
}