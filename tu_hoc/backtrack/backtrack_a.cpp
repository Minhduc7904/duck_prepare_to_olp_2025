#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, k;
int cost[51][51];
int min_cost = 1e7;
vector<int> result;

void back_track(vector<int> found, vector<int> S = {1}, int c = 0){
    // for (auto x : S) cout << x << " ";
    // cout << endl;

    int len = S.size();

    if (len == k) {
        c += cost[S[len-1]][S[0]]; 
        if (min_cost > c){
            min_cost = c;
            result = S;
        }
        return;
    }

    if (c > min_cost) return;

    
    for (int i = 2; i <= n; i++) {
        if (found[i] == 1) continue;
        vector<int> S1(S.begin(), S.end());
        S1.push_back(i);
        found[i] = 1;
        back_track(found, S1, c + cost[S[len-1]][i]);
        found[i] = 0;
    }
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> cost[i][j];
        }
    }
    vector<int> found(n + 1, 0);
    found[1] = 1;

    back_track(found);

    cout << min_cost << endl;
    for (auto x : result) cout << x << " ";
    cout << endl;

    return 0;
}