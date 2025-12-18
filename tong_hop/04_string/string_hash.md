# STRING HASH

## Hash cơ bản

```cpp
const long long BASE = 311;
const long long MOD = 1e9 + 7;

long long hashValue(string s) {
    long long res = 0;
    for (char c : s) {
        res = (res * BASE + c) % MOD;
    }
    return res;
}
```

## Hash với mảng tiền tố

```cpp
const long long BASE = 311;
const long long MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;

long long h[MAXN];      // Mảng hash tiền tố
long long powBase[MAXN]; // Lũy thừa của BASE

void precompute(string s) {
    int n = s.length();
    powBase[0] = 1;
    h[0] = 0;
    
    for (int i = 0; i < n; i++) {
        h[i + 1] = (h[i] * BASE + s[i]) % MOD;
        powBase[i + 1] = (powBase[i] * BASE) % MOD;
    }
}

long long getHash(int l, int r) {
    // Hash của xâu con từ l đến r (0-indexed)
    return (h[r + 1] - h[l] * powBase[r - l + 1] % MOD + MOD) % MOD;
}
```

## Double Hash (tránh collision)

```cpp
const long long BASE1 = 311;
const long long MOD1 = 1e9 + 7;
const long long BASE2 = 313;
const long long MOD2 = 1e9 + 9;

struct Hash {
    long long h1, h2;
    
    bool operator == (const Hash& other) const {
        return h1 == other.h1 && h2 == other.h2;
    }
};

Hash hashValue(string s) {
    Hash res = {0, 0};
    for (char c : s) {
        res.h1 = (res.h1 * BASE1 + c) % MOD1;
        res.h2 = (res.h2 * BASE2 + c) % MOD2;
    }
    return res;
}
```

## Polynomial Rolling Hash

```cpp
class PolynomialHash {
private:
    vector<long long> h, pow;
    long long base, mod;
    
public:
    PolynomialHash(string s, long long b = 311, long long m = 1e9 + 7) {
        base = b;
        mod = m;
        int n = s.length();
        h.resize(n + 1);
        pow.resize(n + 1);
        
        h[0] = 0;
        pow[0] = 1;
        
        for (int i = 0; i < n; i++) {
            h[i + 1] = (h[i] * base + s[i]) % mod;
            pow[i + 1] = (pow[i] * base) % mod;
        }
    }
    
    long long getHash(int l, int r) {
        return (h[r + 1] - h[l] * pow[r - l + 1] % mod + mod) % mod;
    }
};
```

## Ứng dụng

### So sánh hai xâu con
```cpp
bool isEqual(int l1, int r1, int l2, int r2) {
    return getHash(l1, r1) == getHash(l2, r2);
}
```

### Tìm xâu con palindrome
```cpp
bool isPalindrome(int l, int r) {
    // Hash xuôi và hash ngược
    long long hashForward = getHash(l, r);
    long long hashBackward = getReverseHash(l, r);
    return hashForward == hashBackward;
}
```

### Tìm xâu con lặp lại
```cpp
int findRepeatingPattern(string s) {
    int n = s.length();
    
    for (int len = 1; len <= n / 2; len++) {
        if (n % len != 0) continue;
        
        bool valid = true;
        long long firstHash = getHash(0, len - 1);
        
        for (int i = len; i < n; i += len) {
            if (getHash(i, i + len - 1) != firstHash) {
                valid = false;
                break;
            }
        }
        
        if (valid) return len;
    }
    return n;
}
```

### Tìm xâu con chung dài nhất
```cpp
int longestCommonSubstring(string s1, string s2) {
    int n1 = s1.length(), n2 = s2.length();
    
    // Thử binary search độ dài
    int left = 0, right = min(n1, n2);
    int result = 0;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        
        unordered_set<long long> hashes;
        bool found = false;
        
        // Lưu hash của tất cả xâu con độ dài mid của s1
        for (int i = 0; i <= n1 - mid; i++) {
            hashes.insert(getHash1(i, i + mid - 1));
        }
        
        // Kiểm tra s2
        for (int i = 0; i <= n2 - mid; i++) {
            if (hashes.count(getHash2(i, i + mid - 1))) {
                found = true;
                break;
            }
        }
        
        if (found) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}
```

### Đếm số xâu con phân biệt
```cpp
int countDistinctSubstrings(string s) {
    int n = s.length();
    unordered_set<long long> hashes;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            hashes.insert(getHash(i, j));
        }
    }
    
    return hashes.size();
}
```

## Lưu ý
- Chọn BASE là số nguyên tố lớn (thường 311, 313)
- MOD thường là 10^9 + 7 hoặc 10^9 + 9
- Dùng double hash để giảm xác suất collision
- Độ phức tạp: O(n) preprocessing, O(1) query
