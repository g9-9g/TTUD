#include <iostream>
#include <vector>
using namespace std;

int count_solutions(int n, int M, const vector<int> &a)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    
    // Dat lai Y = X - 1, thay doi pham vi thanh so khong am (from N* to N)
    M -= sum; // sum(a_i*Y) = M - sum(a_i)

    if (M < 0) //  M phai la nguyen duong
    {
        return 0;
    }

    vector<int> dp(M + 1);
    dp[0] = 1; // 1 way to calc sum 0

    for (int j = 0; j < n; j++)
    {
        for (int i = a[j]; i <= M; i++)
        {
            dp[i] += dp[i - a[j]];
        }
    }
    return dp[M];
}

int main()
{
    int n, M;
    cin >> n >> M;
    vector<int> a(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    cout << count_solutions(n, M, a) << endl;

    return 0;
}