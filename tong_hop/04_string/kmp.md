# KMP (KNUTH-MORRIS-PRATT)

## Thuật toán KMP

```cpp
string s, t;
cin >> s >> t;

int m = s.size();
int n = t.size();

// Chuyển về 1-based
s = "$" + s;
t = "#" + t;

// ==========================
// TÍNH MẢNG KMP CHO S (PATTERN)
// ==========================
vector<int> kmp(m + 1);
int k = 0;
kmp[1] = 0;

for (int i = 2; i <= m; i++) {
    while (k > 0 && s[i] != s[k + 1])
        k = kmp[k];
    if (s[i] == s[k + 1])
        k++;
    kmp[i] = k;
}

// ==========================
// CHẠY KMP TÌM S TRONG T
// ==========================
vector<int> match(n + 1);
k = 0;

for (int i = 1; i <= n; i++) {
    while (k > 0 && t[i] != s[k + 1])
        k = kmp[k];
    if (t[i] == s[k + 1])
        k++;
    match[i] = k;

    if (k == m) {
        // Vị trí xuất hiện: i - m + 1 (1-based)
        cout << "Match at: " << (i - m + 1) << "\n";
    }
}



```

## Đếm số lần xuất hiện

```cpp
int countOccurrences(string text, string pattern) {
    vector<int> positions = KMP(text, pattern);
    return positions.size();
}
```

## Tìm pattern đầu tiên

```cpp
int firstOccurrence(string text, string pattern) {
    vector<int> lps = computeLPS(pattern);
    int n = text.length(), m = pattern.length();
    int i = 0, j = 0;
    
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++; j++;
        }
        if (j == m) {
            return i - j;  // Trả về vị trí đầu tiên
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return -1;  // Không tìm thấy
}
```

## Tìm chu kỳ lặp của xâu

```cpp
int findPeriod(string s) {
    int n = s.length();
    vector<int> lps = computeLPS(s);
    
    int period = n - lps[n - 1];
    if (n % period == 0) {
        return period;  // Độ dài chu kỳ
    }
    return n;  // Không có chu kỳ
}
```

## Ứng dụng

### Tìm xâu con palindrome
```cpp
bool isPalindrome(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    return KMP(s, rev).size() > 0;
}
```

### Tìm tiền tố dài nhất là hậu tố
```cpp
int longestPrefixSuffix(string s) {
    vector<int> lps = computeLPS(s);
    return lps[s.length() - 1];
}
```

## Độ phức tạp
- **Thời gian**: O(n + m) với n là độ dài text, m là độ dài pattern
- **Không gian**: O(m) cho mảng LPS
