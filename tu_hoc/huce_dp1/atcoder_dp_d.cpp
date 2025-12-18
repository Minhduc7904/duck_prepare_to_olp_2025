#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, W;
int weight[101], value[101];

void solve1() {
    vector<vector<ll>> dp(N, vector<ll>(W + 1, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= W; j++) {
            if (i == 0) {
                if (j >= weight[i]) dp[i][j] = value[i];
            } else {
                if (j >= weight[i]) dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]] + value[i]);
                else dp[i][j] = dp[i-1][j];
            }
        } 
    }

    cout << dp[N-1][W] << endl;
}

void solve2() {
    vector<ll> dp(W+1, 0);

    for (int i = 0; i < N; i++){
        for (int j = W; j >= weight[i]; j--){
            dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
        }
    }

    cout << dp[W] << endl;
}

int main() {
    cin >> N >> W;

    for (int i = 0 ; i < N; i++) {
        cin >> weight[i] >> value[i];
    }

    // solve1();
    solve2();

    return 0;
}