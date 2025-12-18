#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    string a, b;
    cin >> a >> b;
    ll b_num = stol(b);

    while(true) {
        cout << a << endl;
        int N = a.size();
        int M = b.size();
        cout << N << " " << M << endl;
        if (N < M or (N == M and a[0] < b[0])){
            break;
        }
        string a_sub;
        int k;
        if (a[N - M - 1] >= b[0]){
            a_sub = a.substr(N - M, b.size());
            k = N - M;
        } else {
            a_sub = a.substr(N - M - 1, b.size() + 1);
            k = N - M - 1;
        }
        cout << a_sub << " " << k << endl;
        ll a_num = stol(a_sub);
        ll h = a_num - b_num;
        a = a.substr(0, k) + to_string(h);
        cout << a << endl;
    }

    cout << a;

    return 0;
}