/*
Given a material having the shape rectangle with height H and width W. We need to cut this material into n smaller rectangle submaterials of size (h1,w1), (h2, w2), ..., (hn, wn). Write a program to check if we can perform this cut.
Input
    Line 1: contains two positive integers H, W (1 <= H, W <= 10)
    Line 2: contains a positive integer n (1 <= n <= 10)
    Line i+2 (i= 1,...,n): contains two positive integer hi and wi (1 <= hi, wi <= 10)
Output
    Write 1 if we can perform the cut and write 0, otherwise.
*/

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define long long int
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>


// Global variables
int H, W, n;
vector<ii> rects;
bool used[10][10];  // to mark the used area of the material
bool found = false; // to store if a solution has been found

// Check if we can place a rectangle (h, w) at position (x, y)
bool canPlace(int x, int y, int h, int w) {
    if (x + h > H || y + w > W) return false; // Check if it fits within the material
    for (int i = x; i < x + h; i++) {
        for (int j = y; j < y + w; j++) {
            if (used[i][j]) return false; // If space is already occupied
        }
    }
    return true;
}

// Place a rectangle (h, w) at position (x, y)
void place(int x, int y, int h, int w, bool state) {
    for (int i = x; i < x + h; i++) {
        for (int j = y; j < y + w; j++) {
            used[i][j] = state;
        }
    }
}

// Backtracking function Try(k)
void Try(int k) {
    if (k == n) {      // All rectangles are placed successfully
        found = true;
    }

    int h = rects[k].first;
    int w = rects[k].second;

    // Try to place the rectangle in all positions and orientations
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            // Try placing the rectangle in the original orientation (h, w)
            if (canPlace(i, j, h, w)) {
                place(i, j, h, w, true); // Mark space as used
                Try(k + 1);              // Try to place the next rectangle
                place(i, j, h, w, false); // Unmark space (backtrack)
            }
            // Try placing the rectangle in the rotated orientation (w, h)
            if (canPlace(i, j, w, h)) {
                place(i, j, w, h, true); // Mark space as used
                Try(k + 1);              // Try to place the next rectangle
                place(i, j, w, h, false); // Unmark space (backtrack)
            }
        }
    }
}

int main() {
    cin >> H >> W;
    cin >> n;
    rects.resize(n);
    for (int i = 0; i < n; i++) {
        int hi, wi;
        cin >> hi >> wi;
        rects[i] = {hi, wi};
    }

    Try(0); // Start backtracking from the first rectangle

    if (found)
        cout << 1 << endl; // If solution found, print 1
    else
        cout << 0 << endl; // Otherwise, print 0

    return 0;
}
