#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX_N = 1e6;

struct Trie {
    struct Node {
        int child[2];
        int exist, cnt;
    };

    Node nodes[MAX_N + 5];
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

    void add(string s) {
        int pos = 0;
        for (auto b : s) {
            int bit = b - '0';
            if (nodes[pos].child[bit] == -1) nodes[pos].child[bit] = new_node();
            pos = nodes[pos].child[bit];
            nodes[pos].cnt++;
        }
        nodes[pos].exist++;
    }
};

Trie trie;

int main() {
    int N, M;
    cin >> M >> N;
    for (int i = 1; i <= M; i++) {
        int k; cin >> k;
        string s;
        for (int j = 1; j <= k; j++) {
            char c; cin >> c;
            s += c;
        }
        trie.add(s);
    }

    for (int i = 1; i <= N; i++) {
        int k; cin >> k;
        string s = " ";
        for (int j = 1; j <= k; j++) {
            char c; cin >> c;
            s += c;
        }
        int counts = 0;
        int pos = 0;
        for (int j = 1; j <= k; j++) {
            int bit = s[j] - '0';
            if (trie.nodes[pos].child[bit] == -1) break;
            pos = trie.nodes[pos].child[bit];
            if (trie.nodes[pos].exist != 0) {
                counts += trie.nodes[pos].exist;
            } 
            if (j == k) {
                counts += trie.nodes[pos].cnt - trie.nodes[pos].exist;
            }
        }
        cout << counts << endl;
    }
}