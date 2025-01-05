#include <bits/stdc++.h>
using namespace std;


// m == n, nếu ko thì thêm đỉnh rác
const int MAXN = 1005;       // Số đỉnh tối đa mỗi phía
const int INF = 1e9;         // Giá trị lớn để đại diện "vô cực"
int n;                       // Số đỉnh mỗi phía
int w[MAXN][MAXN];           // Ma trận trọng số
int lx[MAXN], ly[MAXN];      // Nhãn của các đỉnh bên U và V
int match[MAXN];             // match[j]: đỉnh bên U được ghép với đỉnh j bên V
bool S[MAXN], T[MAXN];       // Đánh dấu các đỉnh trong tập S (U) và T (V)
int slack[MAXN];             // slack[j]: độ chênh lệch cần điều chỉnh cho đỉnh j bên V
int slackx[MAXN];            // slackx[j]: đỉnh bên U liên quan đến slack[j]

// Tìm augmenting path
bool dfs(int u) {
    S[u] = true;
    for (int v = 1; v <= n; v++) {
        if (T[v]) continue;
        int delta = lx[u] + ly[v] - w[u][v];
        if (delta == 0) { // Cạnh thỏa mãn điều kiện
            T[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        } else {
            if (delta < slack[v]) {
                slack[v] = delta;
                slackx[v] = u;
            }
        }
    }
    return false;
}

// Điều chỉnh nhãn để tạo augmenting path mới
void update_labels() {
    int delta = INF;
    for (int v = 1; v <= n; v++) {
        if (!T[v]) delta = min(delta, slack[v]);
    }
    for (int u = 1; u <= n; u++) {
        if (S[u]) lx[u] -= delta;
    }
    for (int v = 1; v <= n; v++) {
        if (T[v]) ly[v] += delta;
        else slack[v] -= delta;
    }
}

// Thuật toán Kuhn-Munkres
int hungarian() {
    fill(match, match + n + 1, -1);
    fill(ly, ly + n + 1, 0);
    for (int i = 1; i <= n; i++) {
        lx[i] = *max_element(w[i] + 1, w[i] + n + 1); // Khởi tạo nhãn lx
    }
    for (int u = 1; u <= n; u++) {
        fill(slack, slack + n + 1, INF);
        while (true) {
            fill(S, S + n + 1, false);
            fill(T, T + n + 1, false);
            if (dfs(u)) break;
            update_labels();
        }
    }
    int maxWeight = 0;
    for (int v = 1; v <= n; v++) {
        if (match[v] != -1) {
            maxWeight += w[match[v]][v];
        }
    }
    return maxWeight;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> w[i][j]; // Trọng số cạnh từ U[i] -> V[j]
        }
    }
    cout << hungarian() << endl;
    return 0;
}
