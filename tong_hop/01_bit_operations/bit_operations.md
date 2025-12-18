# CÁC PHÉP TOÁN VỀ BIT

## Các phép toán cơ bản

```cpp
// AND: a & b
// OR: a | b
// XOR: a ^ b
// NOT: ~a
// Shift left: a << k (nhân với 2^k)
// Shift right: a >> k (chia cho 2^k)

// Kiểm tra bit thứ i
bool checkBit(int n, int i) {
    return (n >> i) & 1;
}

// Bật bit thứ i
int setBit(int n, int i) {
    return n | (1 << i);
}

// Tắt bit thứ i
int clearBit(int n, int i) {
    return n & ~(1 << i);
}

// Đảo bit thứ i
int toggleBit(int n, int i) {
    return n ^ (1 << i);
}

// Đếm số bit 1
int countBits(int n) {
    return __builtin_popcount(n);
}

// Bit thấp nhất
int lowestBit(int n) {
    return n & (-n);
}
```

## Ứng dụng phổ biến

### Kiểm tra số chẵn/lẻ
```cpp
bool isOdd(int n) {
    return n & 1;
}
```

### Nhân/chia với lũy thừa 2
```cpp
int multiplyBy2Power(int n, int k) {
    return n << k;  // n * 2^k
}

int divideBy2Power(int n, int k) {
    return n >> k;  // n / 2^k
}
```

### Swap hai số không dùng biến phụ
```cpp
void swap(int &a, int &b) {
    a ^= b;
    b ^= a;
    a ^= b;
}
```

### Tìm số xuất hiện lẻ lần
```cpp
int findOddOccurrence(vector<int>& arr) {
    int result = 0;
    for (int x : arr) {
        result ^= x;
    }
    return result;
}
```
