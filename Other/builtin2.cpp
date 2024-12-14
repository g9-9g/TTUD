/*
Sort, binary search,...
*/

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

bool customCompare(int a, int b) {
    return a > b;
}

void _syntax() {
    vector<int> v;
    sort(v.begin(), v.end()); // sort in ascending order

    // Sort with compare function
    sort(v.begin(), v.end(), customCompare);
    *lower_bound(v.begin(), v.end(), 5, customCompare); // lower bound custom fun
}

int binary_search() {
    vector<int> v;
    sort(v.begin(), v.end());
    int x = 5;
    int l = 0;
    int r = v.size() - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (v[mid] == x) return mid;
        if (v[mid] < x) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

int lwb() {
    vector<int> v;
    sort(v.begin(), v.end());
    int x = 5;
    int l = 0;
    int r = v.size() - 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (v[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

int ub() {
    vector<int> v;
    sort(v.begin(), v.end());
    int x = 5;
    int l = 0;
    int r = v.size() - 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (v[mid] > x) r = mid; // 
        else l = mid + 1;
    }
    return l;
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
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
    mergeSort(a, 0, n - 1);


    return 0;
}