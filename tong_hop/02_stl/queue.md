# QUEUE (Hàng đợi)

## Queue cơ bản

```cpp
queue<int> q;

// Thêm vào cuối
q.push(x);

// Xóa đầu
q.pop();

// Lấy phần tử đầu
int front = q.front();

// Lấy phần tử cuối
int back = q.back();

// Kích thước
int size = q.size();

// Kiểm tra rỗng
if (q.empty()) { /* ... */ }
```

## Deque (Double-ended Queue)

```cpp
deque<int> dq;

// Thêm vào đầu/cuối
dq.push_front(x);
dq.push_back(x);

// Xóa đầu/cuối
dq.pop_front();
dq.pop_back();

// Truy cập đầu/cuối
int front = dq.front();
int back = dq.back();

// Truy cập theo index
int val = dq[i];
```

## Ứng dụng

### Sliding Window Maximum với Deque
```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;  // Lưu index
    vector<int> result;
    
    for (int i = 0; i < nums.size(); i++) {
        // Xóa các phần tử ngoài window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Xóa các phần tử nhỏ hơn phần tử hiện tại
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}
```

### BFS với Queue
```cpp
void BFS(int start) {
    queue<int> q;
    vector<bool> visited(n + 1, false);
    
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}
```
