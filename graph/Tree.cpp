#include <bits/stdc++.h>

using namespace std;

#define MAXN (int) 1e5+69
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

int n,m;

vector <ii> adj[MAXN];

// int adj_matrix[MAXN][MAXN];

int visited[MAXN];

int d[MAXN];


void dfs(int u) {
    visited[u] = 1;

    for (auto obj : adj[u]) {
        int v = obj.first;
        int w = obj.second;
        if (!visited[v]) {
            d[v] = d[u] + w;
            dfs(v);
        }
    }
}



void printa(int *arr, int n) {
    for (int i = 1;i <= n;i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int max_d_tree () {
    fill(d,d+n+1, 0);
    dfs(1);

    int u = max_element(d+1, d+n+1) - d;
    // cout << u << endl;
    fill(d,d+n+1, 0);
    fill(visited,visited+n+1,0);
    dfs(u);
    
    cout << *max_element(d+1, d+n+1) << endl;

    return 0;
}


// Sum tree
int c[MAXN]; // number of children of node i
int f[MAXN]; // sum of distance from node i to all its children

void dfs1(int u) {
    visited[u] = 1;

    for (auto obj : adj[u]) {
        int v = obj.first;
        int w = obj.second;
        if (!visited[v]) {
            dfs1(v);
            d[u] += d[v] + w*c[v];
            c[u] += c[v];
        }
    }
}

void dfs2(int u) {
    visited[u] = 1;

    for (auto obj : adj[u]) {
        int v = obj.first;
        int w = obj.second;
        if (!visited[v]) {
            int F = f[u] - (d[v] + c[v]*w);
            f[v] = d[v] + (F + w*(n-c[v]));
            dfs2(v);
        }
    }
}

int sum_d_tree() {
    fill(d,d+n+1, 0);
    fill(c,c+n+1, 1);
    fill(visited,visited+n+1,0);
    fill(f,f+n+1,0);

    dfs1(1);
    fill(visited,visited+n+1,0);
    f[1] = d[1];
    dfs2(1);
    // printa(f,n);
    return *max_element(f+1, f+n+1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


    cin >> n;

    for (int i = 0;i < n-1;i++) {
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].pb({v,w});
        adj[v].pb({u,w});
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

    cout << sum_d_tree() << endl;
    // printa(d, n);

    return 0;
}
