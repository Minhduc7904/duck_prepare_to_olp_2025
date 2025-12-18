#include <bits/stdc++.h>


using namespace std;

typedef long long ll;
int n;
string S[26];
int c = 0;

void back_track(set<char> R = {}, int k = 1) {
    if (k == n + 1) {
        if (R.size() == 26) c += 1;
        return;
    }

    if (R.size() == 26) {
        c += pow(2, n - k - 1);
        return;
    }

    for (int i = k; i <= n; i++) {
        set<char> copy(R.begin(), R.end());
        back_track(copy, k + 1);
        for (char h : S[i]) copy.insert(h);
        back_track(copy, k + 1);
    }
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> S[i];
    }

    back_track();

    cout << c;

    return 0;
}