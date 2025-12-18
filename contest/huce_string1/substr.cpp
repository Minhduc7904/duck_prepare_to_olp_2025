#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    string s, t;
    cin >> t >> s;
    
    int m = s.size(); s = "#" + s;
    int n = t.size(); t = "*" + t;

    vector<int> kmp(m + 1);
    kmp[1] = 0;
    int k = 0;
    for (int i = 2; i <= m; i++) {
        while(k > 0 && s[i] != s[k+1]) k = kmp[k];
        if (s[i] == s[k+1]) k++;
        kmp[i] = k;
    }

    vector<int> match(n + 1);
    k = 0;
    for (int i = 1; i <= n; i++) {
        while(k > 0 && t[i] != s[k+1]) k = kmp[k];
        if (t[i] == s[k+1]) k++;
        match[i] = k;
        if (match[i] == m) cout << i - m + 1 << " ";
    }

    return 0;
}