#include <bits/stdc++.h>
using namespace std;

/*
RMQ: Range Minimum Query
 Cho dãy a0, a1, …, aN-1. Cho số nguyên dương K, ta cần thực hiện K truy vấn, 
mỗi truy vấn dạng RMQ(i, j) trả về chỉ số của phần tử nhỏ nhất của dãy ai, ai+1, . . ., aj
*/

// Min tree, sum tree is the same
struct SegmentTree {
    vector<int> tree;
    int size;

    SegmentTree(int n) {
        size = n;
        tree.assign(4 * n, INT_MAX);
    }

    void build(const vector<int>& a, int node, int start, int end) {
        if (start == end) {
            tree[node] = a[start];
        } else {
            int mid = (start + end) / 2;
            build(a, 2 * node, start, mid);
            build(a, 2 * node + 1, mid + 1, end);
            tree[node] = min(tree[2 * node], tree[2 * node + 1]); // Change here for sum tree
        }
    }

    void update(int node, int start, int end, int idx, int value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node, start, mid, idx, value);
            } else {
                update(2 * node + 1, mid + 1, end, idx, value);
            }
            tree[node] = min(tree[2 * node], tree[2 * node + 1]); // Change here for sum tree
        }
    }

    int query(int node, int start, int end, int L, int R) {
        if (R < start || L > end) {
            return INT_MAX; // No overlap // Change here for sum tree
        }
        if (L <= start && end <= R) {
            return tree[node]; // Total overlap 
        }
        int mid = (start + end) / 2;
        int left_min = query(2 * node, start, mid, L, R);
        int right_min = query(2 * node + 1, mid + 1, end, L, R);
        return min(left_min, right_min); // Change here for sum tree
    }
};

int main() {
    // Index from 0 -> n-1
    vector<int> a = {1, 3, 2, 7};
    int n = a.size();

    SegmentTree seg_tree(n);
    seg_tree.build(a, 1, 0, n - 1);

    cout << "Minimum in range [0, 3]: " << seg_tree.query(1, 0, n - 1, 0, 3) << endl;

    // Append a new element
    a.push_back(4);
    n = a.size();
    seg_tree.tree.resize(4 * n, INT_MAX); // Resize the tree
    seg_tree.update(1, 0, n - 1, n - 1, 4);

    cout << "Minimum in range [0, 4]: " << seg_tree.query(1, 0, n - 1, 0, 4) << endl;

    // Update, delete an element
    // seg_tree.update(1, 0, n - 1, idx, value);

    return 0;
}


/*
O log mỗi truy vấn nhưng có thể add thêm, update giá trị
*/