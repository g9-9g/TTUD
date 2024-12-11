#include <bits/stdc++.h>

using namespace std;
#include <vector>

// Custom comparator -> struct
struct CustomCompare {
    bool operator()(const int& lhs, const int& rhs) {
        return lhs > rhs; // Min-heap
    }
};

struct StringCompare {
    bool operator()(const string& lhs, const string& rhs) {
        return lhs > rhs; // Min-heap (lexicographically smallest string at the top)
    }
};

struct PairCompare {
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
        if (lhs.first == rhs.first) {
            return lhs.second > rhs.second; // Min-heap based on .second if .first is equal
        }
        return lhs.first > rhs.first; // Min-heap based on .first
    }
};

void vector_syntax() {
    vector<int> v;
    
    // print
    cout << "Size of the vector: " << v.size() << endl;
    for (auto num : v) {
        cout << num << " ";
    }

    // Iterators:
    v.begin(); // iterator to the first element
    v.end(); // iterator to the last element
    v.empty(); // check if the vector is empty

    // Capacity:
    v.resize(10); 
    cout << "Size of the vector: " << v.size() << endl;

    // Element access:
    v.front(); v.back(); // -> value first and last element

    // Modifiers:
    v.push_back(1);
    v.pop_back(); // remove the last element

    // Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
    v.assign(7,1);
    v.assign(5, 10); // 5 elements with value 10
    v.insert(v.begin()+3,3, 5); // insert (pointer, count, value) -> pointer of last insert element

    v.erase(v.begin()+3); // erase 1 element
    v.erase(v.begin(), v.begin()); // erase elements in range

    // bonus: vector<bool>
    vector<bool> v_bool;
    v_bool.flip(); // flip all bits
}

void hash_map_set() {
    // UNORDERED_MAP
    unordered_map<string, int> um;
    // Tương tự Vector về syntax Iterator, Capacity, Element access (khoong co front back)
    // Can be insert,erase thủ công
    um.find("key"); // return iterator to the element if found, else return m.end()
    um.insert({"key", 1}); // insert pair
    um.erase("key"); // erase element with key "key"
    // Trong trường hợp có nhiều key trùng nhau
    um.count("key"); // return 1 if found, else return 0
    um.equal_range("key"); // return pair of iterator to the first element and the last element with key "key, 

    // MAP (bin tree), thứ tự luôn được sort theo pair {key,value}
    map<string, int> m;

    // Tương tự UMAP với các hàm cơ bản, mất log
    // BONUS:
    m.lower_bound("key"); // return iterator to the first element with key not less than "key"
    m.upper_bound("key"); // return iterator to the first element with key greater than

    // SET: Lưu các phần tử ko trùng -> cây bin
    set<int> s;
    // Syntax tương tự MAP
    s.insert(1); // insert element
    s.erase(1); // -> có thể xóa theo giá trị hoặc iterator
    // -> duyệt như vector
    s.lower_bound(1); // return iterator to the first element not less than 1
    s.upper_bound(1); // return iterator to the first element greater than 1


    // UNORDERED_SE-> tương tự
    unordered_set<int> us;
}

void queue_stack() {
    // QUEUE
    queue<int> q;
    q.push(1); q.pop(); // pop front push back
    q.front(); q.back();
    q.empty(); // check if the queue is empty
    q.size(); // return the size of the queue

    // STACK
    stack<int> s;
    s.push(1); s.pop(); // pop back push back
    s.top();

    // PRIORITY QUEUE
    priority_queue<int> pq;
    pq.push(1); pq.pop(); // tương tự queue
    
    // PRIORITY QUEUE
    priority_queue<int, vector<int>, CustomCompare> pq_custom;
    pq_custom.push(3);
    pq_custom.push(1);
    pq_custom.push(2);

    std::cout << "Elements in priority_queue: ";
    while (!pq_custom.empty()) {
        cout << pq_custom.top() << " ";
        pq_custom.pop();
    }
    std::cout << std::endl;

    // PRIORITY QUEUE with custom comparator for strings
    priority_queue<string, vector<string>, StringCompare> pq_string;
    priority_queue<int, vector<int>, CustomCompare> pq_int;
    pq_int.top();

    // DEQUE (sliding window)
    // Giống Vector, có thể truy cập front back giống queue
    deque<int> dq;
    dq.push_front(1); dq.pop_front(); // -> POP ko trả lại giá trị
    dq.push_back(1); dq.pop_back();
    // Kết thừa tất cả các hàm của Vector
}

void string_syntax() {
    string s = "Hello";
    cout << s.substr(2, 3) << endl; // -> llo
    cout << s.find("ll") << endl; // -> 2

    // replace: thay thế substring thành 1 string khác
    s.replace(2, 3, "y there");  // s -> Hey there
    s.erase(2, 7);  // s -> He // start, length
}

void pair_syntax() {
    pair<int, int> p = {1, 2};
    p.first; p.second;
    p.swap(p_khac); // swap 2 pair
    // Struct with pair
    for (auto& pair : um) {
        cout << pair.first << " " << pair.second << endl;
    }
}

int main() {

    return 0;
}
