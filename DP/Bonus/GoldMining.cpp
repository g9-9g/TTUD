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
