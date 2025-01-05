#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;       // Số đỉnh tối đa
const int INF = 1e9;        // Giá trị đại diện "vô cực"

int capacity[MAXN][MAXN];   // Ma trận dung lượng của các cạnh
int residual[MAXN][MAXN];   // Ma trận dung lượng còn dư
int parent[MAXN];           // Mảng lưu đường đi trong BFS
int n;                      // Số đỉnh

// BFS tìm đường đi tăng luồng từ source đến sink
bool bfs(int source, int sink) {
    fill(parent, parent + n + 1, -1); // Khởi tạo các đỉnh chưa được duyệt
    vector<bool> visited(n + 1, false);
    queue<int> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v = 1; v <= n; v++) {
            if (!visited[v] && residual[u][v] > 0) { // Cạnh có dung lượng còn dư
                parent[v] = u;                       // Lưu vết
                visited[v] = true;
                if (v == sink) return true;         // Tìm thấy đỉnh đích
                q.push(v);
            }
        }
    }
    return false; // Không tìm thấy đường đi từ source đến sink
}

// Thuật toán Ford-Fulkerson
int fordFulkerson(int source, int sink) {
    // Khởi tạo đồ thị còn dư từ ma trận dung lượng
    memcpy(residual, capacity, sizeof(capacity));

    int maxFlow = 0; // Lưu tổng luồng cực đại

    // Khi còn đường đi tăng luồng từ source đến sink
    while (bfs(source, sink)) {
        // Tìm luồng tăng thêm nhỏ nhất trên đường đi
        int pathFlow = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residual[u][v]);
        }

        // Cập nhật đồ thị còn dư
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= pathFlow; // Giảm dung lượng theo chiều thuận
            residual[v][u] += pathFlow; // Tăng dung lượng theo chiều ngược
        }

        maxFlow += pathFlow; // Cộng luồng tăng thêm vào tổng luồng
    }

    return maxFlow;
}

// Thuật toán Edmonds-Karp
int edmondsKarp(int source, int sink) {
    // Khởi tạo đồ thị còn dư từ ma trận dung lượng
    memcpy(residual, capacity, sizeof(capacity));

    int maxFlow = 0; // Lưu tổng luồng cực đại

    // Khi còn đường đi tăng luồng từ source đến sink
    while (bfs(source, sink)) {
        // Tìm luồng tăng thêm nhỏ nhất trên đường đi
        int pathFlow = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residual[u][v]);
        }

        // Cập nhật đồ thị còn dư
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= pathFlow; // Giảm dung lượng theo chiều thuận
            residual[v][u] += pathFlow; // Tăng dung lượng theo chiều ngược
        }

        maxFlow += pathFlow; // Cộng luồng tăng thêm vào tổng luồng
    }

    return maxFlow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int m; // Số cạnh
    cin >> n >> m; // Nhập số đỉnh và số cạnh

    // Nhập ma trận dung lượng
    memset(capacity, 0, sizeof(capacity));
    for (int i = 0; i < m; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;
        capacity[u][v] += cap; // Nếu có nhiều cạnh từ u đến v, cộng dồn dung lượng
    }

    int source, sink;
    cin >> source >> sink; // Nhập đỉnh nguồn và đỉnh đích

    cout << edmondsKarp(source, sink) << endl;

    return 0;
}
