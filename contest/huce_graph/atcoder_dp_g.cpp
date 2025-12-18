#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAX_N = 1e5+1;
vector<vector<int>> adj(MAX_N + 1);
vector<int> dict(MAX_N + 1);
bool visited[MAX_N];

int dfs(int u) {
    if (visited[u]) return dict[u];
    visited[u] = true;
    int k = 0;
    for (int v: adj[u]) {
        k = max(k, dfs(v) + 1);
    }
    dict[u] = k;
    return dict[u];
}

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    int result = 0;
    for (int i = 1; i <= N; i++) {
        result = max(result, dfs(i));
    }
    cout << result << endl;

    return 0;
}