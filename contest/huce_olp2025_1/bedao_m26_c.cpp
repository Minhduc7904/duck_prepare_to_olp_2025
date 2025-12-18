#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define fi first
#define se second
const int max_n = 1e6;
vector<bool> visited(max_n, false);
vector<int> G[max_n];

bool sort_A (pair<ll, ll> a, pair<ll, ll> b) {
    return a.se > b.se;
}

bool BFS(int idx, pair<ll, ll> s) {
    if (visited[idx]) return false;
    deque<pair<ll, ll>> q;
    q.push_back(s);
    visited[1] = true;
    int ans = 0;
    while (!q.empty()) {
        auto O = q.front(); q.pop_front();
        int x = O.fi, e = O.se;

    }
}

int main() {
    int N;
    cin >> N;
    vector<pair<ll, ll>> A(N + 1);

    set<ll> Xs;
    set<ll> Es;

    for (int i = 1; i <= N; i++) {
        cin >> A[i].fi >> A[i].se;
        Xs.insert(A[i].fi);
        Es.insert(A[i].se);
    }

    sort(A.begin() + 1, A.end(), sort_A);


    if (Es.size() == 1) {
        cout << Xs.size() << endl;
        return 0;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j) continue;   
            ll x_i = A[i].fi, x_j = A[j].fi;
            ll e_i = A[i].se, e_j = A[j].se;      
            if (abs(x_i - x_j) <= (e_i - e_j)) {
                G[i].push_back(j);
            }
        }
    }

    return 0;
}