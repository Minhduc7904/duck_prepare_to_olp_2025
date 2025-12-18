#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    ll lf, rt;
    cin >> lf >> rt;
    ll result = 0;
    int mu = 1;
    ll index = 2;

    while (index <= rt) {
        ll a = lf / index;
        ll b = rt / index;
        if (a % 2 == 0) a++;
        if (b % 2 == 0) b--;

        ll x = index * a;
        if (x < lf) {
            x += index * 2;
            a += 2;
        }
        
        ll y = index * b;

        // cout << index << " " << x << " " << a << " " << y << " " << b << endl;

        if (x >= lf && y <= rt && x <= y && a <= b) {
            result += 1ll * ((b - a) / 2 + 1) * 1 * mu ;
            // cout << result << endl;
        }

        mu++;
        index *= 2;
    }

    cout << result;

    return 0;
}