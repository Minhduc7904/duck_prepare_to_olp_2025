#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int n, m;
const int N = 801;
vector<int> g[N];
bool visited[N];
int result = 0;

void DFS(int s, int &check, vector<int> &vis) {
    if (visited[s]) {
        check = false;
    }
    if (vis[s]) return;

    for (int v : g[s]) {
        
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }










    return 0;
}