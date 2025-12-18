# MANACHER (Tìm Palindrome dài nhất)

## Thuật toán Manacher

```cpp
string preprocess(string s) {
    string res = "@";
    for (char c : s) {
        res += "#";
        res += c;
    }
    res += "#$";
    return res;
}

int manacher(string s) {
    string t = preprocess(s);
    int n = t.length();
    vector<int> p(n);
    int center = 0, right = 0;
    int maxLen = 0;
    
    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;
        
        if (i < right) {
            p[i] = min(right - i, p[mirror]);
        }
        
        // Mở rộng palindrome tại i
        while (t[i + p[i] + 1] == t[i - p[i] - 1]) {
            p[i]++;
        }
        
        // Cập nhật center và right
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        
        maxLen = max(maxLen, p[i]);
    }
    
    return maxLen;
}
```

## Tìm tất cả palindrome

```cpp
struct PalindromeInfo {
    int center;
    int radius;
    int start;
    int length;
};

vector<PalindromeInfo> findAllPalindromes(string s) {
    string t = preprocess(s);
    int n = t.length();
    vector<int> p(n);
    vector<PalindromeInfo> palindromes;
    
    int center = 0, right = 0;
    
    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;
        
        if (i < right) {
            p[i] = min(right - i, p[mirror]);
        }
        
        while (t[i + p[i] + 1] == t[i - p[i] - 1]) {
            p[i]++;
        }
        
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        
        // Lưu palindrome
        if (p[i] > 0) {
            int start = (i - p[i]) / 2;
            int length = p[i];
            palindromes.push_back({i, p[i], start, length});
        }
    }
    
    return palindromes;
}
```

## Tìm palindrome dài nhất và vị trí

```cpp
pair<int, int> longestPalindrome(string s) {
    string t = preprocess(s);
    int n = t.length();
    vector<int> p(n);
    int center = 0, right = 0;
    
    int maxLen = 0;
    int maxCenter = 0;
    
    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;
        
        if (i < right) {
            p[i] = min(right - i, p[mirror]);
        }
        
        while (t[i + p[i] + 1] == t[i - p[i] - 1]) {
            p[i]++;
        }
        
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        
        if (p[i] > maxLen) {
            maxLen = p[i];
            maxCenter = i;
        }
    }
    
    // Tính vị trí bắt đầu trong xâu gốc
    int start = (maxCenter - maxLen) / 2;
    return {start, maxLen};
}
```

## Đếm số palindrome con

```cpp
long long countPalindromes(string s) {
    string t = preprocess(s);
    int n = t.length();
    vector<int> p(n);
    int center = 0, right = 0;
    long long count = 0;
    
    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;
        
        if (i < right) {
            p[i] = min(right - i, p[mirror]);
        }
        
        while (t[i + p[i] + 1] == t[i - p[i] - 1]) {
            p[i]++;
        }
        
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        
        // Mỗi palindrome có bán kính r đóng góp (r+1)/2 palindrome
        count += (p[i] + 1) / 2;
    }
    
    return count;
}
```

## Kiểm tra palindrome cho mọi xâu con

```cpp
class PalindromeChecker {
private:
    vector<vector<bool>> isPalin;
    
public:
    PalindromeChecker(string s) {
        int n = s.length();
        isPalin.assign(n, vector<bool>(n, false));
        
        // Mỗi ký tự đơn là palindrome
        for (int i = 0; i < n; i++) {
            isPalin[i][i] = true;
        }
        
        // Xây dựng bảng DP
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    isPalin[i][j] = (len == 2) || isPalin[i+1][j-1];
                }
            }
        }
    }
    
    bool check(int l, int r) {
        return isPalin[l][r];
    }
};
```

## Ứng dụng

### Chia xâu thành ít palindrome nhất
```cpp
int minCut(string s) {
    int n = s.length();
    vector<vector<bool>> isPalin(n, vector<bool>(n, false));
    vector<int> dp(n, INT_MAX);
    
    // Xây dựng bảng palindrome
    for (int i = 0; i < n; i++) {
        isPalin[i][i] = true;
    }
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                isPalin[i][j] = (len == 2) || isPalin[i+1][j-1];
            }
        }
    }
    
    // DP để tìm số cắt tối thiểu
    for (int i = 0; i < n; i++) {
        if (isPalin[0][i]) {
            dp[i] = 0;
        } else {
            for (int j = 0; j < i; j++) {
                if (isPalin[j+1][i]) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }
    }
    
    return dp[n-1];
}
```

## Độ phức tạp
- **Thời gian**: O(n) - tuyến tính
- **Không gian**: O(n)
- Nhanh hơn nhiều so với DP O(n²)
