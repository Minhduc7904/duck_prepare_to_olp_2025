#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int n, k;
    cin >> n >> k;

    vector<bool> green(n + 1, false);

    for (int i = 1; i <= k; i++) {
        int a;
        cin >> a;
        green[a] = true;
    }
    ll result = 0;

    if (k == 0) {
        for (int i = 1; i <= n - 1; i++) {
            for (int h = 1; h <= n - i; h++) {
                result += h * i;
            }
        }
    } else {
        
    }

    cout << result;
    return 0;
}