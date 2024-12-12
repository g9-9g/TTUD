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
    unordered_map <int, int> mp;
    for (int i = 0;i < n;i++) {
        // mp[s[i]]++;
        for (int j = max((int)'a', s[i] - k);j <= min((int)'z', s[i] + k);j++) {
            mp[s[i]] = max(mp[j],mp[s[i]]);
        }
        mp[s[i]] ++;
        // cout << mp[s[i]] << endl;
    }
    int res = 0;
    for (int i = 0;i < n;i++) {
        res = max(res, mp[s[i]]);
    }
    cout << res << endl;
    return 0;
}