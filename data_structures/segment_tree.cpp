/*
 * Segment tree with lazy propagation.
 *
 * Build complexity: O(N)
 * queries complexity: O(logN)
 *
 */


template<class ValueType>
class SumSegmentTree {
 public:
     SumSegmentTree() = default;
     SumSegmentTree(int sz) : tree(sz * 4), pushing(sz * 4), size(sz) {}
     SumSegmentTree(vector<ValueType> a, int size) : SumSegmentTree(size) {
         build(a, 1, 0, size);
     }

     int add(int l, int r, ValueType delta) {
         return add(1, 0, size - 1, l, r, delta);
     }

     int add(int p, ValueType delta) {
         return add(1, 0, size - 1, p, p, delta);
     }

     int get(int l, int r) {
         return get(1, 0, size - 1, l, r);
     }

 private:
     ValueType merge(int v, int u) {
         return tree[v] + pushing[v] + tree[u] + pushing[u];
     }

     void push(int v) {
         tree[v] += pushing[v];
         pushing[v + v] += pushing[v];
         pushing[v + v + 1] += pushing[v];
         pushing[v] = 0;
     }

     void build(vector<ValueType>& a, int v, int tl, int tr) {
         if (tl == tr) {
             tree[v] = a[tl];
         } else {
             int mid = (tl + tr) / 2;
             build(a, v + v, tl, mid);
             build(a, v + v + 1, mid + 1, tr);
             tree[v] = merge(v + v, v + v + 1);
         }
     }

     void add(int v, int tl, int tr, int l, int r, ValueType delta) {
         if (l > r) {
             return;
         }
         if (l == tl && r == tr) {
             pushing[v] += delta;
             return;
         }
         push(v);
         int mid = (tl + tr) / 2;
         add(v + v, tl, mid, l, min(r, mid), delta);
         add(v + v + 1, mid + 1, tr, max(l, mid + 1), r, delta);
         tree[v] = merge(v + v, v + v + 1);
     }

     ValueType get(int v, int tl, int tr, int l, int r) {
         if (l > r) {
             return 0;
         }
         if (l == tl && r == tr) {
             return tree[v] + pushing[v];
         }
         push(v);
         int mid = (tl + tr) / 2;
         return get(v + v, tl, mid, l, min(r, mid)) +
                 get(v + v + 1, mid + 1, tr, max(l, mid + 1), r);
     }

     vector<ValueType> tree;
     vector<ValueType> pushing;
     size_t size;
};

