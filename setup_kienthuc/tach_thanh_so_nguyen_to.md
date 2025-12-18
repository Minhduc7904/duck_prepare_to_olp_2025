
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<pair<long long, int>> factorize(long long n) {
    vector<pair<long long, int>> result;

    // Tách số 2 trước
    if (n % 2 == 0) {
        int cnt = 0;
        while (n % 2 == 0) {
            n /= 2;
            cnt++;
        }
        result.push_back({2, cnt});
    }

    // Tách các số lẻ
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                n /= i;
                cnt++;
            }
            result.push_back({i, cnt});
        }
    }

    // Nếu còn lại 1 số nguyên tố lớn
    if (n > 1) {
        result.push_back({n, 1});
    }

    return result;
}

int main() {
    long long n;
    cin >> n;

    auto fac = factorize(n);

    for (auto &p : fac) {
        cout << p.first << "^" << p.second << " ";
    }
}
```