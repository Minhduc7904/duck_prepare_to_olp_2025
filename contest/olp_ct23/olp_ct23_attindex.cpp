#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int p; cin >> p;

    string S; cin >> S;
    int q; cin >> q;
    int n = S.size();
    S = "#" + S;
    if (p == 2) {

        vector<ll> prefix_sum(n + 1);
        for (int i = 1; i <= n; i++) {
            if ((S[i] - '0' % 2 == 0)) {}
        }
        while (q--) {
            int L, R;
            cin >> L >> R;
            ll ans = 0;
            for (int i = L; i <= R; i++) {
                if ((S[i] - '0') % 2 == 0) ans = (ans + (R - i) + 1) % MOD;
            }
            cout << ans << endl;
        }
    } else {
        while (q--) {
            int L, R;
            cin >> L >> R;
            ll ans = 0;
            for (int i = L; i <= R; i++) {
                for(int j = i; j <= R; j++) {
                    string s = S.substr(i, j - i + 1);
                    ll N = stoll(s);
                    // cout << N << " ";
                    if (N % p == 0) ans++;
                }
            }
            // cout << endl;
            cout << ans << endl;

        }
    }

    return 0;
}