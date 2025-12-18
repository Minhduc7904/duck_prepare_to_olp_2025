#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    ll N, X, Y;
    int t;

    cin >> t;

    while (t--) {
        cin >> N >> X >> Y;
        ll nu = ( N * Y ) / ( X + Y );
        ll nam = N - nu;
        if (nu < nam) cout << nu << " " << nam;
        else cout << nam << " " << nu;
        cout << endl;
    }
    return 0;
}