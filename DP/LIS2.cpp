// Problem: https://leetcode.com/problems/longest-increasing-subsequence-ii/description/

// Best solution: DP hash and segment tree for Onlogn

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

int n, k;

vector<int> a;

struct SegmentTree { // MAX tree
    vector<int> tree;
    int size;

    SegmentTree(int n) {
        size = n;
        tree.assign(4 * n, 0);
    }

    void build(const vector<int>& a, int node, int start, int end) {
        if (start == end) {
            tree[node] = a[start];
        } else {
            int mid = (start + end) / 2;
            build(a, 2 * node, start, mid);
            build(a, 2 * node + 1, mid + 1, end);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]); // Change here for sum tree
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
            tree[node] = max(tree[2 * node], tree[2 * node + 1]); // Change here for sum tree
        }
    }

    int query(int node, int start, int end, int L, int R) {
        if (R < start || L > end) {
            return 0; // No overlap // Change here for sum tree
        }
        if (L <= start && end <= R) {
            return tree[node]; // Total overlap 
        }
        int mid = (start + end) / 2;
        int left_min = query(2 * node, start, mid, L, R);
        int right_min = query(2 * node + 1, mid + 1, end, L, R);
        return max(left_min, right_min); // Change here for sum tree
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    a.resize(n+1,0);

    for (int i = 0;i < n;i++) {
        cin >> a[i];
    }
    int mx_value = *max_element(a.begin(), a.end());
    vector<int> dp(mx_value+1,0); // DP hash map
    
    // O n*max_a
    // for (int i = 0; i < n;i++) {
    //     dp[a[i]] = 1;
    //     for (int j = max(0,a[i]-k);j < a[i];j++) {
    //         dp[a[i]] = max(dp[j]+1,dp[a[i]]);
    //     }
    // }

    // We can optimize the for loop above by using segment tree Onlog(maxvalue)

    SegmentTree seg_tree(*max_element(a.begin(), a.end())+1);
    for (int i = 0; i < n;i++) {
        int dpa = seg_tree.query(1,0,mx_value,max(0,a[i]-k),a[i]-1)+1;
        seg_tree.update(1,0,mx_value,a[i],dpa);
    }
    
    cout << seg_tree.query(1,0,mx_value,0,mx_value) << endl;
    return 0;
}