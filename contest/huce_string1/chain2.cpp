#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 25e4;

struct Trie {
    struct Node {
        int child[26];
        int cnt, exist;
    };

    Node nodes[N + 5];
    int cur;
    int l = 0;
    Trie() {
        cur = 0;
        memset(nodes[cur].child, -1, sizeof(nodes[0].child));
        nodes[cur].cnt = nodes[cur].exist = 0;
    }

    int new_node() {
        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[0].child));
        nodes[cur].cnt = nodes[cur].exist = 0;
        return cur;
    }

    void add_string(string s) {
        int pos = 0;
        int counts = 1;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) {
                nodes[pos].child[c] = new_node();
            }
            pos = nodes[pos].child[c];
            if (nodes[pos].exist != 0) {
                counts++;
            }
            nodes[pos].cnt++;
        }
        l = max(counts, l);
        nodes[pos].exist++;
    }

    bool delete_string_recursive(int pos, string &s, int i) {
        if (i != (int)s.size()) {
            int c = s[i] - 'a';
            bool isChildDeleted = delete_string_recursive(nodes[pos].child[c], s, i + 1);
            if (isChildDeleted) nodes[pos].child[c] = -1;
        } else nodes[pos].exist--;

        if (pos != 0) {
            nodes[pos].cnt--;
            if (nodes[pos].cnt == 0) return true;
        }
        return false;
    }

    bool find_string(string s) {
        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) return false;
            pos = nodes[pos].child[c];
        }
        return (nodes[pos].exist != 0);
    }

    void delete_string(string s) {
        if (!find_string(s)) return;
        delete_string_recursive(0, s, 0);
    }
};

Trie trie;

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        trie.add_string(s);
    }
    cout << trie.l;
    return 0;
}