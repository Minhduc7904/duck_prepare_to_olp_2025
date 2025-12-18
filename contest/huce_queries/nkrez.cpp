#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    int n; cin >> n;
    map<int, vector<int>> times;
    
    int l = 0;
    for (int i = 1; i <= n; i++) {
        int start, end;
        cin >> start >> end;
        l = max(l, end);
        times[end].push_back(start);
    } 

    vector<ll> dp(l + 1);

    for (int e = 1; e <= l; e++) {
        dp[e] = dp[e-1];
        for (int s : times[e]) {
            int time = e - s;
            dp[e] = max(dp[e], dp[e - time] + time);
        }
    }

    // for (int i = 0; i <= l; i++) cout << dp[i] << " ";
    // cout << endl;

    cout << dp[l] << endl;
    return 0;
}