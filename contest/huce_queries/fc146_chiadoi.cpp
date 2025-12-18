#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
const int N = 4e5;
int fact[N + 5], ifact[N + 5];

ll binpow(ll a, ll b) {
    ll ans = 1;
    while(b > 0) {
        if (b % 2) ans = 1ll * ans * a % MOD;
        a = 1ll * a * a % MOD;
        b /= 2;
    }
    return ans;
}

void prepare() {
    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = 1ll * fact[i - 1] * i % MOD;
    }

    ifact[N] = binpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 0; i--) {
        ifact[i] = 1ll * ifact[i + 1] * (i + 1) % MOD;
    }
}

long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return 1ll * fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;

    prepare();

    vector<ll> a(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());

    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        sum = (sum + (a[2 * n - i + 1] - a[i])) % MOD;
        if (sum < 0) sum += MOD;
    }

    ll ans = sum * C(2 * n, n) % MOD;
    cout << ans << endl;

    return 0;
}