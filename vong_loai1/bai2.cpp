#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    int N, M;
    cin >> N >> M;

    vector<ll> costs(N);
    for (int i = 0; i < N; i++){
        cin >> costs[i];
    }

    while (M--) {
        int counts = 0;
        
        for (int i = 0; i < N; i++){
            int du_doan;
            cin >> du_doan;
            for (auto x : costs) {
                if (du_doan == x) counts++;
            }
        }

        cout << counts << endl;
    }
    return 0;
}