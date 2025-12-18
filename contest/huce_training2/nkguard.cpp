#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int n, m;
int height[701][701];
bool visited[701][701];
#define fi first
#define se second
int result = 0;

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void BFS(pair<int, int> s)
{
    if (visited[s.fi][s.se])
        return;
    visited[s.fi][s.se] = true;
    int H = height[s.fi][s.se];

    queue<pair<int, int>> q;
    q.push(s);

    bool hasHigher = false;

    while (!q.empty())
    {
        auto O = q.front();
        q.pop();
        int x = O.fi;
        int y = O.se;

        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
            
            if (height[nx][ny] > H) {
                hasHigher = true;
            }

            if (!visited[nx][ny] && height[nx][ny] == H) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    if (!hasHigher)
        result++;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> height[i][j];

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // cout << i << j;
            BFS({i, j});
        }
        // cout << endl;
    }

    cout << result << endl;
    return 0;
}