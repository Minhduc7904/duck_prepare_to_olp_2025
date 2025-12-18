# MODULO & NUMBER THEORY

## Setup Modulo cơ bản

```cpp
const long long MOD = 1e9 + 7;

long long add(long long a, long long b) {
    return (a + b) % MOD;
}

long long sub(long long a, long long b) {
    return ((a - b) % MOD + MOD) % MOD;
}

long long mul(long long a, long long b) {
    return (a * b) % MOD;
}
```

## Lũy thừa modulo

```cpp
long long power(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    
    while (b > 0) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    
    return res;
}

long long powerIterative(long long a, long long b) {
    long long result = 1;
    a %= MOD;
    
    for (; b; b >>= 1) {
        if (b & 1) result = (result * a) % MOD;
        a = (a * a) % MOD;
    }
    
    return result;
}
```

## Nghịch đảo modulo (Modular Inverse)

```cpp
// Fermat's little theorem (MOD phải là số nguyên tố)
long long modInv(long long a) {
    return power(a, MOD - 2);
}

// Extended GCD
long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

long long modInvGCD(long long a) {
    long long x, y;
    extGCD(a, MOD, x, y);
    return (x % MOD + MOD) % MOD;
}
```

## Chia modulo

```cpp
long long divide(long long a, long long b) {
    return mul(a, modInv(b));
}
```

## GCD & LCM

```cpp
long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

// Recursive GCD
long long gcdRecursive(long long a, long long b) {
    return b ? gcdRecursive(b, a % b) : a;
}
```

## Extended GCD

```cpp
long long extendedGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

// Tìm x, y sao cho ax + by = gcd(a, b)
```

## Phương trình Diophantine tuyến tính

```cpp
// Giải ax + by = c
bool solveDiophantine(long long a, long long b, long long c, 
                      long long &x, long long &y) {
    long long g = extendedGCD(a, b, x, y);
    
    if (c % g != 0) return false;
    
    x *= c / g;
    y *= c / g;
    return true;
}
```

## Chinese Remainder Theorem (CRT)

```cpp
// Giải hệ: x ≡ a[i] (mod m[i])
long long CRT(vector<long long>& a, vector<long long>& m) {
    int n = a.size();
    long long M = 1;
    
    for (int i = 0; i < n; i++) {
        M *= m[i];
    }
    
    long long result = 0;
    
    for (int i = 0; i < n; i++) {
        long long Mi = M / m[i];
        long long yi = modInv(Mi % m[i]);  // Nghịch đảo của Mi theo mod m[i]
        result = (result + a[i] * Mi % M * yi % M) % M;
    }
    
    return result;
}
```

## Euler's Totient Function (φ)

```cpp
// Đếm số nguyên dương ≤ n nguyên tố cùng nhau với n
long long phi(long long n) {
    long long result = n;
    
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            result -= result / i;
        }
    }
    
    if (n > 1) {
        result -= result / n;
    }
    
    return result;
}

// Tính φ cho tất cả số từ 1 đến n
vector<int> phiTable(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++) phi[i] = i;
    
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {  // i là số nguyên tố
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    
    return phi;
}
```

## Discrete Logarithm (Baby-step Giant-step)

```cpp
// Tìm x sao cho a^x ≡ b (mod m)
long long discreteLog(long long a, long long b, long long m) {
    long long n = sqrt(m) + 1;
    
    map<long long, long long> vals;
    long long an = 1;
    
    for (long long p = 1; p <= n; p++) {
        an = (an * a) % m;
        vals[an] = p;
    }
    
    long long cur = b;
    for (long long q = 0; q <= n; q++) {
        if (vals.count(cur)) {
            long long ans = vals[cur] * n - q;
            if (ans < m) return ans;
        }
        cur = (cur * a) % m;
    }
    
    return -1;  // Không tìm thấy
}
```

## Fibonacci Modulo

```cpp
pair<long long, long long> fib(long long n) {
    if (n == 0) return {0, 1};
    
    auto [a, b] = fib(n >> 1);
    long long c = (a * ((2 * b - a + MOD) % MOD)) % MOD;
    long long d = (a * a + b * b) % MOD;
    
    if (n & 1) {
        return {d, (c + d) % MOD};
    } else {
        return {c, d};
    }
}

long long fibMod(long long n) {
    return fib(n).first;
}
```

## Matrix Exponentiation

```cpp
struct Matrix {
    long long a[2][2];
    
    Matrix operator * (const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                result.a[i][j] = 0;
                for (int k = 0; k < 2; k++) {
                    result.a[i][j] = (result.a[i][j] + a[i][k] * other.a[k][j]) % MOD;
                }
            }
        }
        return result;
    }
};

Matrix matrixPower(Matrix base, long long n) {
    Matrix result;
    result.a[0][0] = result.a[1][1] = 1;
    result.a[0][1] = result.a[1][0] = 0;
    
    while (n > 0) {
        if (n & 1) result = result * base;
        base = base * base;
        n >>= 1;
    }
    
    return result;
}

// Fibonacci bằng matrix
long long fibMatrix(long long n) {
    if (n == 0) return 0;
    
    Matrix base;
    base.a[0][0] = base.a[0][1] = base.a[1][0] = 1;
    base.a[1][1] = 0;
    
    Matrix result = matrixPower(base, n);
    return result.a[0][1];
}
```

## Độ phức tạp
- **GCD**: O(log min(a, b))
- **Power**: O(log b)
- **Phi**: O(√n)
- **Matrix Power**: O(k³ log n) với k là kích thước ma trận
