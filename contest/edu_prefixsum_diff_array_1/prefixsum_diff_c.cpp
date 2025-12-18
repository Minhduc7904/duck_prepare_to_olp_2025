#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ll best_sum = -1e9;
    ll cur_sum = -1;
    for (int i = 1; i <= n; i++) {
        if (cur_sum < 0) cur_sum = a[i];
        else cur_sum += a[i];
        best_sum = max(best_sum, cur_sum);
    }

    cout << best_sum;

    return 0;
}