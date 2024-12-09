/*
Cho dãy số không âm a[1], a[2], . . ., a[n]. Cho trước giá trị Q, hãy tìm dãy
 con (gồm một số phần tử đứng liên tiếp cạnh nhau) dài nhất mà có tổng nhỏ hơn hoặc bằng Q.
*/

#include <bits/stdc++.h>

using namespace std;

#define MAXN (int) 1e6+69
#define long long int
#define INF (int) 1e9+69

int n,q;

vector<int> a;

void cachkhac() {
    int res = 0; int S = 0;
    int L = 1; 
        for (int R = 1, R <= n, R ++) {
            S = S + a[R];
            while (S > q) {
                S = S - a[L]; 
                L = L + 1;
            }
        } 
    cout << res << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;
    a.resize(n+1,0);
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
    }

    int i = 1; int j = 1;
    int cur_sum = 0;
    int res = 0;
    while (j <= n) {
        if (cur_sum + a[j] <= q) {
            cur_sum += a[j];
            j++;
            res = max(res, j-i);
        } else {
            cur_sum -= a[i];
            i++;
        }
    }
    cout << res << endl;

    return 0;
}

/*
Sliding window (1 cách triển khai của 2 con trỏ)
- Sử dụng khi cần xét đến 1 tính chất của subset liền nhau (max,min,sum,...)
- Các bước:
+ Khởi tạo 2 con trỏ tại vị trí 0, [giá trị cần đánh giá] = biểu thị cho 1 tính chất của subset
+ Điều kiện ngắt (j <= n)
+ Dịch chuyển con trỏ (theo cửa sổ, điều kiện là so sánh [giá trị cần đánh giá])

*** Subset có thể đi với deque

*/