#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

int n;

vector<int> a;

vector <int> mem;
int tmp;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    mem.resize(n+1,-1); // For trace

    vector <int> dp(n+1,0);
    if (n > 10000) goto Onlogn;
    // On^2: dp
    a.resize(n+1,0);
    
    for (int i = 0;i < n;i++) {
        cin >> a[i];
    }
    
    dp[0] = 1;
    for (int i = 0 ;i < n;i++) {
        for (int j = 0;j < i;j++) {
            if (a[j] < a[i]) { // Condition of LIS
                if (dp[j] + 1 > dp[i]) { // With trace
                    dp[i] = dp[j] + 1;
                    mem[i] = j;
                }
                // dp[i] = max(dp[i],dp[j]+1); 
            }
        }
    }
    cout << *max_element(dp.begin(),dp.end()) << endl;
    tmp = max_element(dp.begin(),dp.end()) - dp.begin(); // Last index of element of LIS
    while (tmp != -1) {
        cout << a[tmp] << " "; // will be reverse, can use recursion to print in order
        tmp = mem[tmp];
    }

    // Onlogn: Greedy + Binary search
    Onlogn:
    vector<int> sub, subIndex; // subIndex is for tracing
    for (int i = 0; i < n; ++i) {
        if (sub.empty() || sub[sub.size() - 1] < a[i]) { // Condition of LIS
            if (!sub.empty()) mem[i] = subIndex[sub.size() - 1];
            subIndex.push_back(i); // For tracing
            sub.push_back(a[i]);
        } else {
            // auto it = lower_bound(sub.begin(), sub.end(), a[i]); // Find the index of the first element >= a[i]
            // *it = a[i]; // Replace that number with a[i]

            // For tracing:
            int idx = lower_bound(sub.begin(), sub.end(), a[i]) - sub.begin(); // Only works with normal LIS
            if (idx > 0) mem[i] = subIndex[idx - 1];
            sub[idx] = a[i]; // Replace that number with a[i]
            subIndex[idx] = i;
        }
    }
    tmp = subIndex[sub.size() - 1];
    while (tmp != -1) {
        cout << a[tmp] << " "; // will be reverse, can use recursion to print in order
        tmp = mem[tmp];
    }

    cout << sub.size() << endl;
    return 0;
}

// Test cases: https://leetcode.com/problems/longest-increasing-subsequence/description/