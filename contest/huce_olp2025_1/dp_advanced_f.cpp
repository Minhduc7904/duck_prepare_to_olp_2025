#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e5;
vector<ll> a(N + 1);

int n, st, d;
ll ans = 0;

void back_track(int idx, ll s, int dao, vector<bool> &visited, bool trai) {
    if (idx > d) {
        ans = max(ans, s);
        return;
    }
    
    if (!visited[dao]) {
        visited[dao] = true;
        back_track(idx + 1, s + a[dao], dao, visited, trai);
        visited[dao] = false;
    }

    if (dao > 1 && dao < n) {
        back_track(idx + 1, s, dao + 1, visited, trai);
        if (trai) back_track(idx + 1, s, dao - 1, visited, trai);
    } else if (dao == 1) {
        back_track(idx + 1, s, dao + 1, visited, trai);
    } else if (dao == n && trai) {
        back_track(idx + 1, s, dao - 1, visited, trai);
    }
}

int main() {    
    cin >> n >> st >> d;
    for (int i = 1; i<= n; i++) cin >> a[i];
    vector<bool> visited(n + 1, false);
    back_track(1, 0, st + 1, visited, !(st == 0));
    cout << ans;
    return 0;
}