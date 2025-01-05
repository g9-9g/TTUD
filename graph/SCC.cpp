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
int scc[MAXN]; // scc[u] = số thứ tự của thành phần liên thông mạnh chứa đỉnh u
stack<int> stc; // chung stack
int res = 0;

// kosaraju

vector<int> rev_adj[MAXN];

void dfs1(int u) {
    visited[u] = 1;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v);
        }
    }
    stc.push(u); // tout
}

void dfs2(int u, int cl) {
    visited[u] = 1;
    scc[u] = cl;
    for (int v : rev_adj[u]) {
        if (!visited[v]) {
            dfs2(v, cl);
        }
    }
    // cout << u << " ";
}

int kosaraju () {
    fill (visited, visited + n + 1, 0);
    // create reverse graph
    for (int u = 1;u <= n;u++) {
        for (auto v : adj[u]) {
            rev_adj[v].pb(u);
        }
    }

    for (int u = 1;u <= n;u++) {
        if (!visited[u]) {
            dfs1(u);
        }
    }
    fill (visited, visited + n + 1, 0);

    res = 0;
    while (!stc.empty()) {
        int u = stc.top();
        stc.pop();
        if (!visited[u]) {
            dfs2(u, res++);
        }
    }

    return res;
}


// Tarjan
int tin[MAXN], tout[MAXN], low[MAXN], timer=0;
void dfs3(int u) {
    visited[u] = 1;
    low[u] = tin[u] = timer++;
    stc.push(u);
    for (auto v: adj[u]) {
        if (tin[v] == -1) {
            dfs3(v);
            low[u] = min(low[u], low[v]);
        } else if (visited[v]) {
            low[u] = min(low[u], tin[v]);
        }
    }
    if (low[u] == tin[u]) {
        while (true) {
            int v = stc.top();
            stc.pop();
            visited[v] = 0; // Mark node as removed from the stack
            scc[v] = res; // Mark node with current scc
            if (v == u) break;
        }
        res++;
    }
}

int tarjan() {
    fill(tin, tin + n + 1, -1);
    fill(low, low + n + 1, -1);
    fill(visited, visited + n + 1, 0);
    timer = 0;
    res = 0;

    for (int u = 1;u <= n;u++) {
        if (tin[u] == -1) {
            dfs3(u);
            // cout << endl;
        }
    }
    return res;
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

    // cout << kosaraju() << endl;
    cout << tarjan() << endl;
    // for (int u = 1;u <= n;u++) {
    //     cout << scc[u] << " ";
    // }

    fill(scc, scc + n + 1, 0);

    return 0;
}
