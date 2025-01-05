/*
Mở rộng của knapsack problem

A truck is planned to arrive at some stations among N stations 1, 2, . . ., N located on a line. Station i (i = 1,…,N) has coordinate i and has following information
ai : amount of goods
ti: pickup time duration for taking goods
The route of the truck is a sequence of stations x1 < x2 < . . . < xk (1 ≤ xj ≤ N, j = 1,…, k). 
Due to technical constraints, the distance between two consecutive stations that the truck arrives xi and xi+1 is less than or equal 
to D and the total pickup time duration cannot exceed T. Find a route for the truck such that total amount of goods picked up is maximal.

*/

#include <bits/stdc++.h>
using namespace std;

int dp[1001][101];
int N, T, D;
int res = 0;

int main() {
    cin >> N >> T >> D;
    vector<int> a(N), t(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> t[i];
    }

    for (int i = 0; i < N; i++) {
        if (t[i] <= T) {
            dp[i][t[i]] = a[i];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int time = 0; time <= T;time++) {
            if (dp[i][time] == 0) continue;
            for (int j = i + 1; j <= i + D && j < N; j++) {
                if (time + t[j] <= T) { // condition
                    dp[j][time + t[j]] = max(dp[j][time + t[j]], dp[i][time] + a[j]);
                }
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int time = 0; time <= T; ++time) {
            res = max(res, dp[i][time]);
        }
    }
    cout << res << endl;
    return 0;
}