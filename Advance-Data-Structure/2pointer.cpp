/*
 Cho dãy số a[1], a[2], . . ., a[n] được sắp xếp theo thứ tự tăng dần (các phần
 tử đôi một khác nhau). Cho trước giá trị Q, hãy đếm số cặp 2 chỉ số i và j sao cho a[i] + a[j] = Q
*/

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define long long int

int n,q;

vector<int> a;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;
    a.resize(n+2,0);
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
    }

    int i = 1; int j = n;
    int res = 0;
    while (i < j) {
        if (a[i] + a[j] == q) {
            res++;
            i++; // chinhr lech
            j--;
        } else if (a[i] + a[j] > q) {
            j--;
        } else {
            i++;
        }
    }
    cout << res << endl;


    return 0;
}

/*
Ý tưởng chung khi giải bài 2 con trỏ
- Cho 2 con trỏ tương ứng 2 vị trí trong mảng
- Tìm điều kiện ngắt của vòng lặp (thường là i < j)
- Tìm điều kiện thỏa mãn yêu cầu (sẽ ảnh hưởng đến res)
- Tìm điều kiện dịch chuyển con trỏ
=> Suy nghĩ theo hướng 2 con trỏ: 
- 2 con trỏ là cách duyệt tối ưu (sử dụng tham lam) từ thuật 2 vòng lặp brute-force, 
- Phải có 1 điều kiện, yếu tố đặc biệt (thường là mảng đã được sort trước)

*/