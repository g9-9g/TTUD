/*
Tóm tắt:
- Tính thời gian hoàn thành sớm nhất cho toàn bộ dự án dựa trên DAG (Directed Acyclic Graph).
- Ứng dụng: Tìm thời gian hoàn thành dự án, xác định đường đi quan trọng nhất (Critical Path).
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005; 
const int MAXM = 200005; 

int n, m;                       
int duration[MAXN];             
vector<int> adj[MAXN];        
bool visited[MAXN];             
vector<int> topo_order;         
int earliest[MAXN];             

void readInput() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> duration[i];
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
}

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) dfs(v);
    topo_order.push_back(u);
}

int topologicalSortDFS() {
    for (int i = 1; i <= n; ++i) if (!visited[i]) dfs(i);
    for (int i = 1; i <= n; ++i) earliest[i] = duration[i];
    reverse(topo_order.begin(), topo_order.end());
    for (int u : topo_order) 
        for (int v : adj[u]) 
            earliest[v] = max(earliest[v], earliest[u] + duration[v]);
    return *max_element(earliest + 1, earliest + n + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    readInput();
    cout << topologicalSortDFS() << '\n';
    return 0;
}
