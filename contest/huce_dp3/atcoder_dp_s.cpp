#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

string S;
const int P = 1e4;
const int D = 100;
int dp[P][D][2];
int d;

int sum(int a, int b) {
    a += b;
    while (a > MOD) a-=MOD;
    while (a < 0) a+=MOD;
    return a;
}

int dp_digit(int p, int cnt, int c){
    int ans = 0;
    if (p == S.size()) {
        if (cnt == 0) return 1;
        return 0;
    }

    if (dp[p][cnt][c] != -1) return dp[p][cnt][c];

    // c == 1 Đã bé hơn S
    // c == 0 chưa bé hơn S
    int limit = (c == 1 ? 9 : S[p] - '0');

    for (int i = 0; i <= limit; i++) {
        int mod = (cnt + i) % d;
        if (i == S[p] - '0' && c == 0) {
            ans = sum(ans, dp_digit(p + 1, mod, 0));
        } else {
            ans = sum(ans, dp_digit(p + 1, mod, 1));
        }
    }
    dp[p][cnt][c] = ans;
    return ans;
}

int main() {
    cin >> S;
    cin >> d;
    memset(dp, -1, sizeof(dp));
    cout << dp_digit(0, 0, 0) - 1;
}