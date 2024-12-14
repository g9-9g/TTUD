/*
At the beginning of the semester, the head of a computer science department D have to assign courses to teachers in a balanced way. The department D has m teachers T={1,2,...,m} and n courses C={1,2,...,n}. Each teacher t∈T has a preference list which is a list of courses he/she can teach depending on his/her specialization. We known a list of pairs of conflicting two courses that cannot be assigned to the same teacher as these courses have been already scheduled in the same slot of the timetable. The load of a teacher is the number of courses assigned to her/him. How to assign nn courses to mm teacher such that each course assigned to a teacher is in his/her preference list, no two conflicting courses are assigned to the same teacher, and the maximal load is minimal.
Input
The input consists of following lines
Line 1: contains two integer m and n (1≤m≤10, 1≤n≤30)
Line i+1: contains an positive integer k and k positive integers indicating the courses that teacher i can teach (∀i=1,…,m)
Line m+2: contains an integer k
Line i+m+2: contains two integer i and j indicating two conflicting courses (∀i=1,…,k)
Output
The output contains a unique number which is the maximal load of the teachers in the solution found and the value -1 if not solution found.
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits.h>
using namespace std;

int m, n;
vector<vector<int>> teacherPreferences; // courses each teacher can teach
vector<pair<int, int>> conflicts;       // list of conflicting course pairs
vector<int> courseAssignments;          // which teacher is assigned to each course
vector<int> teacherLoad;                // number of courses assigned to each teacher
int minMaxLoad = INT_MAX;               // minimum of the maximum load across teachers

// Check if assigning a course to a teacher is valid
bool isValidAssignment(int course, int teacher) {
    // Check if the course is in the teacher's preference list
    if (find(teacherPreferences[teacher].begin(), teacherPreferences[teacher].end(), course)
        == teacherPreferences[teacher].end())
        return false;

    // Check for conflicts with other courses assigned to this teacher
    for (int i = 0; i < courseAssignments.size(); i++) {
        if (courseAssignments[i] == teacher) {
            for (auto &conflict : conflicts) {
                if ((conflict.first == course && conflict.second == i + 1) ||
                    (conflict.second == course && conflict.first == i + 1)) {
                    return false; // Conflicting course found
                }
            }
        }
    }
    return true;
}

// Recursive backtracking function to assign courses to teachers
void assignCourses(int course) {
    if (course > n) { // All courses are assigned
        int maxLoad = *max_element(teacherLoad.begin(), teacherLoad.end());
        minMaxLoad = min(minMaxLoad, maxLoad);
        return;
    }

    for (int teacher = 0; teacher < m; teacher++) {
        if (isValidAssignment(course, teacher)) {
            // Assign course to this teacher
            courseAssignments[course - 1] = teacher;
            teacherLoad[teacher]++;

            // Prune branches with higher load than current minMaxLoad
            if (*max_element(teacherLoad.begin(), teacherLoad.end()) < minMaxLoad)
                assignCourses(course + 1);

            // Backtrack
            courseAssignments[course - 1] = -1;
            teacherLoad[teacher]--;
        }
    }
}

int main() {
    // Input number of teachers and courses
    cin >> m >> n;
    teacherPreferences.resize(m);
    courseAssignments.resize(n, -1); // -1 means not assigned yet
    teacherLoad.resize(m, 0);

    // Read teacher preferences
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        teacherPreferences[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> teacherPreferences[i][j];
        }
    }

    // Read conflict pairs
    int k;
    cin >> k;
    conflicts.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> conflicts[i].first >> conflicts[i].second;
    }

    // Start assigning courses
    assignCourses(1);

    // Output result
    if (minMaxLoad == INT_MAX) cout << -1 << endl;
    else cout << minMaxLoad << endl;

    return 0;
}
