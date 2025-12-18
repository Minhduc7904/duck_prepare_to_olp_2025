#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 3e5;
const int MOD = 1337377;

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return ((a - b) % MOD + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return (1ll * a * b) % MOD;
}

struct Trie {
    struct Node {
        int child[26];
        int exist, cnt;
    };

    Node nodes[N + 5];
    int cur;

    Trie() {
        cur = 0;
        memset(nodes[0].child, -1, sizeof(nodes[0].child));
        nodes[0].exist = nodes[0].cnt = 0;
    }

    int new_node() {
        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].exist = nodes[cur].cnt = 0;
        return cur;
    }

    void add_string(string s) {
        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) {
                nodes[pos].child[c] = new_node();
            }
            pos = nodes[pos].child[c];
            nodes[pos].cnt++;
        }
        nodes[pos].exist++;
    }

    bool find_string(string s) {
        int pos = 0;
        for (auto f : s){
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) return false;
            pos = nodes[pos].child[c];
        }
        return (nodes[pos].exist != 0);
    }
};

Trie trie;


int main() {
    string s;
    cin >> s;
    int len = s.size(); s = ' ' + s;
    int max_l = 0;
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        string x; cin >> x;
        trie.add_string(x);
        max_l = max(max_l, (int)x.size());
    } 

    vector<int> dp(len + 1, 0);
    dp[0] = 1;
    for (int i = 0; i <= len; i++) {
        if (dp[i] == 0) continue;
        int pos = 0;
        for (int j = i + 1; j <= len && j < i + max_l + 1; j++) {
            int c = s[j] - 'a';
            if (trie.nodes[pos].child[c] == -1) break;
            pos = trie.nodes[pos].child[c];
            if (trie.nodes[pos].exist != 0) {
                dp[j] = add(dp[j], dp[i]);
            }
        }
    }

    cout << dp[len] << endl;
    return 0;
}