#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    string Sb, Se;
    cin >> Sb >> Se;

    string S = ' ' + Se + '#' + Sb;
    int n = S.size() - 1;
    vector<int> kmp(n + 1);
    kmp[1] = 0;
    int k = 0;
    for (int i = 2; i <= n; i++) {
        while (k > 0 && S[i] != S[k + 1]) k = kmp[k];
        if (S[i] == S[k + 1]) k++;
        kmp[i] = k;
    }

    cout << n - 1 - kmp[n];

    return 0;
}