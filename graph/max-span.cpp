#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005; // Số công việc tối đa
const int MAXM = 200005; // Số ràng buộc tối đa

int n, m;                       // Số công việc và số ràng buộc
int duration[MAXN];             // Thời gian hoàn thành mỗi công việc
vector<int> adj[MAXN];        // Danh sách kề lưu các ràng buộc
bool visited[MAXN];             // Mảng đánh dấu đã thăm
vector<int> topo_order;         // Danh sách lưu thứ tự topo
int earliest[MAXN];             // Thời gian hoàn thành sớm nhất của mỗi công việc

void readInput() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> duration[i]; // Nhập thời gian hoàn thành của công việc i
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); // Công việc v phụ thuộc vào công việc u
    }
}

// Hàm DFS để thực hiện Topological Sort
void dfs(int u) {
    visited[u] = true;

    // Duyệt qua các đỉnh phụ thuộc vào u
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }

    // Thêm đỉnh vào danh sách topo_order sau khi hoàn thành DFS
    topo_order.push_back(u);
}

int topologicalSortDFS() {
    // Bước 1: Duyệt qua tất cả các đỉnh để thực hiện DFS
    // Đảm bảo rằng tất cả các đỉnh trong đồ thị đều được duyệt, kể cả khi đồ thị không liên thông
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i); // DFS để sắp xếp các đỉnh theo thứ tự topo
        }
    }

    // Bước 2: Khởi tạo thời gian hoàn thành sớm nhất
    // Với mỗi công việc, thời gian hoàn thành sớm nhất ban đầu là chính thời gian hoàn thành nó
    for (int i = 1; i <= n; ++i) {
        earliest[i] = duration[i]; // Mỗi công việc ban đầu cần ít nhất "duration[i]" để hoàn thành
    }

    // Bước 3: Duyệt qua thứ tự topo
    // Thứ tự topo được lưu ngược trong topo_order vì DFS thêm đỉnh vào cuối sau khi duyệt
    reverse(topo_order.begin(), topo_order.end()); // Đảo ngược để duyệt đúng thứ tự topo
    for (int u : topo_order) { // Với mỗi đỉnh u trong thứ tự topo
        // Duyệt tất cả các công việc phụ thuộc vào u
        for (int v : adj[u]) { 
            // Cập nhật thời gian hoàn thành sớm nhất của v
            // Thời gian này phụ thuộc vào thời gian hoàn thành của u cộng thêm thời gian cần thiết để hoàn thành v
            earliest[v] = max(earliest[v], earliest[u] + duration[v]);
        }
    }

    // Bước 4: Tìm thời gian hoàn thành toàn bộ dự án
    // Thời gian hoàn thành toàn bộ dự án là thời gian hoàn thành sớm nhất của công việc kết thúc muộn nhất
    int max_time = 0;
    for (int i = 1; i <= n; ++i) {
        max_time = max(max_time, earliest[i]);
    }

    return max_time; // Trả về thời gian hoàn thành toàn bộ dự án
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    readInput();
    cout << topologicalSortDFS() << '\n';

    return 0;
}