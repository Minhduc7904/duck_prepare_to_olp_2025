# QUY HOẠCH ĐỘNG - PALINDROME

## Kiểm tra xâu con palindrome

```cpp
const int MAXN = 1005;
bool isPalin[MAXN][MAXN];

void buildPalindrome(string s) {
    int n = s.length();
    
    // Mỗi ký tự đơn là palindrome
    for (int i = 0; i < n; i++) {
        isPalin[i][i] = true;
    }
    
    // Xây dựng cho các xâu con dài hơn
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                isPalin[i][j] = (len == 2) || isPalin[i+1][j-1];
            }
        }
    }
}
```

## Chia xâu thành ít palindrome nhất

```cpp
int minCut[MAXN];

void minPalindromeCut(string s) {
    int n = s.length();
    
    for (int i = 0; i < n; i++) {
        minCut[i] = i;  // Tối đa cần i cắt
        
        for (int j = 0; j <= i; j++) {
            if (isPalin[j][i]) {
                minCut[i] = (j == 0) ? 0 : min(minCut[i], minCut[j-1] + 1);
            }
        }
    }
}
```

## Số cách chia xâu thành palindrome

```cpp
const long long MOD = 1e9 + 7;
long long dp[MAXN];

long long countWays(string s) {
    int n = s.length();
    dp[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        dp[i] = 0;
        for (int j = 0; j < i; j++) {
            if (isPalin[j][i-1]) {
                dp[i] = (dp[i] + dp[j]) % MOD;
            }
        }
    }
    
    return dp[n];
}
```

## Xâu palindrome con dài nhất

```cpp
string longestPalindromicSubstring(string s) {
    int n = s.length();
    int maxLen = 0;
    int start = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (isPalin[i][j] && j - i + 1 > maxLen) {
                maxLen = j - i + 1;
                start = i;
            }
        }
    }
    
    return s.substr(start, maxLen);
}
```

## Thêm ít ký tự nhất để tạo palindrome

```cpp
int minInsertions(string s) {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            if (s[i] == s[j]) {
                dp[i][j] = dp[i+1][j-1];
            } else {
                dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;
            }
        }
    }
    
    return dp[0][n-1];
}
```

## Xâu palindrome subsequence dài nhất

```cpp
int longestPalindromicSubsequence(string s) {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            if (s[i] == s[j]) {
                dp[i][j] = dp[i+1][j-1] + 2;
            } else {
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[0][n-1];
}
```

## Đếm xâu palindrome con

```cpp
int countPalindromicSubstrings(string s) {
    int n = s.length();
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (isPalin[i][j]) {
                count++;
            }
        }
    }
    
    return count;
}
```

## Độ phức tạp
- **Build palindrome table**: O(n²)
- **Space**: O(n²)
