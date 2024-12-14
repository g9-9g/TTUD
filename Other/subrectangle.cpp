/*
A Rectangle of size n x mis divided into unit-square 1 x 1 with two colors black and white. The rectangle is represented by a matrix A(nx m) in which A(i, j) = 1 means that the unit-square at row i, column jis black and A(i, j) = 0 means that the unit-square at row icolumn jis white.
Find the sub-rectangle of the given rectangle containing only black unit-squares such that the area is maximal.
Input
•Line 1: contains 2 positive integers nand m(1 <= n, m<= 1000)
•Line i+1 (i= 1,…, n): contains the ith of the matrix A
Output
Write the area of the sub-rectangle found.
*/

#include<bits/stdc++.h>
using namespace std;

int maxHistogramArea(vector<int>& heights) {
    stack<int> s;
    int max_area = 0;
    int index = 0;
    int n = heights.size();
    
    while (index < n) {
        if (s.empty() || heights[s.top()] <= heights[index]) {
            s.push(index++);
        } else {
            int top = s.top();
            s.pop();
            int area = heights[top] * (s.empty() ? index : index - s.top() - 1);
            max_area = max(max_area, area);
        }
    }
    
    while (!s.empty()) {
        int top = s.top();
        s.pop();
        int area = heights[top] * (s.empty() ? index : index - s.top() - 1);
        max_area = max(max_area, area);
    }
    
    return max_area;
}

int maxRectangle(vector<vector<int>>& matrix) {
    if (matrix.empty()) return 0;
    
    int n = matrix.size();
    int m = matrix[0].size();
    vector<int> heights(m, 0);
    int max_area = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == 0) {
                heights[j] = 0;
            } else {
                heights[j]++;
            }
        }
        max_area = max(max_area, maxHistogramArea(heights));
    } 
    return max_area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }
    
    cout << maxRectangle(matrix) << endl;
    return 0;
}
