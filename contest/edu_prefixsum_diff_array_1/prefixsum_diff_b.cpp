#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<vector<ll>> R(N + 1, vector<ll> (M + 1));

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> R[i][j];
        }
    }

    vector<vector<ll>> prefix_sum(N + 1, vector<ll> (M + 1));
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            prefix_sum[i][j] = prefix_sum[i-1][j] + prefix_sum[i][j-1] - prefix_sum[i-1][j-1] + R[i][j];
        }
    }

    // for (auto x : prefix_sum) {
    //     for (auto y : x) {
    //         cout << y << " ";
    //     }
    //      cout << endl;
    // }

    while (Q--) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        cout << prefix_sum[x2][y2] - prefix_sum[x1-1][y2] - prefix_sum[x2][y1-1] + prefix_sum[x1-1][y1-1] << endl; 
    }

    return 0;
}