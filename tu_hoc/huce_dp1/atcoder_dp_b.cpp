#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> h(N);

    for (auto &x : h) cin >> x;
    
    vector<int> dp(N, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i < N; i++) {
        int start = max(0, i - K);
        for (int j = start; j < i; j++){
            dp[i] = min(dp[i], dp[j] + abs(h[i] - h[j]));
        }
    }

    cout << dp[N-1] << endl;

    return 0;
}