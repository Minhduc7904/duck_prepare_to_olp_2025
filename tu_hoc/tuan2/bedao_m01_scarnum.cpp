#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<ll> result;

void generateNumbers(int limit)
{
    queue<ll> q;
    q.push(2);
    q.push(5);

    while (!q.empty())
    {
        ll num = q.front();
        q.pop();

        if (num > limit)
            break;

        result.push_back(num);
        q.push(num * 10 + 2);
        q.push(num * 10 + 5);
    }
}

int main()
{
    int m;
    cin >> m;
    generateNumbers(1e6 + 1);

    // cout << endl;

    vector<bool> S(1e6 + 1, false);

    for (auto x : result)
    {
        int a = x;
        while (x <= 1e6)
        {
            
            S[x] = true;
            x += a;
        }
    }

    // for (int i = 0; i <= 100; i++)
    //     cout << S[i] << " " << i << endl;

    while (m--)
    {
        int N;
        cin >> N;
        if (N % 2 == 0 || N % 5 == 0) {
            cout << "YES" << endl;
            continue;
        }
        if (S[N])
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}