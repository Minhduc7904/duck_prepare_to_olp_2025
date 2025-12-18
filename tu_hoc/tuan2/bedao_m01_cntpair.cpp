#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    int le = 0, chan = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] % 2) le += 1;
        else chan += 1; 
    }

     

    cout << 1ll * le * (le - 1) / 2 + 1ll * chan * (chan - 1) / 2 << endl;

    return 0;
}