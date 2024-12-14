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

/*
Maximum Subarray Sum - Kadane Algorithm
*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    a.resize(n+1,0);
    for (int i = 0;i < n;i++) {
        cin >> a[i];
    }

    int res = 0;
    int cur_sum = 0;

    for (int i = 0; i < n;i++) {
        cur_sum += a[i];
        if (cur_sum < 0) {
            cur_sum = 0;
        } else {
            if (cur_sum % 2 == 0) res = max(res, cur_sum);
        }
    }
    cout << res << endl;

    return 0;
}