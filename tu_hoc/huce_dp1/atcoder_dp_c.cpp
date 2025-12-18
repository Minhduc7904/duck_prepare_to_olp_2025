#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    int N;
    cin >> N;

    vector<int> scores(4, 0);
    vector<ll> dp1(5, 0);
    vector<ll> dp(5, 0);

    while (N--) {
        for (int i = 1; i <= 3; i++){
            cin >> scores[i];
        } 

        for (int i = 1; i <= 3; i++){
            if (i == 1) dp[i] = scores[i] + max(dp1[i+1], dp1[i+2]);
            else if (i == 2) dp[i] = scores[i] + max(dp1[i+1], dp1[i-1]);
            else if (i == 3) dp[i] = scores[i] + max(dp1[i-1], dp1[i-2]);
        }
        dp1 = dp;
    }


    cout << *max_element(dp.begin(), dp.end()) << endl;

    return 0;
}