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
Minimum Size Subarray Sum
Given an array of positive integers nums and a positive integer target, return the minimal length of a 
subarray whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.
*/
int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size();
    vector<int> pre(n+1);
    int res = INT_MAX;
    for (int i = 0; i < n ;i ++) {
        pre[i+1] = pre[i] + nums[i];
        cout << pre[i+1] << " ";
    }

    for (int i = 0; i <= n; i++) {
        int lbt = pre[i] - target;
        if (lbt < 0) continue;
        int j = upper_bound(pre.begin(), pre.begin() + i, lbt) - pre.begin();
        if (j != -1) {
            res = min(res, i - j + 1);
        }
    }

    return res == INT_MAX ? 0 : res;
}

/*
Given an array of integers nums and an integer k, return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.
*/
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k == 0) return 0;
    int prod = 1;
    int count = 0;
    int left =0; int n = nums.size();
    for (int right = 0; right < n; right++) {
        prod *= nums[right];

        while (prod >= k && left <= right) {
            prod = prod / nums[left];
            left++;
        }

        count+= right - left + 1;
    }

    return count;
}

/*
Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.
A subarray is a contiguous part of an array.
*/

int subarraysDivByK(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> pref (n+1, 0);
    unordered_map<int, int> m;
    m[0] = 1;
    int cnt = 0;
    for (int i = 0;i < n;i++) {
        pref[i+1] = pref[i] + nums[i];
        pref[i+1] %= k;
        if (pref[i+1] < 0) pref[i+1] += k;
        cnt+= m[pref[i+1]];
        m[pref[i+1]]++;
    }

    
    return cnt;
    
}

/*
Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.
A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:
0 <= i, j < nums.length
i != j
|nums[i] - nums[j]| == k
*/

int findPairs(vector<int>& nums, int k) {
    unordered_map<int, bool> m;
    int n = nums.size();
    int cnt = 0;

    if (k == 0) {
        unordered_map<int, int> mp;
        for (int i = 0;i < n;i++) {
            mp[nums[i]]++;
        }

        for (auto x : mp) {
            if (x.second >= 2) cnt++;
        }
        return cnt;
    }

    for (int i = 0; i < n; i++) {
        if (m[nums[i]]) continue;            
        int target1 = nums[i] - k;
        int target2 = nums[i] + k;

        cnt += m[target1] + m[target2];
        
        m[nums[i]] = true;
    }

    return cnt;
}

/*
VERY HARD
Given an integer array nums and an integer k, return the number of good subarrays of nums.
A good array is an array where the number of different integers in that array is exactly k.
For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.
A subarray is a contiguous part of an array.
*/

int subarraysWithKDistinctSub (vector <int> & nums, int k) {
    unordered_map<int, int> freq;
    int count = 0; int n = nums.size();

    int left = 0;
    for (int right = 0; right < n; right++) {
        freq[nums[right]]++;
        while (freq.size() > k) {
            freq[nums[left]]--;
            if (freq[nums[left]] == 0) freq.erase(nums[left]);
            left++;
        }

        count += right - left + 1;
    }

    return count;
}

int subarraysWithKDistinct(vector<int>& nums, int k) {
    return subarraysWithKDistinctSub(nums, k) - subarraysWithKDistinctSub(nums, k-1);
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    a.resize(n+1,0);
    for (int i = 0;i < n;i++) {
        cin >> a[i];
    }


    return 0;
}