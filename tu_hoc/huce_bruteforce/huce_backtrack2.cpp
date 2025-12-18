#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<char>> S(8, vector<char>(8));
int result = 0;

void solve(vector<int> cols, vector<int> C1, vector<int> C2, int k = 0)
{
    if (k == 8) {
        result++;
        return;
    }
    
    for (int i = 0; i < 8; i++) {
        // cout << i << " " << k << endl;
        if (S[k][i] == '*') continue;
        if (C1[i - k + 7] == 1 or C2[i + k] == 1) continue;
        if (cols[i] == 1) continue;
        cols[i] = 1;
        C1[i - k + 7] = 1;
        C2[i + k] =  1; 

        solve(cols, C1, C2, k + 1);

        C1[i - k + 7] = 0;
        C2[i + k] =  0; 
        cols[i] = 0;
    }
}

int main()
{
    vector<int> cols(8, 0);
    vector<int> C1(15, 0);
    vector<int> C2(15, 0);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cin >> S[i][j];
        }
    }

    solve(cols, C1, C2);
    cout << result;
    return 0;
}