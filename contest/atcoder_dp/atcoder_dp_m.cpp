#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;

ll cong(ll a, ll b) {
    return (a + b) % MOD; 
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> a(N);

    for (int &x : a) cin >> x;

    vector<vector<ll>> dp(N, vector<ll>(K + 1, 0));
    dp[0][0] = 1;
    for (int j = 1; j <= K; j++) {
        if (j <= a[0]) {
            dp[0][j] = 1;
        }
    }

    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= K; j++) {
            for (int k = 0; k <= a[i]; k++) {
                if (k > j) {
                    dp[i][j] = cong(dp[i-1][k], dp[i][j]) ;
                } else {
                    dp[i][j] = cong(dp[i-1][j-k], dp[i][j]);
                }
            }
        }
    }

    // for (auto x : dp) {
    //     for (auto y : x) {
    //         cout << y << " ";
    //     }
    //     cout << endl;
    // }
    cout << dp[N-1][K];
    return 0;
}