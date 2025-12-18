#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    int N;
    cin >> N;
    vector<int> h(N);

    for (int i; i < N; i++) {
        cin >> h[i];
    }

    vector<int> dp(N, 0);
    dp[1] = abs(h[1] - h[0]);
    for (int i = 2; i < N; i++){
        dp[i] = min(dp[i-1] + abs(h[i] - h[i-1]), dp[i-2] + abs(h[i] - h[i-2])); 
    }

    // for (auto x : dp) cout << x << " ";
    // cout << endl;

    cout << dp[N-1] << endl;

    return 0;
    

}