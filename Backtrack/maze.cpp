#include <bits/stdc++.h>
using namespace std;

#define MAX_LEN 2000


int a[MAX_LEN][MAX_LEN];

int d[MAX_LEN][MAX_LEN];

int dx[4] = {0 , 1 , -1, 0};
int dy[4] = {1, 0 , 0 ,-1};

int m,n,r,c;

int bfs(int r, int c, int n, int m) {
    queue <pair<int,int>> qq; 
    qq.push({r,c});
    
    // if (r < 1 || r > m || c < 1 || c > n) return 0;
    
    d[r][c] = 0;
    a[r][c] = 1;
    
    while (!qq.empty()) {
        int u = qq.front().first;
        int v = qq.front().second;
        qq.pop();
        

        for (int i = 0; i < 4; i++) {
            int x = dx[i] + u;
            int y = dy[i] + v;
            if (x < 1 || x > n || y < 1 || y > m) {
                return d[u][v] + 1;
            }
            if (a[x][y] != 1) {
                d[x][y] = d[u][v] + 1;
                qq.push({x, y});
                a[x][y] = 1;
            }
        }

    }
    
    return -1;
}


int main() {
    
    cin >> n >> m >> r >> c;
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= m;j++) {
            cin >> a[i][j];
        }
    }
    cout << bfs(r,c,n,m) << endl;
    // for (int i = 1; i <= n;i++) {
    //     for (int j = 1;j <= m;j++) {
    //         cout << (d[i][j]) << " ";
    //     }
    //     cout << endl;
    // }
    
    return 0;
}
