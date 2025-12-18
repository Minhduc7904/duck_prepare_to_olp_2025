#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e5;
vector<int> a(N + 1);

int main() {
    int n; cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i];

    set<int> ans;
    set<int> prev, cur;
    for (int i = 1; i <= n; i++) {
        cur.clear();

        cur.insert(a[i]);
        ans.insert(a[i]);
        for (ll x : prev) {
            ll y = x | a[i];
            cur.insert(y);
            ans.insert(y);
        }

        prev = cur;
    }


    cout << ans.size() << endl;

    return 0;
}