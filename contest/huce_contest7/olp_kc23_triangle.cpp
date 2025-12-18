#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    ll u, v;
    cin >> u >> v;
    ll S = 1ll * u * u + 1ll * v * v;
    if (S % 4 == 0) {
        cout << S / 4 << ".00";
    } else if (S % 4 == 1 || S % 4 == 3) {
        cout << S / 4 << ".25";
    } else {
        cout << S / 4 << ".50";
    }

    return 0;
}