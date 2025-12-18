#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll compute () {

}

int back_track(vector<ll> &a, vector<int> sign, int n, ll m) {
    int result;

    if (compute(vector<ll> &a, vector<int> &sign, int n) == m) result++;


    return result;
}


int main() {
    int t;
    cin >> t;

    while (t--) {
        int n; 
        ll m;
        cin >> n >> m;
        vector<int> sign(1);
        vector<ll> a(n + 1);

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        int result = back_track(a, sign, n, m);

        cout << result << endl;
    }







    return 0;
}