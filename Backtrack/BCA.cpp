/*
Đầu học kỳ, trưởng khoa công nghệ thông tin cần phân công các môn học cho các giảng viên sao cho cân đối. 
Khoa có m giảng viên T = {1, 2, ..., m} và n môn học C = {1, 2, ..., n}. 
Mỗi giảng viên t ∈ T có một danh sách các môn học mà họ có thể dạy tùy theo chuyên môn. 
Ngoài ra, có danh sách các cặp môn học xung đột không thể được giao cho cùng một giảng viên 
vì các môn này đã được xếp cùng một khung giờ trong thời khóa biểu. 
Tải của một giảng viên là số môn học được giao cho giảng viên đó. 
Bài toán yêu cầu phân công n môn học cho m giảng viên sao cho:
1. Mỗi môn học được giao cho một giảng viên nằm trong danh sách môn học mà giảng viên đó có thể dạy.
2. Không có hai môn học xung đột nào được giao cho cùng một giảng viên.
3. Tải lớn nhất của các giảng viên là nhỏ nhất.
Đầu vào
- Dòng 1: chứa hai số nguyên m và n (1 ≤ m ≤ 10, 1 ≤ n ≤ 30)
- Dòng i+1: chứa một số nguyên dương k và k số nguyên chỉ định các môn học mà giảng viên i có thể dạy (∀i=1,…,m)
- Dòng m+2: chứa một số nguyên k
- Dòng i+m+2: chứa hai số nguyên i và j chỉ định hai môn học xung đột (∀i=1,…,k)
Đầu ra
- Một số duy nhất là tải lớn nhất của các giảng viên trong giải pháp tìm được, hoặc giá trị -1 nếu không có giải pháp.
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits.h>
using namespace std;

int m, n;
vector<vector<int>> teacherPreferences; // Danh sách các môn học mỗi giảng viên có thể dạy
vector<pair<int, int>> conflicts;       // Danh sách các cặp môn học xung đột 
vector<int> courseAssignments;          // Giảng viên được giao cho mỗi môn học
vector<int> teacherLoad;                // Tải của từng giảng viên (số môn được giao)
int minMaxLoad = INT_MAX;               // Giá trị nhỏ nhất của tải lớn nhất giữa các giảng viên

// Kiểm tra nếu việc giao môn học cho một giảng viên là hợp lệ
bool isValidAssignment(int course, int teacher) {
    // Kiểm tra môn học có nằm trong danh sách giảng viên có thể dạy không
    if (find(teacherPreferences[teacher].begin(), teacherPreferences[teacher].end(), course)
        == teacherPreferences[teacher].end())
        return false;

    // Kiểm tra xung đột với các môn học khác đã được giao cho giảng viên này
    for (int i = 0; i < courseAssignments.size(); i++) {
        if (courseAssignments[i] == teacher) {
            for (auto &conflict : conflicts) {
                if ((conflict.first == course && conflict.second == i + 1) ||
                    (conflict.second == course && conflict.first == i + 1)) {
                    return false; // Tìm thấy môn học xung đột
                }
            }
        }
    }
    return true;
}

// Hàm đệ quy sử dụng phương pháp quay lui để phân công môn học cho giảng viên
void assignCourses(int course) {
    if (course > n) { // Tất cả các môn học đã được phân công
        int maxLoad = *max_element(teacherLoad.begin(), teacherLoad.end());
        minMaxLoad = min(minMaxLoad, maxLoad);
        return;
    }

    for (int teacher = 0; teacher < m; teacher++) {
        if (isValidAssignment(course, teacher)) {
            // Giao môn học cho giảng viên này
            courseAssignments[course - 1] = teacher;
            teacherLoad[teacher]++;

            // Cắt tỉa nhánh có tải lớn hơn giá trị minMaxLoad hiện tại
            if (*max_element(teacherLoad.begin(), teacherLoad.end()) < minMaxLoad)
                assignCourses(course + 1);

            // Quay lui
            courseAssignments[course - 1] = -1;
            teacherLoad[teacher]--;
        }
    }
}

int main() {
    // Nhập số lượng giảng viên và môn học
    cin >> m >> n;
    teacherPreferences.resize(m);
    courseAssignments.resize(n, -1); // -1 nghĩa là chưa được giao
    teacherLoad.resize(m, 0);

    // Đọc danh sách môn học mỗi giảng viên có thể dạy
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        teacherPreferences[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> teacherPreferences[i][j];
        }
    }

    // Đọc danh sách cặp môn học xung đột
    int k;
    cin >> k;
    conflicts.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> conflicts[i].first >> conflicts[i].second;
    }

    // Bắt đầu phân công môn học
    assignCourses(1);

    // Xuất kết quả
    if (minMaxLoad == INT_MAX) cout << -1 << endl;
    else cout << minMaxLoad << endl;

    return 0;
}
