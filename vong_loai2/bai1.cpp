#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int N;
    ll W;
    cin >> N >> W;

    int max_value = 100001;

    vector<ll> weight(N);
    vector<int> value(N);

    for (int i = 0; i < N; i++) {
        cin >> weight[i] >> value[i];
    }

    vector<vector<ll>> dp(N, vector<ll> (max_value, 1000000001));
    dp[0][0] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < max_value; j++) {
            if (i == 0) {
                if (j == value[i]) {
                    dp[i][j] = weight[i];
                }
                continue;
            }
            if (j < value[i]) {
                dp[i][j] = dp[i-1][j];
                continue;
            }
            dp[i][j] = min(dp[i-1][j], dp[i-1][j-value[i]] + weight[i]);
        }
    }

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j <= 90; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = max_value - 1; i >= 0; i--){
        if (dp[N-1][i] <= W) {
            cout << i << endl;
            return 0;
        } 

    }

    return 0;
}