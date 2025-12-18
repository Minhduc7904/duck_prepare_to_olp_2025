#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


void prepare() {

}

void process() {
    
}

int main() {
    string S;
    int x, y, n;
    int c = 0;
    char pre_c;
    cin >> S;
    x = 0; y = 1;
    n = S.size();
    if (S.size() == 1) {
            cout << 1;
            return 0;
        }

    while (true) {
        if (x > n - 1 && y > n - 1) break;
        if (y > n - 1) {
            x += 1;
            y = x + 1;
            continue;
        }

        if (S[x] == S[y] && x + 1 == y) {
            c++;
            y++;
            x++;
            continue;
        }

        if (y == x + 1) {
            pre_c = S[y];
            y++;
            continue;
        }

        if (S[y] == pre_c) {
            y++;
            continue;
        }

        if (S[x] == S[y]) {
            c++;
        } 
        x++;
        y = x + 1;
    }
    cout << c << endl;
    return 0;
}