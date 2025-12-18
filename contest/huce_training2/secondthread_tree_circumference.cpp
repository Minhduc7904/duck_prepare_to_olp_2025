#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 3e5 + 1;
vector<int> g[N];

// bool visited[N];
int start, end, length = 0;

void DFS(int s, int parent, bool is_start = true, int len = 0) {
    if (len > length) {
        length = len;
        if (is_start) start = s;
    }

    for (int v : g[s]) {
        if (v == parent) continue;
        DFS(v, s, is_start, len + 1);
    }
}


int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    DFS(1, 1);
    length = 0;
    DFS(start, start, false);

    cout << length * 3 << endl;

    return 0;
}