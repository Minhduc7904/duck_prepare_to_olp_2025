# LAZY PROPAGATION

## Lazy Propagation (Range Update + Range Query)

```cpp
struct SegTree {
    int n;
    vector<ll> st, a, lazy;

    SegTree(int _n) {
        n = _n;
        st.assign(n * 4 + 5, 0);
        a.assign(n + 1, 0);
        lazy.assign(n * 4 + 5, 0);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            st[id] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id] = max(st[2 * id], st[2 * id + 1]);
    }

    void push(int id) {
        if (lazy[id] != 0) {
            st[id * 2] += lazy[id];
            st[id * 2 + 1] += lazy[id];
            lazy[id * 2] += lazy[id];
            lazy[id * 2 + 1] += lazy[id];
            lazy[id] = 0;
        }
    }

    void update(int id, int l, int r, int x, int y, ll val) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            st[id] += val;
            lazy[id] += val;
            return;
        }
        push(id);
        int mid = (l + r) / 2;
        update(id * 2, l, mid, x, y, val);
        update(id * 2 + 1, mid + 1, r, x, y, val);
        st[id] = max(st[id * 2], st[id * 2 + 1]);
    }

    ll get(int id, int l, int r, int u, int v) {
        if (u > r || v < l) return LLONG_MIN;
        if (u <= l && r <= v) return st[id];
        push(id);
        int mid = (l + r) / 2;
        return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
    }
};
```

## Lazy Propagation (Set Range)

```cpp
const int MAXN = 1e5 + 5;
long long st[4 * MAXN];
long long lazy[4 * MAXN];
bool hasLazy[4 * MAXN];

void push(int id, int l, int r) {
    if (!hasLazy[id]) return;
    
    st[id] = lazy[id] * (r - l + 1);
    
    if (l != r) {
        lazy[2*id] = lazy[id];
        lazy[2*id+1] = lazy[id];
        hasLazy[2*id] = hasLazy[2*id+1] = true;
    }
    
    hasLazy[id] = false;
}

void setRange(int id, int l, int r, int u, int v, long long val) {
    push(id, l, r);
    
    if (v < l || u > r) return;
    
    if (u <= l && r <= v) {
        lazy[id] = val;
        hasLazy[id] = true;
        push(id, l, r);
        return;
    }
    
    int mid = (l + r) / 2;
    setRange(2*id, l, mid, u, v, val);
    setRange(2*id+1, mid+1, r, u, v, val);
    
    push(2*id, l, mid);
    push(2*id+1, mid+1, r);
    
    st[id] = st[2*id] + st[2*id+1];
}
```

## Lazy Propagation với nhiều loại operation

```cpp
struct LazyNode {
    long long addVal;
    long long setVal;
    bool hasSet;
    
    LazyNode() : addVal(0), setVal(0), hasSet(false) {}
};

LazyNode lazy[4 * MAXN];

void push(int id, int l, int r) {
    if (lazy[id].hasSet) {
        st[id] = lazy[id].setVal * (r - l + 1);
        if (l != r) {
            lazy[2*id].setVal = lazy[id].setVal;
            lazy[2*id+1].setVal = lazy[id].setVal;
            lazy[2*id].hasSet = lazy[2*id+1].hasSet = true;
            lazy[2*id].addVal = lazy[2*id+1].addVal = 0;
        }
        lazy[id].hasSet = false;
    }
    
    if (lazy[id].addVal != 0) {
        st[id] += lazy[id].addVal * (r - l + 1);
        if (l != r) {
            lazy[2*id].addVal += lazy[id].addVal;
            lazy[2*id+1].addVal += lazy[id].addVal;
        }
        lazy[id].addVal = 0;
    }
}
```

## Ví dụ sử dụng

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
        
        if (type == 1) {  // Range update
            int l, r;
            long long val;
            cin >> l >> r >> val;
            updateRange(1, 1, n, l, r, val);
        } else {  // Range query
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << "\n";
        }
    }
    
    return 0;
}
```
