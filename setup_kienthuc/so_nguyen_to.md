
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<bool> isPrime;
vector<int> primes;

void linearSieve(int n) {
    isPrime.assign(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) primes.push_back(i);

        for (int p : primes) {
            long long x = 1LL * p * i;
            if (x > n) break;

            isPrime[x] = false;

            if (i % p == 0) break; 
        }
    }
}

int main() {
    int N = 1000000;
    linearSieve(N);

    // Ví dụ check 97
    cout << (isPrime[97] ? "Prime" : "Not prime") << endl;

    return 0;
}
```
