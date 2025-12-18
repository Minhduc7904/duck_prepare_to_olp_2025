# STACK - NGĂN XẾP

## 📚 KHÁI NIỆM

**Stack** (ngăn xếp) là cấu trúc dữ liệu **LIFO** (Last In First Out - vào sau ra trước), giống như chồng đĩa.

```cpp
#include <stack>
stack<int> st;
```

---

## 🔧 CÁC THAO TÁC CƠ BẢN

### 1. Thêm phần tử (Push)
```cpp
stack<int> st;
st.push(10);
st.push(20);
st.push(30);
// Stack: [10, 20, 30] (30 ở đỉnh)
```

### 2. Lấy phần tử đỉnh (Top)
```cpp
int top_element = st.top();  // 30
```

### 3. Xóa phần tử đỉnh (Pop)
```cpp
st.pop();  // Xóa 30
// Stack: [10, 20]
```

### 4. Kiểm tra rỗng
```cpp
if (st.empty()) {
    cout << "Stack rong";
}
```

### 5. Kích thước
```cpp
int size = st.size();  // 2
```

---

## 📊 BẢNG TÓM TẮT THAO TÁC

| Thao tác | Code | Độ phức tạp | Mô tả |
|----------|------|-------------|-------|
| **Thêm** | `st.push(x)` | O(1) | Thêm x vào đỉnh |
| **Xóa đỉnh** | `st.pop()` | O(1) | Xóa phần tử đỉnh |
| **Lấy đỉnh** | `st.top()` | O(1) | Trả về phần tử đỉnh |
| **Kiểm tra rỗng** | `st.empty()` | O(1) | true nếu rỗng |
| **Kích thước** | `st.size()` | O(1) | Số phần tử |

---

## 💡 ỨNG DỤNG STACK

### 1. Kiểm tra dấu ngoặc hợp lệ
```cpp
bool isValid(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            st.pop();
            
            if (c == ')' && top != '(') return false;
            if (c == ']' && top != '[') return false;
            if (c == '}' && top != '{') return false;
        }
    }
    return st.empty();
}

// Test
cout << isValid("()[]{}");     // true
cout << isValid("([)]");       // false
cout << isValid("{[()]}");     // true
```

### 2. Tính giá trị biểu thức hậu tố (Postfix)
```cpp
// Ví dụ: "2 3 + 5 *" = (2 + 3) * 5 = 25
int evaluatePostfix(string s) {
    stack<int> st;
    stringstream ss(s);
    string token;
    
    while (ss >> token) {
        if (isdigit(token[0])) {
            st.push(stoi(token));
        } else {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            
            if (token == "+") st.push(a + b);
            else if (token == "-") st.push(a - b);
            else if (token == "*") st.push(a * b);
            else if (token == "/") st.push(a / b);
        }
    }
    return st.top();
}
```

### 3. Chuyển trung tố sang hậu tố (Infix to Postfix)
```cpp
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infixToPostfix(string s) {
    stack<char> st;
    string result = "";
    
    for (char c : s) {
        if (isalnum(c)) {
            result += c;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop();  // Xóa '('
        } else {  // Toán tử
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    
    return result;
}

// Test
cout << infixToPostfix("A+B*C");     // ABC*+
cout << infixToPostfix("(A+B)*C");   // AB+C*
```

### 4. Tìm phần tử lớn hơn tiếp theo (Next Greater Element)
```cpp
vector<int> nextGreater(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> st;  // Lưu chỉ số
    
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            result[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }
    
    return result;
}

// Test
vector<int> arr = {4, 5, 2, 10, 8};
vector<int> nge = nextGreater(arr);
// Output: [5, 10, 10, -1, -1]
```

### 5. Diện tích hình chữ nhật lớn nhất trong histogram
```cpp
int largestRectangleArea(vector<int>& heights) {
    stack<int> st;
    int maxArea = 0;
    int n = heights.size();
    
    for (int i = 0; i < n; i++) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, h * width);
        }
        st.push(i);
    }
    
    while (!st.empty()) {
        int h = heights[st.top()];
        st.pop();
        int width = st.empty() ? n : n - st.top() - 1;
        maxArea = max(maxArea, h * width);
    }
    
    return maxArea;
}

// Test
vector<int> heights = {2, 1, 5, 6, 2, 3};
cout << largestRectangleArea(heights);  // 10
```

