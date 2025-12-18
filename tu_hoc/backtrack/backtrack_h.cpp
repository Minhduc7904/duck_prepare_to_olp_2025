#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

void backtrack(ll N, int &result, ll S = 1, int k = 0, int so_uoc = 1) {
    if (S > N || k == 20) return;

    result = max(result, so_uoc);

    int c = 0;
    while (S < N) {
        S *= 1ll * primes[k];
        c++;
        backtrack(N, result, S, k + 1, so_uoc * (c + 1));
    }
}


int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        ll N;
        cin >> N;
        int result = 1;
        backtrack(N, result);
        cout << result << endl;
    }

    return 0;
}