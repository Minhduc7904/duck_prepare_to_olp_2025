# ⭐ **Sử dụng công thức truy hồi**

$$
C_n^k =
\begin{cases}
1 & \text{nếu } k=0 \text{ và } n\ge 0 \\
0 & \text{nếu } k>n \\
C_{n-1}^{k-1} + C_{n-1}^k & \text{trong các trường hợp còn lại}
\end{cases}
$$

Với công thức truy hồi này, ta sẽ sử dụng một mảng hai chiều `C[n][k]` để tính ( C_n^k ).

---

# ⭐ **Code C++ minh họa**

```cpp
for (int i = 0; i <= n; i++){
    C[i][0] = 1;
    for (int k = 1; k <= i; k++){
        C[i][k] = C[i - 1][k - 1] + C[i - 1][k];
    }
}
```

---

# ⭐ **Độ phức tạp**

* **Không gian:** ( O(n^2) )
* **Thời gian:**

  * Tiền xử lý: ( O(n^2) )
  * Truy vấn: ( O(1) )

---

# ## 📌 **Sử dụng công thức truy hồi**

Ở đây, ta sẽ sử dụng công thức truy hồi ở trên và thay đổi một chút:

$$
C_n^k = (C_{n-1}^{k-1} + C_{n-1}^k) \bmod M
$$

---

## 📌 **Code C++ minh họa**

```cpp
for (int i = 0; i <= n; i++){
    C[i][0] = 1 % MOD;
    for (int k = 1; k <= i; k++){
        C[i][k] = (C[i - 1][k - 1] + C[i - 1][k]) % MOD;
    }
}
```

---

## 📌 **Độ phức tạp**

- **Không gian:**  
  $O(n^2)$

- **Thời gian:**
  - Tiền xử lý: $O(n^2)$
  - Truy vấn: $O(1)$

---

# ## 💡 Ý tưởng:

Ta viết lại:

$$
C_n^k = n! \times (k!)^{-1} \times ((n-k)!)^{-1} \mod M
$$

---

### ✔ Ta sử dụng hai mảng:

* `fact[i]` để lưu ( i! \mod M )
* `ifact[i]` để lưu ( (i!)^{-1} \mod M )

Sau đó dùng công thức (dựa trên định lý Fermat nhỏ):

$$
(i!)^{-1} = (i!)^{M-2} \mod M
$$

Chú ý rằng:

$$
fact[i] = 0 \pmod{M} \quad \forall i \ge M
$$

nên ta chỉ tính `fact[i]` và `ifact[i]` với:

$$
0 \le i \le M - 1
$$

---

### ✔ Tính mảng `fact[i]` như sau:

$$
\begin{cases}
fact[0] = 1 \
fact[i] = (fact[i-1] \times i)\ \bmod M \quad \text{nếu } 1 \le i \le n
\end{cases}
$$

---

### ✔ Tính `ifact[n]` bằng lũy thừa nhanh:

$$
ifact[n] = (fact[n])^{M-2} \mod M
$$

Độ phức tạp: **O(log M)**.

---

### ✔ Sau đó tính tiếp `ifact[i]` bằng:

$$
\begin{cases}
ifact[n] = (fact[n])^{M-2} \mod M \
ifact[i-1] = ifact[i] \times i \mod M \quad \text{nếu } 1 \le i \le n
\end{cases}
$$

---

### ✔ Cuối cùng:

$$
C_n^k = fact[n] \times ifact[k] \times ifact[n-k] \mod M
$$

---

# ## ⭐ Code C++ minh họa

```cpp
const int MOD = 1e9 + 7;
const int N = 1e6;
int fact[N + 5], ifact[N + 5];

// Hàm lũy thừa nhanh
long long binpow(long long a, long long b) {
    long long ans = 1;
    while (b > 0){
        if (b % 2) ans = ans * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }
    return ans;
}

// Chuẩn bị
void prepare(){
    // Tính fact[]
    fact[0] = 1;
    for (int i = 1; i <= N; i++)
        fact[i] = 1LL * fact[i - 1] * i % MOD;

    // Tính ifact[]
    ifact[N] = binpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 1; i--)
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
}

// Hàm tính nCk
int C(int n, int k){
    if (k > n) return 0;
    return (1LL * fact[n] * ifact[k] % MOD) * ifact[n - k] % MOD;
}

int main(){
    prepare();
    // Truy vấn
    int q; cin >> q;
    while (q--){
        int n, k; cin >> n >> k;
        cout << C(n, k) << '\n';
    }
}
```

