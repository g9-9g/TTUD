/*
GREEDY ALGORITHM
Given a set of segments X = {(a1, b1), . . . , (an, bn)} in which ai < bi are coordinates of the segment i on a line, i = 1, …, n.  Find a subset of X having largest cardinality in which no two segments of the subset intersect
Input
Line 1: contains a positive integer n (1 <= n <= 100000)
Line i+1 (i= 1,...,n): contains ai and bi (0 <= ai <= bi <= 1000000)
Output
Number of segments in the solution found.

Sort theo second -> tham
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
vector <pair <int, int>> segment;
bool sortbysec(const pair<int,int> &a, const pair<int,int> &b)
{
    return (a.second < b.second);
}
 
int solve(int n) {
    int count = 0, last = -1;
    for (int i = 0; i < n; i++) {
        if (segment[i].first > last) {
            count++;
            last = segment[i].second;
        }
    }
    return count;
}
 
int main () {
    int n;
    cin >> n;
    segment.resize(n);
    for (int i = 0; i < n; i++)
        cin >> segment[i].first >> segment[i].second;
    sort(segment.begin(), segment.end(), sortbysec);
    cout << solve(n);
    return 0;
}
