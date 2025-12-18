# PRIORITY QUEUE (Hàng đợi ưu tiên)

## Priority Queue cơ bản

```cpp
// Max heap (mặc định)
priority_queue<int> pq;

// Min heap
priority_queue<int, vector<int>, greater<int>> pq_min;

// Thêm phần tử
pq.push(x);

// Lấy phần tử có độ ưu tiên cao nhất
int top = pq.top();

// Xóa phần tử có độ ưu tiên cao nhất
pq.pop();

// Kích thước
int size = pq.size();

// Kiểm tra rỗng
if (pq.empty()) { /* ... */ }
```

## Priority Queue với cấu trúc tùy chỉnh

```cpp
struct Node {
    int value;
    int priority;
    
    bool operator < (const Node& other) const {
        return priority < other.priority;  // Max heap theo priority
    }
};

priority_queue<Node> pq;
```

## Ứng dụng

### Dijkstra với Priority Queue
```cpp
void dijkstra(int start) {
    priority_queue<pair<long long, int>, 
                   vector<pair<long long, int>>, 
                   greater<pair<long long, int>>> pq;
    
    vector<long long> dist(n + 1, LLONG_MAX);
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}
```

### K-th Smallest/Largest Element
```cpp
// K phần tử lớn nhất
priority_queue<int, vector<int>, greater<int>> minHeap;

void addElement(int x, int k) {
    minHeap.push(x);
    if (minHeap.size() > k) {
        minHeap.pop();
    }
}

int getKthLargest() {
    return minHeap.top();
}
```

### Merge K Sorted Lists
```cpp
struct Node {
    int value;
    int listIndex;
    int elementIndex;
    
    bool operator < (const Node& other) const {
        return value > other.value;  // Min heap
    }
};

vector<int> mergeKLists(vector<vector<int>>& lists) {
    priority_queue<Node> pq;
    vector<int> result;
    
    // Thêm phần tử đầu của mỗi list
    for (int i = 0; i < lists.size(); i++) {
        if (!lists[i].empty()) {
            pq.push({lists[i][0], i, 0});
        }
    }
    
    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        
        result.push_back(node.value);
        
        // Thêm phần tử tiếp theo từ cùng list
        if (node.elementIndex + 1 < lists[node.listIndex].size()) {
            pq.push({
                lists[node.listIndex][node.elementIndex + 1],
                node.listIndex,
                node.elementIndex + 1
            });
        }
    }
    
    return result;
}
```
