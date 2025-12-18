#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, W;
int weight[101], value[101];
int MAX_VALUE = 1000 * 100;
long long MAX = 10000000000000000000;

void solve() {
    vector<ll> dp(MAX_VALUE + 1, MAX);

    for (int i = 0; i < N; i++) {
        for (int j = MAX_VALUE; j >= value[i]; j--) {
            dp[j] = min(dp[j], dp[j - value[i]] + weight[i]);
            if (i == N - 1 && dp[j] <= W) {
                cout << j << " " << W << endl;
                return;
            } 
        }
    }
}


int main() {
    cin >> N >> W;

    for (int i = 0; i < N; i++) {
        cin >> weight[i] >> value[i];
    }

    solve();

    return 0;
}