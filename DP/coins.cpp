/*
Given an integer array of coins[] of size n representing different types of denominations and an integer sum, the task is to count all combinations of coins to make a given value sum.  
The same coin can be used any number of times.

DP:
if (sum-coins[i]) is greater than 0, then dp[i][sum] = dp[i][sum-coins[i]] + dp[i-1][sum].
else dp[i][sum] = dp[i-1][sum].

*/


#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

int n, sm;

vector<int> coins;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> sm;
    coins.resize(n+1,0);
    for (int i = 0;i < n;i++) {
        cin >> coins[i];
    }
    
    vector<vector<int> > dp(n + 1, vector<int>(sm + 1, 0));
    // Represents the base case where the target sum is 0,
    // and there is only one way to make change: by not
    // selecting any coin
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= sm; j++) {
            // Add the number of ways to make change without
            // using the current coin,
            dp[i][j] += dp[i - 1][j];
            if ((j - coins[i - 1]) >= 0) {
                // Add the number of ways to make change
                // using the current coin
                dp[i][j] += dp[i][j - coins[i - 1]];
            }
        }
    }
    cout << dp[n][sm] << endl;

    return 0;
}