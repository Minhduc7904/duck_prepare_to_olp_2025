#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int N = 1e6;
int fact[N + 5], ifact[N + 5];
int grid[1000 + 1][1000 + 1];
int m, n, k;

ll binpow(ll a, ll b)
{
    ll ans = 1;
    while (b > 0)
    {
        if (b % 2)
            ans = ans * a % MOD;
        a = a * a % MOD;
        b = b / 2;
    }

    return ans;
}

void prepare()
{
    fact[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        fact[i] = 1ll * fact[i - 1] * i % MOD;
    }

    ifact[N] = binpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 1; i--)
    {
        ifact[i] = 1ll * ifact[i + 1] * (i + 1) % MOD;
    }
}

int C(int n, int k)
{
    if (k > n)
        return 0;
    return (1LL * fact[n] * ifact[k] % MOD) * ifact[n - k] % MOD;
}

void solve()
{
    if (k == 0)
    {
        int result = C(m + n - 2, m - 1);
        cout << result;
        return;
    }
    else
    {
        vector<ll> dp(n + 1, 0);
        vector<ll> dp1(n + 1, 0);
        vector<ll> last_col(m + 1);
        for (int i = 1; i <= min(1000, m); i++)
        {
            for (int j = 1; j <= min(1000, n); j++)
            {
                if (grid[i][j] == 1) {
                    dp[j] = 0;
                    continue;
                }
                if (i == 1 && j == 1) {
                    dp[j] = 1;
                    continue;
                }
                dp[j] = (dp1[j] + dp[j - 1]) % MOD;
                dp1 = dp;
                if (j == 1e3) last_col[i] = dp[j];
                // cout << i << " " << j << " " << dp[i][j] << endl;
                // cout << i << " " << j << " " << dp[j] << " ";
            }
            // cout << endl;
        }

        if (m <= 1e3 && n <= 1e3)
        {
            cout << dp[n] << endl;
            return;
        }
        ll result = 0;
        if (n > 1e3) {
            int max_i = max(m, 1000);
            for (int i = 1; i <= max_i; i++) {
                result += 1ll * last_col[i] * C(m - i + n - 1e3 + 1, m - i) % MOD; 
            }
        }
        if (m > 1e3) {
            int max_j = max(n, 1001);
            for (int j = 1; j <= max_j; j++) {
                result += 1ll * dp[j] * C(n - j + m - 1e3 + 1, n - j) % MOD;
            }
        }

        cout << result;
        return;
    }
}

int main()
{
    prepare();
    cin >> m >> n >> k;
    memset(grid, 0, sizeof(grid));

    while (k--)
    {
        int x, y;
        cin >> x >> y;
        grid[x][y] = 1;
    }

    solve();

    return 0;
}