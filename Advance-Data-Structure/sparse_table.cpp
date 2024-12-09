#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class SparseTable {
    vector<vector<int>> table;
    vector<int> log;

public:
    SparseTable(const vector<int>& arr) {
        int n = arr.size();
        int k = log2(n) + 1;
        table.resize(n, vector<int>(k));
        log.resize(n + 1);

        // Precompute log values
        log[1] = 0;
        for (int i = 2; i <= n; i++) {
            log[i] = log[i / 2] + 1;
        }

        // Build Sparse Table
        for (int i = 0; i < n; i++) {
            table[i][0] = arr[i];
        }
        for (int j = 1; j <= log[n]; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]); // Change here for sum
            }
        }
    }

    int query(int L, int R) {
        int j = log[R - L + 1];
        return min(table[L][j], table[R - (1 << j) + 1][j]); // Change here for sum
    }
};

int main() {
    vector<int> arr = {1, 3, 2, 7, 9, 11};
    SparseTable st(arr);

    cout << "Minimum in range [1, 3]: " << st.query(1, 3) << endl;
    cout << "Minimum in range [0, 5]: " << st.query(0, 5) << endl;

    return 0;
}

/*
build: O(nlogn)
query: O(1)
-> cannot update
*/