### 6. Stock Span Problem
Tìm số ngày trước đó có giá ≤ giá hiện tại
```cpp
vector<int> stockSpan(vector<int>& prices) {
    int n = prices.size();
    vector<int> span(n);
    stack<int> st;  // Lưu chỉ số
    
    for (int i = 0; i < n; i++) {
        while (!st.empty() && prices[st.top()] <= prices[i]) {
            st.pop();
        }
        
        span[i] = st.empty() ? (i + 1) : (i - st.top());
        st.push(i);
    }
    
    return span;
}

// Test
vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
vector<int> spans = stockSpan(prices);
// Output: [1, 1, 1, 2, 1, 4, 6]
```

### 7. Undo/Redo trong Editor
```cpp
class TextEditor {
    stack<string> undoStack;
    stack<string> redoStack;
    string current;
    
public:
    TextEditor() { current = ""; }
    
    void write(string text) {
        undoStack.push(current);
        current += text;
        while (!redoStack.empty()) redoStack.pop();  // Clear redo
    }
    
    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(current);
            current = undoStack.top();
            undoStack.pop();
        }
    }
    
    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(current);
            current = redoStack.top();
            redoStack.pop();
        }
    }
    
    string getText() { return current; }
};
```

---

## 🎯 BÀI TẬP THỰC HÀNH

### Bài 1: Minimum Stack
Thiết kế stack hỗ trợ lấy min trong O(1)
```cpp
class MinStack {
    stack<int> st;
    stack<int> minSt;
    
public:
    void push(int x) {
        st.push(x);
        if (minSt.empty() || x <= minSt.top()) {
            minSt.push(x);
        }
    }
    
    void pop() {
        if (st.top() == minSt.top()) {
            minSt.pop();
        }
        st.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minSt.top();
    }
};
```

### Bài 2: Valid Parentheses với độ dài tối thiểu
```cpp
bool isValidWithMinLength(string s, int minLen) {
    stack<int> st;  // Lưu vị trí
    st.push(-1);
    int maxLen = 0;
    
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            st.push(i);
        } else {
            st.pop();
            if (st.empty()) {
                st.push(i);
            } else {
                maxLen = max(maxLen, i - st.top());
            }
        }
    }
    
    return maxLen >= minLen;
}
```

### Bài 3: Decode String
```cpp
// Input: "3[a2[c]]" → Output: "accaccacc"
string decodeString(string s) {
    stack<int> countSt;
    stack<string> strSt;
    string current = "";
    int num = 0;
    
    for (char c : s) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == '[') {
            countSt.push(num);
            strSt.push(current);
            num = 0;
            current = "";
        } else if (c == ']') {
            string temp = current;
            current = strSt.top();
            strSt.pop();
            int count = countSt.top();
            countSt.pop();
            for (int i = 0; i < count; i++) {
                current += temp;
            }
        } else {
            current += c;
        }
    }
    
    return current;
}
```

---

## ⚠️ LƯU Ý QUAN TRỌNG

### 1. Kiểm tra rỗng trước khi pop/top
```cpp
// ❌ SAI
st.pop();
int x = st.top();

// ✅ ĐÚNG
if (!st.empty()) {
    int x = st.top();
    st.pop();
}
```

### 2. Pop không trả về giá trị
```cpp
// ❌ SAI
int x = st.pop();  // Lỗi biên dịch

// ✅ ĐÚNG
int x = st.top();
st.pop();
```

### 3. Stack vs Vector
```cpp
// Stack: chỉ truy cập đỉnh
stack<int> st;
st.push(1);
st.push(2);
// Không thể truy cập st[0] hay st[1]

// Vector: truy cập ngẫu nhiên
vector<int> v;
v.push_back(1);
v.push_back(2);
cout << v[0] << " " << v[1];  // OK
```

---

## 📝 TEMPLATE NHANH

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // Stack cơ bản
    stack<int> st;
    st.push(10);
    st.push(20);
    
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    // Output: 20 10
    
    return 0;
}
```

---

## 🔗 LIÊN KẾT

- **Queue**: Cấu trúc FIFO
- **Deque**: Kết hợp Stack + Queue
- **Priority Queue**: Heap
- **DFS**: Sử dụng stack (hoặc đệ quy)

---

## 💪 KHI NÀO DÙNG STACK?

✅ **Nên dùng khi:**
- Kiểm tra dấu ngoặc, tag HTML
- Tính biểu thức (postfix, infix)
- DFS iterative
- Backtracking
- Undo/Redo
- Next/Previous Greater Element
- Histogram problems

❌ **Không nên dùng khi:**
- Cần truy cập phần tử ở giữa → dùng vector/deque
- Cần FIFO → dùng queue
- Cần phần tử min/max → dùng priority_queue

---

**Tips:** Stack thường xuất hiện trong các bài toán xử lý chuỗi, tính toán biểu thức, và các thuật toán duyệt đồ thị!
