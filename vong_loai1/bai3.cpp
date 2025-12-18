#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    
    if (a.size() == 2) {
        cout << a[1] - a[0] << endl;
        return 0;
    }
    if (a.size() == 1) {
        cout << a[0] << endl;
        return 0;
    }
    while (true){
        
        int s = a.size();
        if (s == 1) {
            cout << a[0];
            break;
            
        }
        for (int i = s-2; i >= 0; i-= 2){
            
            a[i] = a[i+1] - a[i];
            a.erase(a.begin() + i + 1);
            // cout << a[i] << a[i+1] << endl; 
            // for (int x : a) cout << x << " ";
            // cout << endl;
        }
        sort(a.begin(), a.end());
    }

    return 0;
}