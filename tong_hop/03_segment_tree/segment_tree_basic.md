# SEGMENT TREE CỞ BẢN

## Segment Tree (Sum Query)

```cpp
struct SegTree {
    int n;
    vector<ll> st, a;
    SegTree(int _n) {
        n = _n;
        st.assign(n * 4 + 5, 0);
        a.assign(n + 1, 0);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            st[id] = a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id] = st[id * 2] + st[id * 2 + 1];
    }

    void update(int id, int l, int r, int pos, ll val) {
        if (l == r) {
            st[id] = val;
            a[pos] = val;
            return;
        }

        int mid = (l + r) / 2;
        if (pos <= val) update(id * 2, l, mid, pos, val);
        else update(id * 2 + 1, mid + 1, r, pos, val);
        st[id] = st[id * 2] + st[id * 2 + 1];
    }

    void get(int id, int l, int r, int u, int v) {
        if (u > r || v < l) return 0;
        if (u <= l && r <= v) return st[id];

        int mid = (l + r) / 2;
        return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
    }
};
```

## Segment Tree (Min/Max Query)

```cpp
const int INF = 1e9;
int st[4 * MAXN];

void buildMin(int id, int l, int r) {
    if (l == r) {
        st[id] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    buildMin(2*id, l, mid);
    buildMin(2*id+1, mid+1, r);
    st[id] = min(st[2*id], st[2*id+1]);
}

void updateMin(int id, int l, int r, int pos, int val) {
    if (pos < l || pos > r) return;
    if (l == r) {
        st[id] = val;
        return;
    }
    int mid = (l + r) / 2;
    updateMin(2*id, l, mid, pos, val);
    updateMin(2*id+1, mid+1, r, pos, val);
    st[id] = min(st[2*id], st[2*id+1]);
}

int queryMin(int id, int l, int r, int u, int v) {
    if (v < l || u > r) return INF;
    if (u <= l && r <= v) return st[id];
    int mid = (l + r) / 2;
    return min(queryMin(2*id, l, mid, u, v), 
               queryMin(2*id+1, mid+1, r, u, v));
}
```

## Segment Tree (GCD Query)

```cpp
long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

long long st[4 * MAXN];

void buildGCD(int id, int l, int r) {
    if (l == r) {
        st[id] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    buildGCD(2*id, l, mid);
    buildGCD(2*id+1, mid+1, r);
    st[id] = gcd(st[2*id], st[2*id+1]);
}

long long queryGCD(int id, int l, int r, int u, int v) {
    if (v < l || u > r) return 0;
    if (u <= l && r <= v) return st[id];
    int mid = (l + r) / 2;
    return gcd(queryGCD(2*id, l, mid, u, v), 
               queryGCD(2*id+1, mid+1, r, u, v));
}
```

## Cách sử dụng

```cpp
int main() {
    int n, q;
    cin >> n >> q;
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    build(1, 1, n);
    
    while (q--) {
        int type;
        cin >> type;
        
        if (type == 1) {  // Update
            int pos, val;
            cin >> pos >> val;
            update(1, 1, n, pos, val);
        } else {  // Query
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << "\n";
        }
    }
    
    return 0;
}
```
