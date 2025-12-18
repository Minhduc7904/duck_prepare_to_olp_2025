# TỔNG HỢP KIẾN THỨC ÔN THI OLYMPIC TIN HỌC

## 📋 MỤC LỤC & ĐƯỜNG DẪN

### [1. Các phép toán về bit](01_bit_operations/bit_operations.md)
- Các phép toán cơ bản
- Kiểm tra, bật, tắt, đảo bit
- Ứng dụng: swap, tìm số xuất hiện lẻ

### [2. STL: Stack, Set, Multiset, Queue, Priority Queue](02_stl/)
- **[Stack](02_stl/stack.md)**: Ngăn xếp, dấu ngoặc, postfix, histogram
- **[Set & Multiset](02_stl/set_multiset.md)**: Tập hợp, lower_bound, upper_bound
- **[Queue](02_stl/queue.md)**: Hàng đợi, deque, sliding window
- **[Priority Queue](02_stl/priority_queue.md)**: Hàng đợi ưu tiên, heap

### [3. Segment Tree](03_segment_tree/)
- **[Segment Tree cơ bản](03_segment_tree/segment_tree_basic.md)**: Sum, Min, Max, GCD
- **[Lazy Propagation](03_segment_tree/lazy_propagation.md)**: Range update, range query

### [4. Xử lý xâu](04_string/)
- **[KMP](04_string/kmp.md)**: Knuth-Morris-Pratt, tìm pattern
- **[Trie](04_string/trie.md)**: Cây tiền tố, autocomplete, binary trie
- **[String Hash](04_string/string_hash.md)**: Hash tiền tố, double hash
- **[Manacher](04_string/manacher.md)**: Tìm palindrome dài nhất O(n)

### [5. Quy hoạch động](05_dynamic_programming/)
- **[QHĐ Palindrome](05_dynamic_programming/dp_palindrome.md)**: Chia xâu, xâu con palindrome
- **[QHĐ Bit Mask](05_dynamic_programming/dp_bitmask.md)**: TSP, assignment problem
- **[QHĐ Chữ số](05_dynamic_programming/dp_digit.md)**: Digit DP, đếm số thỏa điều kiện
- **[QHĐ trên DAG](05_dynamic_programming/dp_on_dag.md)**: Đường đi dài nhất, topological sort

### [6. Đồ thị](06_graph/)
- **[DSU](06_graph/dsu.md)**: Disjoint Set Union, Union Find
- **[BFS & DFS](06_graph/bfs_dfs.md)**: Duyệt đồ thị, tìm thành phần liên thông
- **[Shortest Path](06_graph/shortest_path.md)**: Dijkstra, Floyd, Bellman-Ford, SPFA
- **[MST](06_graph/mst.md)**: Kruskal, Prim, cây khung nhỏ nhất
- **[LCA](06_graph/lca.md)**: Binary lifting, RMQ, kth ancestor

### [7. Toán học](07_math/)
- **[Modulo](07_math/modulo.md)**: Setup modulo, nghịch đảo, lũy thừa, GCD
- **[Số nguyên tố](07_math/primes.md)**: Sàng, Miller-Rabin, phân tích thừa số
- **[Tổ hợp](07_math/combinatorics.md)**: nCk, Pascal, Catalan, Stirling

---

## ✅ CHECKLIST ÔN TẬP

### Kiến thức cơ bản
- [ ] Các phép toán bit
- [ ] STL: Stack, Set, Multiset, Queue, Priority Queue
- [ ] Segment Tree (cơ bản + lazy)

### Xử lý xâu
- [ ] KMP
- [ ] Trie
- [ ] String Hash
- [ ] Manacher

### Quy hoạch động
- [ ] QHĐ Palindrome
- [ ] QHĐ Bit Mask
- [ ] QHĐ Chữ số
- [ ] QHĐ trên DAG

### Đồ thị
- [ ] DSU
- [ ] BFS/DFS
- [ ] Dijkstra, Floyd
- [ ] Kruskal, Prim
- [ ] LCA

### Toán học
- [ ] Setup Modulo
- [ ] GCD, LCM
- [ ] Sàng số nguyên tố
- [ ] Kiểm tra số nguyên tố
- [ ] Phân tích thừa số
- [ ] Đếm ước
- [ ] Tổ hợp nCk

---

## 📝 TIPS QUAN TRỌNG

### Khi thi:
1. **Đọc kỹ đề**: Chú ý giới hạn, điều kiện đặc biệt
2. **Phân tích độ phức tạp**: O(n log n) thường an toàn với n ≤ 10^5
3. **Test các trường hợp đặc biệt**: n = 1, n = 0, số âm, số lớn
4. **Overflow**: Dùng `long long` khi cần thiết
5. **Modulo**: Nhớ lấy mod ở mọi phép toán
6. **Debug**: In ra giá trị trung gian để kiểm tra

### Độ phức tạp thường gặp:
| Độ phức tạp | Thuật toán | Giới hạn n |
|-------------|------------|-----------|
| **O(1)** | Hash, Array access | Bất kỳ |
| **O(log n)** | Binary search, GCD | n ≤ 10^18 |
| **O(n)** | Linear search, Prefix sum | n ≤ 10^8 |
| **O(n log n)** | Sort, Segment tree, BIT | n ≤ 10^6 |
| **O(n√n)** | Factorization | n ≤ 10^7 |
| **O(n²)** | DP 2 chiều, Floyd | n ≤ 5000 |
| **O(n³)** | Floyd, Matrix mult | n ≤ 500 |
| **O(2^n)** | Bitmask, Backtrack | n ≤ 20 |
| **O(n!)** | Permutation | n ≤ 10 |

---

## ✅ CHECKLIST TRƯỚC KHI NỘP BÀI

- [ ] Kiểm tra lại giới hạn biến (int vs long long)
- [ ] Test với sample input
- [ ] Test với trường hợp đặc biệt (min, max, 0, âm)
- [ ] Kiểm tra overflow
- [ ] Kiểm tra mảng có đủ kích thước không
- [ ] Khởi tạo biến đúng cách
- [ ] Xem lại độ phức tạp thuật toán
- [ ] Kiểm tra điều kiện dừng vòng lặp
- [ ] Modulo ở mọi phép toán (nếu có)

---

## 🔗 LIÊN KẾT NHANH

### Template thường dùng
- [Segment Tree Template](03_segment_tree/segment_tree_basic.md)
- [Dijkstra Template](06_graph/shortest_path.md)
- [DSU Template](06_graph/dsu.md)
- [Modulo Setup](07_math/modulo.md)

### Bài toán hay gặp
- **Tìm đường đi ngắn nhất**: → Dijkstra, BFS, Floyd
- **Cây khung nhỏ nhất**: → Kruskal, Prim
- **Tìm xâu con**: → KMP, Hash
- **Palindrome**: → Manacher, DP
- **Tổ hợp**: → nCk, Catalan
- **Đồ thị có chu trình**: → DSU, DFS

---

**Chúc bạn thi tốt! 🎯**

*"Luyện tập là chìa khóa thành công"*
