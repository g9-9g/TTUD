/*
 Mộtxe buýtxuất phát từ điểm 0 cần được tính toán lộ trình để phục vụ đưa đón n khách và quay trở về điểm
 0. Khách i có điểm đón là i và điểm trả là i + n (i = 1, 2, …, n). Xe buýt có K chỗ ngồi để phục vụ khách. Khoảng
 cách di chuyển từ điểm i đến điểm j là d(i, j), với i, j = 0, 1, 2, . . , 2n. Hãy tính lộ trình cho xe buýt sao cho
 tổng độ dài quãng đường di chuyển là nhỏ nhất, đồng thời số khách trên xe tại mỗi thời điểm không vượt
 quá K.
 • Thuậttoán nhánhvà cận
 • Môhìnhhóa:X1, X2, . . ., X2n là dãy các điểm đón-trả trên lộ trình xe buýt (là hoán vị của 1, 2, …, 2n).
 • Cmin:khoảngcách nhỏ nhất trongsố các khoảng cách giữa 2 điểm
 • Mảngđánhdấu:visited[v] = true có nghĩa điểm v đã xuất hiện trên lộ trình và visited[v] = false, ngược lại
 • load: số khách đang có mặt trên xe
 • Khi lộ trình đi đến điểm đón thì load tăng lên 1 và khi đi đến điểm trả thì load giảm đi 1
 • f: độdài của lộ trình bộ phận
 • f*: độdài lộ trình ngắn nhất đã tìm thấy (kỷ lục)

*/

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

int n,p;
vector <vector<int>> d;
int f_rec = INF;
int min_d = INF;

vector<int> visited;
// In, debug ra 1 phương án thỏa mãn
void solution(int res) {
    // cout << res << endl;
    f_rec = min(f_rec,res);
}

// Kiểm tra bước thử có hợp lệ hay không 
bool check(int k,int v, int cap) {
    if (visited[v] == 1) return false;
    if (v <= n) {       // Pick-up point
        if (cap + 1 > p) return false;  // Exceeds capacity
    } else {                            // Drop-off point
        if (!visited[v - n]) return false;  // Pick-up must happen first
    }
    return true;
}

void backtrack(int k, int cur, int cap, int res) {
    for (int v = 1; v <= 2*n;v++) {
        if (check(k,v,cap)) {
            visited[v] = 1;
            if (k == 2*n) {
                solution(res+d[cur][v] +d[v][0]);
            } else {
                if (res + d[cur][v] + (2*n-k) * min_d < f_rec) {
                    if (v <= n) backtrack(k+1,v, cap+1, res + d[cur][v]);
                    else backtrack(k+1,v, cap-1, res + d[cur][v]);
                }
            }
            visited[v] = 0;
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> p;
    d.resize(2*n+10,vector<int>(2*n+10,0));
    visited.resize(2*n+10,0);

    for (int i = 0;i <= 2*n;i++) {
        for (int j = 0;j <= 2*n;j++) {
            cin >> d[i][j];
            if (d[i][j] != 0) min_d = min(min_d,d[i][j]);
        }
    }

    backtrack(1,0,0,0);

    cout << f_rec << endl;
    return 0;
}

/*
Old version - Using global variables

#include ...
vector <int> visited;

// In, debug ra 1 phương án thỏa mãn
void solution() {
    // cout << res << endl;
    f_rec = min(f_rec,res);
}

// Kiểm tra bước thử có hợp lệ hay không 
bool check(int k,int v) {
    if (visited[v] == 1) return false;
    if (v <= n) {       // Pick-up point
        if (cap + 1 > p) return false;  // Exceeds capacity
    } else {                            // Drop-off point
        if (!visited[v - n]) return false;  // Pick-up must happen first
    }
    return true;
}

void backtrack(int k, int cur) {
    for (int v = 1; v <= 2*n;v++) {
        if (check(k,v)) {
            visited[v] = 1;
            res += d[cur][v];
            if (v > n) {cap -= 1;}
            else {cap += 1;}
            if (k == 2*n) {
                res += d[v][0];
                solution();
                res -= d[v][0];
            } else {
                if (res + (2*n-k) * min_d < f_rec) {
                    backtrack(k+1,v);
                }
            }
            if (v > n) {cap += 1;}
            else {cap -= 1;}
            res -= d[cur][v];
            visited[v] = 0;
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> p;
    d.resize(2*n+10,vector<int>(2*n+10,0));
    visited.resize(2*n+10,0);

    for (int i = 0;i <= 2*n;i++) {
        for (int j = 0;j <= 2*n;j++) {
            cin >> d[i][j];
            if (d[i][j] != 0) min_d = min(min_d,d[i][j]);
        }
    }

    backtrack(1,0);

    cout << f_rec << endl;
    return 0;
}


*/