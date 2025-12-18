#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void input_array(vector<int>& arr) {
    for (auto &x : arr) {
        cin >> x;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    vector<int> b(n);

    input_array(a);
    input_array(b);

    int c = 0;
    for (int i : a){
        ll y = x - i;
        c += count(b.begin(), b.end(), y);
    }

    cout << c << "\n";
    return 0;
}