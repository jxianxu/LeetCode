#pragma once
#include "common.h"

/*
编写一个程序，找出第 n 个丑数。

丑数就是质因数只包含 2, 3, 5 的正整数。

示例:

输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
说明:  

1 是丑数。
n 不超过1690。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ugly-number-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

int min(int a, int b)
{
    return (a > b) ? b : a;
}

int nthUglyNumber(int n) {
    if (0 == n)
        return 0;

    if (n <= 6)
        return n;

    vector<int> dp(n + 1);
    int p2 = 0;
    int p3 = 0;
    int p5 = 0;
    dp[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = min(min(dp[p2] * 2, dp[p3] * 3), dp[p5] * 5);
        if (dp[i] == dp[p2] * 2) p2++;
        if (dp[i] == dp[p3] * 3) p3++;
        if (dp[i] == dp[p5] * 5) p5++;

    }
    return dp[n - 1];
}
/*
给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。

示例 1:

输入: n = 12
输出: 3
解释: 12 = 4 + 4 + 4.
示例 2:

输入: n = 13
输出: 2
解释: 13 = 4 + 9.\

递推公式
设dp[n] 为组成n的完全平方数的最少个数
dp[n] = min {dp[ n- k ]} + 1, 其中k是完全平方数数组中小于等于n的一个完全平方数

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/perfect-squares
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
int numSquares(int n) {
    if (0 == n)
        return 0;

    vector<int> squareVec;
    for (int i = 1; i < n; i++)
    {
        if (i * i <= n)
            squareVec.push_back(i * i);
        else
            break;
    }
    vector<int> dp(n + 1);
    dp[1] = 1;
    int min = 0;
    for (int i = 2; i <= n; ++i)
    {
        min = i;
        for (int j = 0; j < squareVec.size(); ++j)
        {
            if (squareVec[j] <= i)
            {
                if (dp[i - squareVec[j]] < min)
                    min = dp[i - squareVec[j]];
            }
            else
            {
                break;
            }
        }
        dp[i] = min + 1;
    }
    return dp[n];
}
