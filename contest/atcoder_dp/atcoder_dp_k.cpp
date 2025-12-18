#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> a(N);

    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    vector<bool> dp(K+1);
    for (int i = 1; i <= K; i++) {
        for (int j : a) {
            if (i >= j && !dp[i - j]) {
                dp[i] = 1;
            }
        }
    }

    cout << (dp[K] ? "First" : "Second");
    return 0;
}