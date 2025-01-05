#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005; // Số tasks tối đa
const int MAXM = 10005; // Số staffs tối đa

vector<int> adj[MAXN]; // Danh sách kề biểu diễn đồ thị hai phía
int match[MAXM];       // match[v]: staff v đang được gán cho task nào
bool visited[MAXM];    // visited[v]: đánh dấu staff đã được thăm trong DFS

// Tìm augmenting path bằng DFS
bool dfs(int task) {
    for (int staff : adj[task]) {
        if (visited[staff]) continue; // Nếu staff đã được thăm, bỏ qua
        visited[staff] = true;        // Đánh dấu đã thăm staff

        // Nếu staff chưa được gán hoặc tìm được augmenting path
        if (match[staff] == -1 || dfs(match[staff])) {
            match[staff] = task; // Gán staff cho task
            return true;         // Đường đi tăng luồng được tìm thấy
        }
    }
    return false; // Không tìm thấy đường đi tăng luồng
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    // Đọc input
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k; // Số staff có thể làm task i
        while (k--) {
            int staff;
            cin >> staff;
            adj[i].push_back(staff); // Thêm cạnh task -> staff
        }
    }

    // Khởi tạo
    fill(match, match + m + 1, -1); // Chưa có staff nào được gán

    int maxMatch = 0; // Số lượng task được gán tối đa

    // Thử tìm augmenting path cho từng task
    for (int i = 1; i <= n; i++) {
        fill(visited, visited + m + 1, false); // Reset visited trước mỗi DFS
        if (dfs(i)) maxMatch++; // Nếu tìm được augmenting path, tăng số ghép cặp
    }

    // Output kết quả
    cout << maxMatch << endl;

    return 0;
}
