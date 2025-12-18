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