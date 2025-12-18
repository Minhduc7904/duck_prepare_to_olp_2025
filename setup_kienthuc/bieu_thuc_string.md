
Giả sử:

* `sign[i]`: 0 = `+`, 1 = `-`, 2 = `*`
* `a[i]` là mảng 1-index
* `n`, `modulo` là biến global / truyền vào

```cpp
int compute(const vector<int>& sign, const vector<long long>& a, int n, int modulo) {
    stack<pair<int, long long>> st;
    st.push({sign[1], a[1]});

    for (int i = 2; i <= n; i++) {
        if (sign[i] == 2) { // '*'
            // biểu thức đúng thì chắc chắn st không rỗng
            pair<int, long long> u = st.top();
            st.pop();

            u.second = (u.second * a[i]) % modulo;
            st.push(u);
        } else {
            st.push({sign[i], a[i]}); // '+' hoặc '-'
        }
    }

    long long finalSum = 0;
    while (!st.empty()) {
        pair<int, long long> u = st.top();
        st.pop();

        if (u.first == 0) { // '+'
            finalSum = (finalSum + u.second) % modulo;
        } else {            // '-'
            finalSum = (finalSum - u.second) % modulo;
        }
    }

    // chuẩn hoá về [0, modulo-1]
    finalSum %= modulo;
    if (finalSum < 0) finalSum += modulo;

    return (int)finalSum;
}
```
