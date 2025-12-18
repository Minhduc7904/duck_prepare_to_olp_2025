#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e6 + 1;

vector<bool> isPrime(N, true);
vector<int> primes;

void sinh_primes() {
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i < N; i++) {
        if (isPrime[i]) primes.push_back(i);

        for (int p : primes) {
            ll x = 1LL * p * i;
            if (x >= N) break;
            isPrime[x] = false;
            if (i % p == 0) break;
        }
    }

}

int main() {
    int n; cin >> n;
    sinh_primes();
    vector<int> a(n + 1);

    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<ll> prefix_sum(n + 1);

    for (int i = 1; i <= n; i++) {
        prefix_sum[i] = prefix_sum[i-1] + a[i];
    }

    ll best_sum = -N;
    ll min_pre = prefix_sum[1];

    for (int R : primes) {
        if (R > n) break;

        best_sum = max(prefix_sum[R] - min_pre, best_sum);

        min_pre = min(min_pre, prefix_sum[R - 1]);
    }
    

    // for (int i = 0; i < primes.size(); i++) {
    //     cout << primes[i] << " ";
    // }
    // cout << endl;

    cout << best_sum;
    return 0;
}