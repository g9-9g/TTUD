#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;       // Số đỉnh tối đa
const int INF = 1e9;        // Giá trị đại diện "vô cực"

struct Edge {
    int v, capacity, cost, flow, rev;
};

vector<Edge> graph[MAXN];
int dist[MAXN], parent[MAXN], parentEdge[MAXN];
bool inQueue[MAXN];

// Thêm cạnh vào đồ thị
void addEdge(int u, int v, int capacity, int cost) {
    Edge a = {v, capacity, cost, 0, (int)graph[v].size()};
    Edge b = {u, 0, -cost, 0, (int)graph[u].size()};
    graph[u].push_back(a);
    graph[v].push_back(b);
}

// Tìm đường đi ngắn nhất (chi phí nhỏ nhất) từ source đến sink (SPFA)
bool spfa(int source, int sink, int n) {
    fill(dist, dist + n + 1, INF);
    fill(inQueue, inQueue + n + 1, false);
    queue<int> q;

    dist[source] = 0;
    q.push(source);
    inQueue[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (int i = 0; i < graph[u].size(); i++) {
            Edge &e = graph[u][i];
            if (e.flow < e.capacity && dist[e.v] > dist[u] + e.cost) {
                dist[e.v] = dist[u] + e.cost;
                parent[e.v] = u;
                parentEdge[e.v] = i;
                if (!inQueue[e.v]) {
                    q.push(e.v);
                    inQueue[e.v] = true;
                }
            }
        }
    }

    return dist[sink] != INF; // Có đường đi từ source đến sink
}

// Thuật toán Min-Cost Max-Flow
pair<int, int> minCostMaxFlow(int source, int sink, int n) {
    int maxFlow = 0, minCost = 0;

    while (spfa(source, sink, n)) {
        // Tìm luồng tăng thêm nhỏ nhất trên đường đi
        int pathFlow = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            int idx = parentEdge[v];
            pathFlow = min(pathFlow, graph[u][idx].capacity - graph[u][idx].flow);
        }

        // Cập nhật luồng và chi phí
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            int idx = parentEdge[v];
            graph[u][idx].flow += pathFlow;
            graph[v][graph[u][idx].rev].flow -= pathFlow;
            minCost += pathFlow * graph[u][idx].cost;
        }

        maxFlow += pathFlow;
    }

    return {maxFlow, minCost};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m; // Nhập số đỉnh và số cạnh

    for (int i = 0; i < m; i++) {
        int u, v, capacity, cost;
        cin >> u >> v >> capacity >> cost;
        addEdge(u, v, capacity, cost); // Thêm cạnh với dung lượng và chi phí
    }

    int source, sink;
    cin >> source >> sink; // Nhập đỉnh nguồn và đỉnh đích

    pair<int, int> result = minCostMaxFlow(source, sink, n);
    cout << "Max Flow: " << result.first << "\n";
    cout << "Min Cost: " << result.second << "\n";

    return 0;
}
