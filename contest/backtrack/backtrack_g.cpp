#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e6;
vector<bool> isPrimes(N, true);
vector<int> primes;
vector<ll> factorize;
vector<int> power;

void sang_nguyen_to(int n) {
    isPrimes[0] = isPrimes[1] = false;
    for (ll i = 2; 1ll * i * i <= n; i++) {
        if (isPrimes[i]) {
            for (ll j = 1ll * i * i; j <= n; j += i) {
                isPrimes[j] = false;
            }
        }
    }

    for (ll i = 2; 1ll * i * i <= n; i++) {
        if (isPrimes[i]) primes.push_back(i);
    }
}

void phan_tich(int n) {
    for (int p : primes) {
        if (1ll * p * p > n) break;
        int cnt = 0;
        while(n % p == 0) {
            cnt++;
            n /= p;
        }
        if (cnt > 0) {
            factorize.push_back(p);
            power.push_back(cnt);
        }
    }
}

void back_track(vector<ll> &f, vector<int> &p, vector<int> &chu_cai, int idx = 0) {
    if (idx == (int)f.size()) {
        
    }
}

int main() {
    ll n; cin >> n;
    string s; cin >> s;

    vector<int> chu_cai(10, 0);
    for (auto c : s) {
        chu_cai[c - '0']++;
    }

    sang_nguyen_to(n);
    phan_tich(n);

    back_track(factorize, power, chu_cai);

    return 0;
}