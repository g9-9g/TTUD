#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

vector <vector<int>> dp;

/*
LCS:
    dp[i][j] = length of the longest common subsequence of s1[0..i-1] and s2[0..j-1]
    dp[i][j] = dp[i-1][j-1] + 1 if s1[i-1] == s2[j-1]
    dp[i][j] = max(dp[i-1][j], dp[i][j-1]) otherwise
*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0); 

    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size();
    int m = s2.size();

    dp.resize(n+1, vector<int>(m+1, 0));  


    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= m;j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    cout << dp[n][m] << endl;   

    return 0;
}

// Test cases: https://leetcode.com/problems/longest-common-subsequence/description/