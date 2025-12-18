#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll a, b, m;
    cin >> a >> b >> m;
    ll n = max(a, b);
    vector<ll> fib(n + 1);
    fib[1] = fib[2] = 1;

    for (ll i = 3; i <= n; i++) {
        fib[i] = (fib[i-1] + fib[i-2]);
    }
    cout << __gcd(fib[a], fib[b]) % m << endl;
    
    return 0;
}