#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int base = 1000000;
const int digit = 6;
const int maxn = 160;

struct big_num {
    int a[31];

    big_num() { 
        memset(a, 0, sizeof(a)); 
    }
};

big_num a[maxn + 1];

void nhan(int i) {
    int mem = 0, x = 4 * i - 2;
    a[i].a[0] = a[i-1].a[0];
    for (int j = 1; j <= a[i].a[0]; j++) {
        int t = a[i-1].a[j] * x + mem;
        a[i].a[j] = t % base;
        mem = t / base;
    }

    if (mem > 0) {
        a[i].a[0]++;
        a[i].a[a[i].a[0]] = mem;
    }
}

void chia(int i) {
    int mem = 0, k = i + 1;
    big_num t;
    for (int j = a[i].a[0]; j >= 1; j--) {
        int x = a[i].a[j] + mem * base;
        if (x < k) mem = x;
        else {
            t.a[j] = x / k;
            mem = x % k;
        }
    }
    int j;
    for (j = a[i].a[0]; j >= 1; j--)
        if (t.a[j] > 0) break;
    a[i].a[0] = j;
    for (j = 1; j <= a[i].a[0]; j++)
        a[i].a[j] = t.a[j];
}

void set_up() {
    a[0].a[0] = 1;
    a[0].a[1] = 1;
    for (int i = 1; i <= maxn; i++) {
        nhan(i);
        chia(i);
    }
}

void print(big_num N) {
    for (int i = N.a[0]; i >= 1; i--) {
        if (i < N.a[0]) {
            cout << setfill('0') << setw(digit) << N.a[i];
        } else {
            cout << N.a[i];
        }
    }
    cout << endl;
}

int main() {
    set_up();

    while (true) {
        int n;
        cin >> n;
        if (n == -1) return 0;
        print(a[n]);
    }

    return 0;
}