#include <bits/stdc++.h>

using namespace std;

#define MAXN (int) 1e5+69
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

int n,m;

vector <int> adj[MAXN];

// int adj_matrix[MAXN][MAXN];

int visited[MAXN];

int tin[MAXN], tout[MAXN], low[MAXN], timer=0;

/*
Dành riêng cho đồ thị VÔ HƯỚNG

tin[u] = thời gian duyệt đến đỉnh u
tout[u] = thời gian kết thúc điểm u, dùng trong topo sort
low[u]: là thời điểm sớm nhất mà đỉnh u hoặc bất kỳ con cháu nào của nó có thể "quay lại" tổ tiên thông qua các cạnh ngược (Back Edge) hoặc các cạnh khác.
*/


// bridges: Cầu là một cạnh của đồ thị, nếu loại bỏ cạnh này khỏi đồ thị sẽ làm tăng số thành phần liên thông.
vector <ii> bridges;


// articulation point: đỉnh được gọi là khớp nếu như loại bỏ đỉnh này và các cạnh liên thuộc với nó ra khỏi đồ thị thì số thành phần liên thông của đồ thị tăng lên.
bool isArticulation[MAXN];

void dfs(int u, int parent) {
    visited[u] = 1;

    tin[u] = low[u] = timer++;
    int children = 0; // Số lượng con trực tiếp của đỉnh u trong cây DFS

    for (int v : adj[u]) {
        if (v == parent) continue;
        if (!visited[v]) {
            // Tree Edge
            cout << u << " -> " << v << " is a Tree Edge" << endl;

            children++;
            dfs(v, u);

            low[u] = min(low[u], low[v]);

            // Kiểm tra điều kiện cầu
            if (low[v] > tin[u]) {
                bridges.pb({u, v});
            }

            // Kiểm tra điều kiện đỉnh khớp
            if (low[v] >= tin[u] && parent != -1) {
                isArticulation[u] = true;
            }

        } else {
            if (tin[v] < tin[u]) {
                // Back Edge
                cout << u << " -> " << v << " is a Back Edge" << endl;
            } else if (tin[v] > tin[u]) {
                // Forward Edge
                cout << u << " -> " << v << " is a Forward Edge" << endl;
            } else {
                // Crossing Edge
                cout << u << " -> " << v << " is a Crossing Edge" << endl;
            }

            // bridge & articulation point

            low[u] = min(low[u], tin[v]);
        }
    }
    tout[u] = timer++;


    // Kiểm tra điều kiện cho gốc của cây DFS
    if (parent == -1 && children > 1) {
        isArticulation[u] = true;
    }
}



void printa(int *arr, int n) {
    for (int i = 1;i <= n;i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


    cin >> n >> m;

    for (int i = 1;i <= m;i++) {
        int u,v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }



    // adj matrix input

    /*
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= n;j++) {
            int x; // weight of edge i->j
            cin >> x;
            adj_matrix[i].pb(x);
        }
    }
    */

    fill(tin, tin + n + 1, -1);
    fill(low, low + n + 1, -1);


    for (int i = 1;i <= n;i++) {
        if (!visited[i]) {
            dfs(i,-1);
        }
    }

    for (auto x : bridges) {
        cout << x.first << " " << x.second << endl;
    }

    int res = 0;
    for (int i = 1;i <= n;i++) {
        if (isArticulation[i]) {
            cout << i << " is an articulation point" << endl;
            res++;
        }
    }
    cout << res << " " << bridges.size() << endl;

    return 0;
}
