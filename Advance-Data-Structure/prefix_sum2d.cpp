/*
Tổng hình chữ nhật m x n
Cong thuc truy hoi: S[i][j] = S[i-1][j] + S[i][j-1] - S[i-1][j-1] + a[i][j]
Công thức tinhs toan: query[a, b, c, d] = S[c, d] – S[c, b-1] – S[a-1, d] + S[a-1, b-1]
2 diem (a,b) va (c,d) la 2 duong cheo cua hinh chu nhat
*/

#include <bits/stdc++.h>

using namespace std;
#define MAXN 1e6+69
#define long long int

int n,m,q;

vector<vector<int>> arr;
vector<vector<int>> prefix_sum2d;

int main () {
    cin >> n >> m;
    arr.resize(n+1, vector<int>(m+1,0));
    prefix_sum2d.resize(n+3, vector<int>(m+3,0));

    // Index 1->n, 1->m
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= m;j++) {
            cin >> arr[i][j];
            prefix_sum2d[i][j] = arr[i][j] + prefix_sum2d[i-1][j] + prefix_sum2d[i][j-1] - prefix_sum2d[i-1][j-1];
        }
    }

    for (int j = 0;j < q;j++) {
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        cout << prefix_sum2d[c][d] - prefix_sum2d[c][b-1] - prefix_sum2d[a-1][d] + prefix_sum2d[a-1][b-1] << endl;
    }


}