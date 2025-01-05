#include <bits/stdc++.h>

using namespace std;

#define MAXN (int) 1e4+69
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

int n,m;

vector <int> adj[MAXN];

int adj_matrix[MAXN][MAXN];

int visited[MAXN];

int ranked[MAXN];


void dfs(int u) {
    visited[u] = 1;

    for (int v : adj[u]) {
        if (!visited[v]) {
            ranked[v] = ranked[u] + 1;
            dfs(v);
        }
    }
}

void bfs(int s) {
    queue <int> q;
    q.push(s);
    visited[s] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : adj[u]) {
            if (!visited[v]) {
                visited[v] = 1;
                q.push(v);
            }
        }
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
        adj[u].pb(v); // 2 way
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

    for (int i = 1;i <= n;i++) {
        if (!visited[i]) {
            ranked[1] = 1;
            dfs(1);
        }
    }



    printa(ranked, n);

    return 0;
}
