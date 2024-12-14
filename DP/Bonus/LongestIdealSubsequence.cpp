// Problem: https://leetcode.com/problems/longest-ideal-subsequence/description/


#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

int k;

string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> s >> k;
    int n = s.size();
    unordered_map <int, int> dp; // dp hash map
    for (int i = 0;i < n;i++) {
        // dp[s[i]]++;
        for (int j = max((int)'a', s[i] - k);j <= min((int)'z', s[i] + k);j++) {
            dp[s[i]] = max(dp[j],dp[s[i]]);
        }
        dp[s[i]] ++;
        // cout << dp[s[i]] << endl;
    }
    int res = 0;
    for (int i = 0;i < n;i++) {
        res = max(res, dp[s[i]]);
    }
    cout << res << endl;
    return 0;
}