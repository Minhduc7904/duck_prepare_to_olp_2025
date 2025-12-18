# TỔ HỢP (COMBINATORICS)

## Tổ hợp nCk với Factorial

```cpp
const int MOD = 1e9 + 7;
const int N = 1e6;
int fact[N + 5], ifact[N + 5];

// Hàm lũy thừa nhanh
long long binpow(long long a, long long b) {
    long long ans = 1;
    while (b > 0){
        if (b % 2) ans = ans * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }
    return ans;
}

// Chuẩn bị
void prepare(){
    // Tính fact[]
    fact[0] = 1;
    for (int i = 1; i <= N; i++)
        fact[i] = 1LL * fact[i - 1] * i % MOD;

    // Tính ifact[]
    ifact[N] = binpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 1; i--)
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
}

// Hàm tính nCk
int C(int n, int k){
    if (k > n) return 0;
    return (1LL * fact[n] * ifact[k] % MOD) * ifact[n - k] % MOD;
}
long long nPk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return (fact[n] * inv_fact[n-k]) % MOD;
}
int main(){
    prepare();
    // Truy vấn
    int q; cin >> q;
    while (q--){
        int n, k; cin >> n >> k;
        cout << C(n, k) << '\n';
    }
}


```

## Pascal Triangle (cho n, k nhỏ)

```cpp
const int MAXN = 1005;
long long C[MAXN][MAXN];

void pascalTriangle() {
    for (int i = 0; i < MAXN; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
        }
    }
}
```

## Lucas Theorem (nCk mod p với p là SNT nhỏ)

```cpp
long long lucas(long long n, long long k, long long p) {
    if (k == 0) return 1;
    return (nCk(n % p, k % p) * lucas(n / p, k / p, p)) % p;
}
```

## Catalan Numbers

```cpp
// C(n) = (2n)! / ((n+1)! * n!)
// C(n) = C(0)*C(n-1) + C(1)*C(n-2) + ... + C(n-1)*C(0)
long long catalan[MAXN];

void computeCatalan(int n) {
    catalan[0] = catalan[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] = (catalan[i] + catalan[j] * catalan[i-1-j]) % MOD;
        }
    }
}

// Công thức trực tiếp
long long catalanDirect(int n) {
    return (nCk(2*n, n) * modInv(n + 1)) % MOD;
}
```

## Stirling Numbers

```cpp
// Stirling số loại 1: S1(n, k) = số hoán vị của n phần tử có k chu trình
long long S1[MAXN][MAXN];

void stirling1(int n) {
    S1[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            S1[i][j] = ((i-1) * S1[i-1][j] + S1[i-1][j-1]) % MOD;
        }
    }
}

// Stirling số loại 2: S2(n, k) = số cách chia n phần tử vào k tập không rỗng
long long S2[MAXN][MAXN];

void stirling2(int n) {
    S2[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            S2[i][j] = (j * S2[i-1][j] + S2[i-1][j-1]) % MOD;
        }
    }
}
```

## Bell Numbers (Số cách phân hoạch)

```cpp
long long bell[MAXN];

void computeBell(int n) {
    bell[0] = 1;
    for (int i = 1; i <= n; i++) {
        bell[i] = 0;
        for (int k = 0; k < i; k++) {
            bell[i] = (bell[i] + nCk(i-1, k) * bell[k]) % MOD;
        }
    }
}
```

## Fibonacci Numbers

```cpp
long long fib[MAXN];

void computeFib(int n) {
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <= n; i++) {
        fib[i] = (fib[i-1] + fib[i-2]) % MOD;
    }
}
```

## Derangement (Hoán vị không điểm bất động)

```cpp
// D(n) = n! * (1 - 1/1! + 1/2! - 1/3! + ... + (-1)^n/n!)
long long derangement[MAXN];

void computeDerangement(int n) {
    derangement[0] = 1;
    derangement[1] = 0;
    for (int i = 2; i <= n; i++) {
        derangement[i] = ((i - 1) * (derangement[i-1] + derangement[i-2])) % MOD;
    }
}
```

## Số cách chia n vật giống nhau vào k nhóm

```cpp
// Stars and bars: C(n+k-1, k-1)
long long distribute(int n, int k) {
    return nCk(n + k - 1, k - 1);
}

// Mỗi nhóm ít nhất 1 vật: C(n-1, k-1)
long long distributeNonEmpty(int n, int k) {
    if (n < k) return 0;
    return nCk(n - 1, k - 1);
}
```

## Số cách chọn k phần tử có lặp

```cpp
// Chọn k phần tử từ n loại (có thể lặp)
long long multisetCombination(int n, int k) {
    return nCk(n + k - 1, k);
}
```

## Inclusion-Exclusion Principle

```cpp
// Đếm số phần tử thỏa ít nhất 1 trong n điều kiện
long long inclusionExclusion(vector<long long>& sizes) {
    int n = sizes.size();
    long long result = 0;
    
    for (int mask = 1; mask < (1 << n); mask++) {
        long long intersection = LLONG_MAX;
        int bits = 0;
        
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                intersection = min(intersection, sizes[i]);
                bits++;
            }
        }
        
        if (bits % 2 == 1) {
            result += intersection;
        } else {
            result -= intersection;
        }
    }
    
    return result;
}
```

## Burnside's Lemma (Đếm với đối xứng)

```cpp
// Đếm số cách tô màu vòng tròn n vị trí với k màu
long long colorCircle(int n, int k) {
    long long sum = 0;
    
    for (int d = 1; d <= n; d++) {
        if (n % d == 0) {
            sum = (sum + power(k, d)) % MOD;
        }
    }
    
    return sum * modInv(n) % MOD;
}
```

## Polya Enumeration

```cpp
// Đếm số cách tô màu với các phép đối xứng
long long polyaCount(int n, int k, vector<int>& cycles) {
    long long sum = 0;
    
    for (int c : cycles) {
        sum = (sum + power(k, c)) % MOD;
    }
    
    return sum * modInv(cycles.size()) % MOD;
}
```

## Partition Function (Phân hoạch số)

```cpp
// p(n, k) = số cách viết n thành tổng của các số nguyên dương ≤ k
long long partition[MAXN][MAXN];

void computePartition(int n, int k) {
    partition[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            partition[i][j] = partition[i][j-1];
            if (i >= j) {
                partition[i][j] = (partition[i][j] + partition[i-j][j]) % MOD;
            }
        }
    }
}
```

## Số cách sắp xếp n người vào vòng tròn

```cpp
long long circularPermutation(int n) {
    if (n == 0) return 0;
    return fact[n-1];
}
```

## Độ phức tạp
- **nCk với precompute**: O(n) precompute, O(1) query
- **Pascal Triangle**: O(n²)
- **Lucas**: O(log_p(n))
- **Catalan**: O(n²) hoặc O(n) với công thức
