#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
vector<vector<int>> adj(MAX_N); 
bool visited[MAX_N];
vector<vector<int>> dp(2, vector<int> (MAX_N));

int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
    return a;
}


void dfs(int u) {
    if (visited[u]) return;
    visited[u] = true;

    if (adj[u].size() == 1 && visited[adj[u][0]]) {
        dp[0][u] = 1;
        dp[1][u] = 1;
        return;
    }

    for (int v : adj[u]) {
        if (visited[v]) continue;
        dfs(v);
        dp[0][u] = add(dp[1][v], dp[0][u]);
        dp[1][u] = add(add(dp[0][v], dp[1][v]), dp[1][u]);
    }
}

int main() {
    int N;
    cin >> N;

    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);

    // for (auto x : dp) {
    //     for (int i = 1; i <= N; i++) {
    //         cout << x[i] << " ";
    //     }
    //     cout << endl;
    // }
    
    cout << dp[0][1] + dp[1][1];

    return 0;
}