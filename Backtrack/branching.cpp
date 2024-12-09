/*
Nhánh cận, backtrack mở rộng, cấu trúc cơ bản:
*/

#include <bits/stdc++.h>

using namespace std;


#define MAXN 1000000
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

int n;

vector<int> a;

// lưu trữ kết quả tốt nhất tìm được
int f_rec;

// Lưu trữ kết quả hiện tại, có thể đưa vào trong hàm backtrack
int res;

// In ra 1 phương án thỏa mãn
void solution() {
    // Cập nhập f_rec và ghi ra kết quả
    f_rec = min(f_rec, res);
    for (int i = 1;i <= n;i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

// Kiểm tra bước thử có hợp lệ hay không 
bool check(int k,int v) {
    return true;
}

void backtrack(int k) {
    // Thử tất cả các phương án ở bước K
    for (int v = 0;v <= 1;v++) {
        if (check(k,v)) {
            a[k] = v; // [Update a data structure D]
            if (k == n) { // Điều kiện dừng
                solution(); 
            } else {
                if (g(X1, X2, …, Xk) < f_rec) // Hàm cận dưới
                    backtrack(k+1); // Thử tiếp chỉ khi phương án cụ thể này có khả năng tốt hơn.
            }
            // [Recover the data structure D]
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    a.resize(n+1,0);
    for (int i = 0;i < n;i++) {
        cin >> a[i];
    }


    return 0;
}