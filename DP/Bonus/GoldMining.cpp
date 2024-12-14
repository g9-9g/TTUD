/*
Có n nhà kho nằm trên một đường thẳng.
Nhà kho i có số lượng vàng là ai
**Yêu cầu:**
Chọn các nhà kho sao cho:
- Tổng lượng vàng là lớn nhất.
- 2 nhà kho liên tiếp có khoảng cách nằm trong khoảng \([L_1, L_2]\).

---

- Gọi F[i] là tổng lượng vàng lớn nhất nếu chọn các nhà kho từ 1 đến i-1 và nhà kho thứ i được chọn.

- Khởi tạo: F[i] = a[i];

- Công thức:
    F[i] = max(F[j] + a[i]), với j chạy từ i - L2 đến i - L1. -> dùng deque để O(n)
- Kết quả:
    max(F[i]), với i chạy từ 1 đến n.

*/

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

int n, L1, L2;

vector<int> a;

// Segment tree solution
void solve() {
    cin >> n >> L1 >> L2;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    SegmentTree segTree; // max tree
    segTree.init(n);
    vector<int> dp(n, -INF);

    for (int i = 0; i < n; i++) {
        // L1 <= i -j < L2 -> j thuoc [i-L2, i-L1]
        if (i - L1 >= 0) {
            int l = max(0, i - L2);
            int r = i - L1;
            int max_val = segTree.query(l, r);
            dp[i] = max(dp[i], max_val + a[i]);
        } else {
            dp[i] = a[i];
        }
        segTree.update(i, dp[i]);
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> L1 >> L2;
    a.resize(n+1,0);
    for (int i = 0;i < n;i++) {
        cin >> a[i];
    }

    vector <int> dp(n,0);
    vector <ii> dq;
    int res = 0;

    for (int i = 0; i < n; i++) {
        dp[i] = a[i];
        while (!dq.empty())  {
            if (dq.back().first < i - L2) dq.pop_back();
            else break;
        }
        if (i-L1 > 0) {
            if (dq.empty()) dq.push_back({i-L1, dp[i-L1]});
            else if (dq.back().second < dp[i-L1]) dq.push_back({i-L1, dp[i-L1]});
        }
        if (!dq.empty()) dp[i] += dq.back().second;
        cout << dp[i] << " ";
        res = max(res, dp[i]);
    }
    cout << res << endl;

    return 0;
}
