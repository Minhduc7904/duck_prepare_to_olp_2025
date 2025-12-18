# TRIE (Cây tiền tố)

## Cấu trúc Trie cơ bản

https://wiki.vnoi.info/algo/string/trie

Trie, hay một số tài liệu còn gọi là cây tiền tố, là một cấu trúc dữ liệu dạng cây hữu dụng được dùng để quản lí một tập hợp các xâu. Mặc dù dễ hiểu và dễ cài đặt, trie lại có rất nhiều ứng dụng. Do vậy, trie thường xuyên xuất hiện trong các cuộc thi lập trình ở Việt Nam nói riêng và quốc tế nói chung.

Một trie cơ bản có thể thực hiện ba thao tác sau với độ phức tạp thời gian tuyến tính:

- Thêm một xâu vào tập hợp
- Xóa một xâu khỏi tập hợp
- Kiểm tra một xâu có nằm trong tập hợp đó hay không

```cpp
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

```

## Trie với đếm tần suất

```cpp
struct TrieNode {
    TrieNode* children[26];
    int count;
    int endCount;
    
    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        count = 0;
        endCount = 0;
    }
};

class TrieWithCount {
private:
    TrieNode* root;
    
public:
    TrieWithCount() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
            node->count++;
        }
        node->endCount++;
    }
    
    int countPrefix(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) return 0;
            node = node->children[idx];
        }
        return node->count;
    }
    
    int countWord(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) return 0;
            node = node->children[idx];
        }
        return node->endCount;
    }
};
```

## Trie cho số (Binary Trie)

```cpp
struct BinaryTrieNode {
    BinaryTrieNode* children[2];
    int count;
    
    BinaryTrieNode() {
        children[0] = children[1] = nullptr;
        count = 0;
    }
};

class BinaryTrie {
private:
    BinaryTrieNode* root;
    const int MAXBIT = 30;
    
public:
    BinaryTrie() {
        root = new BinaryTrieNode();
    }
    
    void insert(int num) {
        BinaryTrieNode* node = root;
        for (int i = MAXBIT; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->children[bit]) {
                node->children[bit] = new BinaryTrieNode();
            }
            node = node->children[bit];
            node->count++;
        }
    }
    
    int maxXOR(int num) {
        BinaryTrieNode* node = root;
        int result = 0;
        
        for (int i = MAXBIT; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int oppositeBit = 1 - bit;
            
            if (node->children[oppositeBit] && node->children[oppositeBit]->count > 0) {
                result |= (1 << i);
                node = node->children[oppositeBit];
            } else {
                node = node->children[bit];
            }
        }
        return result;
    }
};
```

## Ứng dụng

### Autocomplete
```cpp
void getAllWords(TrieNode* node, string current, vector<string>& results) {
    if (node->isEnd) {
        results.push_back(current);
    }
    
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            getAllWords(node->children[i], current + char('a' + i), results);
        }
    }
}

vector<string> autocomplete(string prefix) {
    TrieNode* node = root;
    for (char c : prefix) {
        int idx = c - 'a';
        if (!node->children[idx]) return {};
        node = node->children[idx];
    }
    
    vector<string> results;
    getAllWords(node, prefix, results);
    return results;
}
```

## Độ phức tạp
- **Insert**: O(m) với m là độ dài từ
- **Search**: O(m)
- **Space**: O(ALPHABET_SIZE * m * n) với n là số từ
