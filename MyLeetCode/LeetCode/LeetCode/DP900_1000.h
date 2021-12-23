#pragma once
#include "common.h"
/*******************************************************
 935 骑士拨号器
 国际象棋中的骑士可以按下图所示进行移动：

 .           


这一次，我们将 “骑士” 放在电话拨号盘的任意数字键（如上图所示）上，接下来，骑士将会跳 N-1 步。每一步必须是从一个数字键跳到另一个数字键。

每当它落在一个键上（包括骑士的初始位置），都会拨出键所对应的数字，总共按下 N 位数字。

你能用这种方式拨出多少个不同的号码？

因为答案可能很大，所以输出答案模 10^9 + 7。

 

示例 1：

输入：1
输出：10
示例 2：

输入：2
输出：20
示例 3：

输入：3
输出：46

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/knight-dialer
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
dp(i,n)表示站在数字键i上跳n步的跳法种类数

dp(1, n) = dp(8, N-1) + dp(6, N-1)
dp(2, n) = dp(7, n-1) + dp(9, n-1)
:
:
dp(4, n) = dp(0, n-1) + dp(3, n-1) + dp(9, n-1)
dp(6, n) = dp(0, n-1) + dp(1, n-1) + dp(7,n-1)
:
:
dp(0, n) = dp(4, n-1) + dp(6, n-1)

sum = dp(0,n) +dp(1,n) + dp(2,n) + ..... + dp(9, n)
注意： 当n>1时，不需要dp(5,n),因为站在数字5上，按马走日的话，
由数字5 跳不到任何数字上

像这种问题，先写出它的递归式，然后初始化最小的子问题即可
********************************************************/
int knightDialer(int n) {
    if (1 == n)
        return 10;
    /* if (2 == n)
         return 20;
     if (3 == n)
         return 46;*/

    int mod = 1000000007;

    int** dp = new int* [10];
    for (int i = 0; i < 10; i++)
        dp[i] = new int[n + 1];

    for (int i = 0; i < 10; ++i)
    {
        dp[i][1] = 1;
    }
    vector<vector<int>> moves = { {4,6},{6,8},{7,9},{4,8},{0,3,9},{-1},{0,1,7},{2,6},{1,3},{2,4} };
    //可用moves代替下面循环中的switch结构
    /*for (int j = 2; j <= n; ++j)
    {
        for (int i = 0; i < 10; ++i)
        {
            if (5 == i)
                continue;
            if (i == 4 ||i == 6)
                dp[i][j] = ((dp[ moves[i][0] ][j - 1] + dp[ moves[i][1] ][j - 1]) % mod + dp[moves[i][2] ][j - 1]) % mod;
            else
                dp[i][j] = (dp[ moves[i][0] ][j - 1] + dp[moves[i][1]][j - 1]) % mod;

        }
    }*/
    for (int j = 2; j <= n; ++j)
    {
        for (int i = 0; i < 10; ++i)
        {
            if (5 == i)
                continue;
            switch (i)
            {
            case 0:
                dp[i][j] = (dp[4][j - 1] + dp[6][j - 1]) % mod;
                break;
            case 1:
                dp[i][j] = (dp[8][j - 1] + dp[6][j - 1]) % mod;
                break;
            case 2:
                dp[i][j] = (dp[7][j - 1] + dp[9][j - 1]) % mod;
                break;
            case 3:
                dp[i][j] = (dp[4][j - 1] + dp[8][j - 1]) % mod;
                break;
            case 4:
                dp[i][j] = ((dp[3][j - 1] + dp[9][j - 1]) % mod + dp[0][j - 1]) % mod;
                break;
            case 6:
                dp[i][j] = ((dp[1][j - 1] + dp[7][j - 1]) % mod + dp[0][j - 1]) % mod;
                break;
            case 7:
                dp[i][j] = (dp[2][j - 1] + dp[6][j - 1]) % mod;
                break;
            case 8:
                dp[i][j] = (dp[1][j - 1] + dp[3][j - 1]) % mod;
                break;
            default:
                dp[i][j] = (dp[4][j - 1] + dp[2][j - 1]) % mod;
                break;
            }
        }


    }
    int sum = 0;
    for (int i = 0; i < 10; ++i)
    {
        if (5 == i)
            continue;
        sum = (sum + dp[i][n]) % mod;
    }
    return sum;

}
