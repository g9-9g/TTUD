#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

/*
Thêm mảng thời gian:

time[mask][i]: Thời gian đến thành phố i sau khi đi qua các thành phố trong mask.
Kiểm tra ràng buộc thời gian:

Chỉ cập nhật trạng thái dp nếu thời gian đến thành phố v nằm trong khoảng thời gian cho phép start end


*/


int tsp(int n, vector<vector<int>>& distances, vector<pair<int, int>>& time_constraints) {
    // dp[mask][i]: chi phí tối thiểu để thăm tất cả các thành phố trong mask, kết thúc tại thành phố i
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    vector<vector<int>> time(1 << n, vector<int>(n, INF)); // Thời gian đến mỗi thành phố
    
    // Trạng thái cơ sở: Bắt đầu tại thành phố 0
    dp[1][0] = 0;
    time[1][0] = 0;

    // Duyệt qua tất cả các tập hợp thành phố (mask)
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int u = 0; u < n; ++u) {
            // Nếu thành phố u nằm trong tập hợp mask
            if ((mask & (1 << u)) != 0) {
                for (int v = 0; v < n; ++v) {
                    // Nếu thành phố v chưa nằm trong mask và có đường từ u đến v
                    if ((mask & (1 << v)) == 0 && distances[u][v] != 0) {
                        int arrival_time = time[mask][u] + distances[u][v];
                        
                        // Kiểm tra ràng buộc thời gian của thành phố v
                        if (arrival_time >= time_constraints[v].first && arrival_time <= time_constraints[v].second) {
                            int new_mask = mask | (1 << v);
                            if (dp[new_mask][v] > dp[mask][u] + distances[u][v]) {
                                dp[new_mask][v] = dp[mask][u] + distances[u][v];
                                time[new_mask][v] = arrival_time; // Cập nhật thời gian đến thành phố v
                            }
                        }
                    }
                }
            }
        }
    }

    // Tìm kết quả cuối cùng
    int result = INF;
    for (int v = 1; v < n; ++v) {
        if (distances[v][0] != 0) {
            result = min(result, dp[(1 << n) - 1][v] + distances[v][0]);
        }
    }
    return result;
}

int main() {
    int n;
    cin >> n;

    // Nhập ma trận khoảng cách
    vector<vector<int>> distances(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> distances[i][j];
        }
    }

    // Nhập ràng buộc thời gian cho từng thành phố
    vector<pair<int, int>> time_constraints(n);
    for (int i = 0; i < n; ++i) {
        cin >> time_constraints[i].first >> time_constraints[i].second;
    }

    // Xuất kết quả tổng quãng đường tối thiểu
    cout << tsp(n, distances, time_constraints) << endl;

    return 0;
}
