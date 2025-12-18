# QUY HOẠCH ĐỘNG - BIT MASK

## Travelling Salesman Problem (TSP)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;


ll binPow(ll a, ll b) {
    ll ans = 1;
    while (b > 0) {
        if (b % 2) ans = 1ll * ans * a % MOD;
        a = 1ll * a * a % MOD;
        b /= 2;
    }

    return ans;
}

int add(int &a, int b) {
    a += b;
    while (a > MOD) a -= MOD;
    if (a < 0) a += MOD;
    return a;
}

int sum(int a, int b) {
    return add(a, b), a;
}

int main() {
    int n;
    cin >> n;
    ll N = pow(2, n);
    vector<int> dp(N);
    dp[0] = 1;

    vector<vector<int>> a(n, vector<int> (n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        int k = __builtin_popcount(i);
        for (int j = 0; j < n; j++) {
            int c = i & (1 << j);
            if (c == 0 && a[k][j]) {
                ll cur = i | (1 << j);
                dp[cur] = sum(dp[cur], dp[i]);
            }
        }
    }

    cout << dp[N-1];
    return 0;
}
```

## Lưu ý
- Chỉ dùng cho n ≤ 20 (2^20 = 1,048,576)
- Độ phức tạp: O(2^n * n) hoặc O(2^n * n^2)
- Cần tối ưu bộ nhớ khi n lớn
