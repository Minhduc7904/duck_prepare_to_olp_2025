#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    cin >> n;

    long long s = n * (n + 1) / 2;
    if (s % 2 != 0) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    vector<ll> a, b;

    if (n % 4 == 0) {
        for (ll i = 1; i <= n; i += 4) {
            a.push_back(i);
            a.push_back(i + 3);
            b.push_back(i + 1);
            b.push_back(i + 2);
        }
    } else if (n % 4 == 3) {
        a.push_back(1);
        a.push_back(2);
        b.push_back(3);
        for (ll i = 4; i <= n; i += 4) {
            a.push_back(i);
            a.push_back(i + 3);
            b.push_back(i + 1);
            b.push_back(i + 2);
        }
    }

    cout << a.size() << "\n";
    for (auto x : a) cout << x << " ";
    cout << "\n";

    cout << b.size() << "\n";
    for (auto x : b) cout << x << " ";
    cout << "\n";
}
