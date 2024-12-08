/*
Cho dãy số a1, a2, …, an. Thực hiện Q truy vấn, mỗi truy vấn được đặc trưng bởi
 cặp chỉ số (i, j) trong đó ta cần tính tổng ai + ai+1 + . . . + aj.

*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 1e6+69
#define long long int

int n,q;
vector<int> arr;
vector<int> prefix_sum;


int main() {  
    int n, q;
    cin >> n >> q;
    arr.resize(n+1,0);
    prefix_sum.resize(n+1,0);

    // index should be 1 -> n

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        prefix_sum[i] = prefix_sum[i-1] + arr[i];
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        cout << prefix_sum[r] - prefix_sum[l-1] << endl;
    }

    return 0;
}