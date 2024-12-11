/*
• Thuật toán Karatsuba nhân nhanh số lớn
• Thuật toán Strassen nhân ma trận
• Rất nhiều thuật toán trong tính toán hình học
• Bao lồi (Convex hull)
• Cặp điểm gần nhất (Closest pair of points)
*/

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define INF (int) 1e9+69
#define MOD 1000000007
#define pb push_back
#define ii pair<int,int>

int n;

// Hàm thực hiện thuật toán Karatsuba
long long karatsuba(long long x, long long y) {
    if (x < 10 || y < 10) return x * y;

    int n = max(to_string(x).size(), to_string(y).size());
    int m = n / 2;

    long long high1 = x / pow(10, m);
    long long low1 = x % (long long)pow(10, m);
    long long high2 = y / pow(10, m);
    long long low2 = y % (long long)pow(10, m);

    long long z0 = karatsuba(low1, low2);
    long long z1 = karatsuba((low1 + high1), (low2 + high2));
    long long z2 = karatsuba(high1, high2);

    return (z2 * pow(10, 2 * m)) + ((z1 - z2 - z0) * pow(10, m)) + z0;
}

// Hàm thực hiện thuật toán Strassen
vector<vector<int>> strassen(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int newSize = n / 2;
        vector<int> inner(newSize);
        vector<vector<int>> 
            a11(newSize, inner), a12(newSize, inner), a21(newSize, inner), a22(newSize, inner),
            b11(newSize, inner), b12(newSize, inner), b21(newSize, inner), b22(newSize, inner),
            c11(newSize, inner), c12(newSize, inner), c21(newSize, inner), c22(newSize, inner),
            p1(newSize, inner), p2(newSize, inner), p3(newSize, inner), p4(newSize, inner),
            p5(newSize, inner), p6(newSize, inner), p7(newSize, inner),
            aResult(newSize, inner), bResult(newSize, inner);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                a11[i][j] = A[i][j];
                a12[i][j] = A[i][j + newSize];
                a21[i][j] = A[i + newSize][j];
                a22[i][j] = A[i + newSize][j + newSize];

                b11[i][j] = B[i][j];
                b12[i][j] = B[i][j + newSize];
                b21[i][j] = B[i + newSize][j];
                b22[i][j] = B[i + newSize][j + newSize];
            }
        }

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                aResult[i][j] = a11[i][j] + a22[i][j];
                bResult[i][j] = b11[i][j] + b22[i][j];
            }
        }
        p1 = strassen(aResult, bResult);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                aResult[i][j] = a21[i][j] + a22[i][j];
            }
        }
        p2 = strassen(aResult, b11);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                bResult[i][j] = b12[i][j] - b22[i][j];
            }
        }
        p3 = strassen(a11, bResult);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                bResult[i][j] = b21[i][j] - b11[i][j];
            }
        }
        p4 = strassen(a22, bResult);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                aResult[i][j] = a11[i][j] + a12[i][j];
            }
        }
        p5 = strassen(aResult, b22);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                aResult[i][j] = a21[i][j] - a11[i][j];
                bResult[i][j] = b11[i][j] + b12[i][j];
            }
        }
        p6 = strassen(aResult, bResult);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                aResult[i][j] = a12[i][j] - a22[i][j];
                bResult[i][j] = b21[i][j] + b22[i][j];
            }
        }
        p7 = strassen(aResult, bResult);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                c12[i][j] = p3[i][j] + p5[i][j];
                c21[i][j] = p2[i][j] + p4[i][j];
            }
        }

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                c11[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
                c22[i][j] = p1[i][j] + p3[i][j] - p2[i][j] + p6[i][j];
            }
        }

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                C[i][j] = c11[i][j];
                C[i][j + newSize] = c12[i][j];
                C[i + newSize][j] = c21[i][j];
                C[i + newSize][j + newSize] = c22[i][j];
            }
        }
    }
    return C;
}

// Hàm thực hiện thuật toán Convex Hull
vector<ii> convexHull(vector<ii>& points) {
    sort(points.begin(), points.end());
    vector<ii> hull;

    for (int i = 0; i < points.size(); i++) {
        while (hull.size() >= 2 && 
               (hull[hull.size() - 1].second - hull[hull.size() - 2].second) * 
               (points[i].first - hull[hull.size() - 1].first) <= 
               (points[i].second - hull[hull.size() - 1].second) * 
               (hull[hull.size() - 1].first - hull[hull.size() - 2].first)) {
            hull.pop_back();
        }
        hull.pb(points[i]);
    }

    int t = hull.size() + 1;
    for (int i = points.size() - 1; i >= 0; i--) {
        while (hull.size() >= t && 
               (hull[hull.size() - 1].second - hull[hull.size() - 2].second) * 
               (points[i].first - hull[hull.size() - 1].first) <= 
               (points[i].second - hull[hull.size() - 1].second) * 
               (hull[hull.size() - 1].first - hull[hull.size() - 2].first)) {
            hull.pop_back();
        }
        hull.pb(points[i]);
    }

    hull.pop_back();
    return hull;
}

// Hàm thực hiện thuật toán cặp điểm gần nhất
double closestPair(vector<ii>& points, int left, int right) {
    if (right - left <= 3) {
        double minDist = INF;
        for (int i = left; i < right; i++) {
            for (int j = i + 1; j < right; j++) {
                double dist = sqrt(pow(points[i].first - points[j].first, 2) + 
                                   pow(points[i].second - points[j].second, 2));
                if (dist < minDist) {
                    minDist = dist;
                }
            }
        }
        return minDist;
    }

    int mid = (left + right) / 2;
    double dl = closestPair(points, left, mid);
    double dr = closestPair(points, mid, right);
    double d = min(dl, dr);

    vector<ii> strip;
    for (int i = left; i < right; i++) {
        if (abs(points[i].first - points[mid].first) < d) {
            strip.pb(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), [](ii a, ii b) { return a.second < b.second; });

    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size() && (strip[j].second - strip[i].second) < d; j++) {
            double dist = sqrt(pow(strip[i].first - strip[j].first, 2) + 
                               pow(strip[i].second - strip[j].second, 2));
            if (dist < d) {
                d = dist;
            }
        }
    }

    return d;
}

int main() {
    // Ví dụ sử dụng thuật toán Karatsuba
    long long x = 123456789;
    long long y = 987654321;
    cout << "Karatsuba: " << karatsuba(x, y) << endl;

    // Ví dụ sử dụng thuật toán Strassen
    vector<vector<int>> A = {{1, 2}, {3, 4}};
    vector<vector<int>> B = {{5, 6}, {7, 8}};
    vector<vector<int>> C = strassen(A, B);
    cout << "Strassen: " << endl;
    for (auto row : C) {
        for (auto val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Ví dụ sử dụng thuật toán Convex Hull
    vector<ii> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    vector<ii> hull = convexHull(points);
    cout << "Convex Hull: " << endl;
    for (auto p : hull) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }

    // Ví dụ sử dụng thuật toán cặp điểm gần nhất
    vector<ii> points2 = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    sort(points2.begin(), points2.end());
    cout << "Closest Pair: " << closestPair(points2, 0, points2.size()) << endl;

    return 0;
}