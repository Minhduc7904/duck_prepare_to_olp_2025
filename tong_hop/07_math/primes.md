# SỐ NGUYÊN TỐ (PRIME NUMBERS)

## Sàng Eratosthenes cơ bản

```cpp
const int MAXN = 1e6 + 5;
bool isPrime[MAXN];
vector<int> primes;

void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        isPrime[i] = true;
    }    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j *= i) {
                isPrime[j] = false;
            }
        }
    }
    
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
}
```

## Sàng tuyến tính (Linear Sieve)

```cpp
const int N = 1000000;
int minPrime[N + 1];
vector<int> primes;

void linear_sieve() {
    for (int i = 2; i <= N; i++) {
        if (minPrime[i] == 0) {
            minPrime[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > minPrime[i] || 1LL * p * i > N) break;
            minPrime[p * i] = p;
        }
    }
}

```

## Kiểm tra số nguyên tố (Trial Division)

```cpp
bool isPrimeCheck(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    
    return true;
}
```

## Miller-Rabin (Kiểm tra nhanh)

```cpp
long long mulmod(long long a, long long b, long long mod) {
    return (__int128)a * b % mod;
}

long long powerMod(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = mulmod(res, a, mod);
        a = mulmod(a, a, mod);
        b >>= 1;
    }
    return res;
}

bool millerRabin(long long n, long long a) {
    if (n % a == 0) return n == a;
    
    long long d = n - 1;
    int r = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    
    long long x = powerMod(a, d, n);
    if (x == 1 || x == n - 1) return true;
    
    for (int i = 0; i < r - 1; i++) {
        x = mulmod(x, x, n);
        if (x == n - 1) return true;
    }
    
    return false;
}

bool isPrimeMR(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    
    // Các witness cho n < 2^64
    vector<long long> witnesses = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    
    for (long long a : witnesses) {
        if (n == a) return true;
        if (!millerRabin(n, a)) return false;
    }
    
    return true;
}
```

## Phân tích thừa số nguyên tố

```cpp
vector<pair<int, int>> primeFactorization(int n) {
    vector<pair<int, int>> factors;
    
    for (int i = 2; i * i <= n; i++) {
        int cnt = 0;
        while (n % i == 0) {
            cnt++;
            n /= i;
        }
        if (cnt > 0) {
            factors.push_back({i, cnt});
        }
    }
    
    if (n > 1) {
        factors.push_back({n, 1});
    }
    
    return factors;
}

// Với sàng tuyến tính
vector<pair<int, int>> factorize(int n) {
    vector<pair<int, int>> factors;
    
    while (n > 1) {
        int p = minPrimeFactor[n];
        int cnt = 0;
        
        while (n % p == 0) {
            cnt++;
            n /= p;
        }
        
        factors.push_back({p, cnt});
    }
    
    return factors;
}
```

## Pollard's Rho (Phân tích số lớn)

```cpp
long long pollardRho(long long n) {
    if (n % 2 == 0) return 2;
    
    long long x = rand() % (n - 2) + 2;
    long long y = x;
    long long c = rand() % (n - 1) + 1;
    long long d = 1;
    
    while (d == 1) {
        x = (mulmod(x, x, n) + c) % n;
        y = (mulmod(y, y, n) + c) % n;
        y = (mulmod(y, y, n) + c) % n;
        d = __gcd(abs(x - y), n);
        
        if (d == n) break;
    }
    
    return d;
}

vector<long long> factorize(long long n) {
    if (n == 1) return {};
    
    if (isPrimeMR(n)) return {n};
    
    long long divisor = pollardRho(n);
    auto left = factorize(divisor);
    auto right = factorize(n / divisor);
    
    left.insert(left.end(), right.begin(), right.end());
    return left;
}
```

## Đếm ước số

```cpp
int countDivisors(int n) {
    int count = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            count++;
            if (i * i != n) count++;
        }
    }
    return count;
}

// Từ phân tích thừa số: n = p1^a1 * p2^a2 * ... * pk^ak
// Số ước = (a1+1) * (a2+1) * ... * (ak+1)
int countDivisorsFromFactors(vector<pair<int, int>>& factors) {
    int count = 1;
    for (auto [p, a] : factors) {
        count *= (a + 1);
    }
    return count;
}
```

## Tổng ước số

```cpp
long long sumDivisors(int n) {
    long long sum = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) sum += n / i;
        }
    }
    return sum;
}

// Từ phân tích: n = p1^a1 * p2^a2 * ... * pk^ak
// Tổng ước = (1 + p1 + p1^2 + ... + p1^a1) * ... * (1 + pk + ... + pk^ak)
long long sumDivisorsFromFactors(vector<pair<int, int>>& factors) {
    long long sum = 1;
    
    for (auto [p, a] : factors) {
        long long partialSum = 0;
        long long power = 1;
        
        for (int i = 0; i <= a; i++) {
            partialSum += power;
            power *= p;
        }
        
        sum *= partialSum;
    }
    
    return sum;
}
```

## Số nguyên tố thứ k

```cpp
// Ước lượng số nguyên tố thứ k
long long estimatePrime(int k) {
    if (k < 6) return primes[k-1];
    return k * (log(k) + log(log(k)));
}
```

## Đếm số nguyên tố ≤ n

```cpp
int countPrimes(int n) {
    if (n < 2) return 0;
    sieve(n);
    return primes.size();
}
```

## Số nguyên tố liên tiếp

```cpp
// Tìm khoảng cách giữa 2 số nguyên tố liên tiếp
vector<int> primesGaps() {
    vector<int> gaps;
    for (int i = 1; i < primes.size(); i++) {
        gaps.push_back(primes[i] - primes[i-1]);
    }
    return gaps;
}
```

## Độ phức tạp
- **Sàng Eratosthenes**: O(n log log n)
- **Sàng tuyến tính**: O(n)
- **Trial Division**: O(√n)
- **Miller-Rabin**: O(k log³ n), k là số witness
- **Pollard's Rho**: O(n^(1/4))
