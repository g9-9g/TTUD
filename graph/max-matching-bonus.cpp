#include <bits/stdc++.h>
using namespace std;

/*


*/


const int MAXN = 1005;  // Số đỉnh tối đa cho U và V
const int INF = 1e9;    // Giá trị "vô cực" để đại diện năng lực lớn

int n, m, k;                  // Số đỉnh U, V và giới hạn k
int capacity[MAXN][MAXN];     // Ma trận năng lực
int cost[MAXN][MAXN];         // Ma trận trọng số
vector<int> adj[MAXN * 2];    // Danh sách kề

// Hàm Bellman-Ford để tìm đường đi ngắn nhất (giảm chi phí)
bool bellman_ford(int s, int t, vector<int>& parent, vector<int>& dist) {
    fill(dist.begin(), dist.end(), INF);
    dist[s] = 0;
    parent[s] = -1;

    queue<int> q;
    vector<bool> in_queue(t + 1, false);
    q.push(s);
    in_queue[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && dist[v] > dist[u] + cost[u][v]) {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u;
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
    return dist[t] != INF;
}

// Hàm tìm Maximum Weight Matching với ràng buộc k
int min_cost_max_flow(int s, int t) {
    int max_flow = 0, min_cost = 0;
    vector<int> parent(t + 1), dist(t + 1);

    // Lặp tìm augmenting path
    while (bellman_ford(s, t, parent, dist)) {
        // Tìm năng lực nhỏ nhất trên augmenting path
        int flow = INF;
        for (int v = t; v != s; v = parent[v]) {
            flow = min(flow, capacity[parent[v]][v]);
        }

        // Cập nhật năng lực và chi phí
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= flow;
            capacity[v][u] += flow;
            min_cost += flow * cost[u][v];
        }
        max_flow += flow;
    }
    return min_cost; // Trả về tổng trọng số tối đa
}

int main() {
    cin >> n >> m >> k;

    // Khởi tạo nguồn (s) và đích (t)
    int s = 0, t = n + m + 1;

    // Đọc input trọng số các cạnh
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int w;
            cin >> w;
            if (w > 0) {
                adj[i].push_back(n + j);
                adj[n + j].push_back(i);
                capacity[i][n + j] = 1; // Task chỉ được ghép tối đa 1 lần
                cost[i][n + j] = -w;   // Trọng số lớn -> chi phí nhỏ
                cost[n + j][i] = w;    // Chi phí ngược
            }
        }
    }

    // Thêm cạnh từ nguồn (s) đến các task (U)
    for (int i = 1; i <= n; i++) {
        adj[s].push_back(i);
        adj[i].push_back(s);
        capacity[s][i] = 1; // Mỗi task chỉ ghép 1 lần
    }

    // Thêm cạnh từ mỗi staff (V) đến đích (t)
    for (int j = 1; j <= m; j++) {
        adj[n + j].push_back(t);
        adj[t].push_back(n + j);
        capacity[n + j][t] = k; // Giới hạn k staff trên mỗi V
    }

    // Tìm trọng số lớn nhất (dạng bài toán Min-Cost Max-Flow)
    cout << -min_cost_max_flow(s, t) << endl;

    return 0;
}
