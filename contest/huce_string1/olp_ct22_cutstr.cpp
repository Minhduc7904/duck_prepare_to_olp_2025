#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e4;
string S;
int T, n;
vector<vector<bool>> dp(N + 1, vector<bool> (N + 1));
vector<vector<int>> vt(N + 1, vector<int> (N + 1));

void prepare() {
    cin >> S;
    cin >> T;
    n = S.size();
    S = "#" + S;
}

void process() {    

    for (int j = 1; j <= n; j++) {
        for (int i = j; i >= 1; j--) {
            if (i == j) {
                dp[i][j] = 1;
                vt[i][1] = i;
            }
            else if (i == j - 1) {
                if (S[i] == S[j]) {
                    dp[i][j] = 1;
                    vt[i][2] = i;
                }
            }
            else {
                if (S[i] != S[j]) continue;
                if(dp[i + 1][j - 1]) {
                    dp[i][j] = 1;
                    vt[i][j - i + 1] = i;
                }
            }
        }
    } 

    while (T--) {
        int k;
        vector<int> 
    }

}

int main() {
    prepare();
    process();
    return 0;
}
