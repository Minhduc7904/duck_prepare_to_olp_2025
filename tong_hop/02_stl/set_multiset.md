# SET & MULTISET

## Set (Tập hợp không trùng lặp)

```cpp
set<int> s;

// Thêm phần tử
s.insert(x);

// Xóa phần tử
s.erase(x);  // Xóa tất cả x

// Tìm kiếm
auto it = s.find(x);
if (it != s.end()) {
    // Tìm thấy
}

// Lower bound / Upper bound
auto it1 = s.lower_bound(x);  // >= x
auto it2 = s.upper_bound(x);  // > x

// Duyệt qua các phần tử
for (int x : s) {
    cout << x << " ";
}

// Kích thước
int size = s.size();

// Kiểm tra rỗng
if (s.empty()) { /* ... */ }

// Xóa tất cả
s.clear();
```

## Multiset (Tập hợp có trùng lặp)

```cpp
multiset<int> ms;

// Thêm phần tử
ms.insert(x);

// Xóa 1 phần tử x
ms.erase(ms.find(x));

// Xóa tất cả x
ms.erase(x);

// Đếm số lần xuất hiện
int count = ms.count(x);

// Lower bound / Upper bound
auto it1 = ms.lower_bound(x);  // >= x
auto it2 = ms.upper_bound(x);  // > x
```

## Ứng dụng

### Duy trì k phần tử lớn nhất
```cpp
multiset<int> topK;
int k;

void addElement(int x) {
    topK.insert(x);
    if (topK.size() > k) {
        topK.erase(topK.begin());  // Xóa phần tử nhỏ nhất
    }
}
```

### Tìm median động
```cpp
multiset<int> lower, upper;

void insert(int x) {
    if (lower.empty() || x <= *lower.rbegin()) {
        lower.insert(x);
    } else {
        upper.insert(x);
    }
    
    // Cân bằng
    if (lower.size() > upper.size() + 1) {
        upper.insert(*lower.rbegin());
        lower.erase(prev(lower.end()));
    } else if (upper.size() > lower.size()) {
        lower.insert(*upper.begin());
        upper.erase(upper.begin());
    }
}

double getMedian() {
    if (lower.size() == upper.size()) {
        return (*lower.rbegin() + *upper.begin()) / 2.0;
    }
    return *lower.rbegin();
}
```
