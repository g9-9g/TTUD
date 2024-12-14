/*
Nurse

Đề bài: Một giám đốc của một bệnh viện muốn lập lịch làm việc cho y tá trong N ngày 1…N.
Y tá chỉ có thể làm việc liên tục trong x ngày (K1 <= x <= K2), sau đó phải nghỉ 1 ngày.

Y tá chỉ được nghỉ 1 ngày giữa 2 đợt làm việc liên tiếp. Có nghĩa rằng nếu y tá nghỉ ngày hôm nay, ngày mai y tá đó sẽ phải làm việc.

Công thức đệ quy:
- Gọi f[i][0] là số cách lập lịch đến ngày thứ i và ngày thứ i là ngày nghỉ.
- Gọi f[i][1] là số cách lập lịch đến ngày thứ i và ngày thứ i là ngày kết thúc của một đợt làm việc.

Công thức:
f[i][0] = f[i − 1][1];
f[i][1] = Σ(k1 ≤ j ≤ k2) f[i − j][0];
=> kết quả: f[n][0] + f[n][1];

*/

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

int n,k1,k2;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k1 >> k2;

    vector <vector<int>> f(n+1,vector<int>(2,0));
    f[0][0] = f[0][1] = 1;
    for (int i = 1;i <= n;i++) {
        for (int j = k1;j <= k2;j++) {
            if (i - j >= 0) {
                f[i][1] = (f[i][1] + f[i-j][0]) % MOD;
            }
        }
        f[i][0] = f[i-1][1];
    }

    cout << (f[n][0] + f[n][1]) % MOD << endl;

    return 0;
}