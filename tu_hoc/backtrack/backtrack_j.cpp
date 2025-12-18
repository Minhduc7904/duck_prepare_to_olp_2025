#include <bits/stdc++.h>
using namespace std;

int n, m;

bool back_track(vector<vector<char>> &G, int empty_counts, int i = 1, int j = 1) {
    if (empty_counts == 0) return true;

    if (j > m) {
        j = 1;
        i++;
    }
    if (i == n) return false;

    if (G[i][j] != '.') {
        return back_track(G, empty_counts, i, j + 1);
    }

    bool S = false;

    if (i < n && j < m &&
        G[i+1][j] == '.' &&
        G[i+1][j+1] == '.') {

        G[i][j] = G[i+1][j] = G[i+1][j+1] = '*';
        S = back_track(G, empty_counts - 3, i, j + 1);
        if (S) return true;
        G[i][j] = G[i+1][j] = G[i+1][j+1] = '.';
    }

    if (i < n && j > 1 &&
        G[i+1][j] == '.' &&
        G[i+1][j-1] == '.') {

        G[i][j] = G[i+1][j] = G[i+1][j-1] = '*';
        S = back_track(G, empty_counts - 3, i, j + 1);
        if (S) return true;
        G[i][j] = G[i+1][j] = G[i+1][j-1] = '.';
    }

    return false;
}

int main() {
    cin >> n >> m;
    vector<vector<char>> G(n + 2, vector<char>(m + 2, '#')); 
    int empty_counts = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> G[i][j];
            if (G[i][j] == '.') empty_counts++;
        }
    }

    if (empty_counts % 3 != 0) {
        cout << "NO";
        return 0;
    }

    cout << (back_track(G, empty_counts) ? "YES" : "NO");
    return 0;
}
