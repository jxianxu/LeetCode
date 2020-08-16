#pragma once
#include "common.h"

/***************************************************************
*   0-1 背包问题
*   定义：有 N 件物品和一个容量为 V 的背包。放入第 i 件物品耗费的费用
*   是 Wi，得到的价值是 Ci。求解将哪些物品装入背包可使价值总和最大。
*   (每件物品最多只能放入一次)
*   dp[i][v] 表示将前i个物品放入当前容量为v的背包中时，背包中物品的价
*   值最大值。
*
*   测试数据
*   vector<int> W = {1,2,3};
*   vector<int> V = { 6,10,12 };
*   target = 5
*   三个物品，重量（耗费）分别为1,2,3， 价值分别为6,10，12
*   袋子的容量为5
****************************************************************/

int knapsack01(vector<int>& W, vector<int>& V, int target)
{
    if (target < 0)
        return 0;
    if (W.empty() || V.empty())
        return 0;
    int n = W.size();
    int** dp = new int* [n + 1];
    for (int i = 0; i <= n; i++)
        dp[i] = new int[target + 1];

    //initialize -- dp[i][v] = max {dp[i-1][v], dp[i-1][v-Wi] + Vi}
    //dp[0][v] = 0
    //dp[i][0] = 0
    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;
    for (int v = 0; v <= target; v++)
        dp[0][v] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int v = GetWi(W, i); v <= target; v++)
        {
            dp[i][v] = dp[i - 1][v];  // 现有容量装不下第i个物品

            // 现有容量能装下第i个物品,则面临两个选择:
            // 1 不装第i个物品-> dp[i][v] = dp[i-1][v] 
            // 2 装第i个物品，问题转化为在容量为v-Wi的背包中装前面的i-1个背包的问题(dp[i-1][v-Wi])，所以 dp[i][v] = dp[i-1][v-Wi] + Vi
            // dp[i][v]应该取1，2 两种情况里面的最大值
            if (GetWi(W, i) <= v)      // 现有容量能装下第i个物品
            {
                dp[i][v] = max(dp[i - 1][v], dp[i - 1][v - GetWi(W, i)] + GetVi(V, i));
            }
            
        }
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= target; j++)
            cout << setw(2) << left << dp[i][j] << " ";
        cout << endl;
    }
    return dp[n][target];
}
/****************************************************************
*   0-1背包问题的第二种问法：当背包恰好被装满时，背包内物品的最大值
*   我们引入一个常量NaN=-1 表示不可达状态，用以表示当用前i个物品无法
*   填充满容量为v的背包时，dp[i][v]的值。此问题中，dp的递推公式仍然
*   是与之前相同的：
*
*   dp[i][v] = max {dp[i-1][v], dp[i-1][v-Wi] + Vi}
*   这个问题和上述简单01背包问题有两个不同点：

*   --------------------------------------------------------------
*   不同点 1
*   初始化值不同，此问题中，dp[i][0] = 0, dp[0][v]中除dp[0][0] = 0
*   之外都为NaN(不可达状态),就像下面这样
*   0   -1  -1  -1
*   0
*   0
*   0
*   0
*   --------------------------------------------------------------
*   不同点 2
*       上述递推公式成立的前提是当dp[i-1][v] , dp[i-1][v-Wi] 至少有
*       一个不为NaN，当他们都为NaN时，dp[i][v]的值也应该为NaN，这说明
*       不管放不放第i个物体，前i个物品都无法装满当前容量为v的袋子
*******************************************************************/

int knapsack01_full(vector<int>& W, vector<int>& V, int target)
{
    if (target < 0)
        return 0;
    if (W.empty() || V.empty())
        return 0;
    int n = W.size();
    int** dp = new int* [n + 1];
    for (int i = 0; i <= n; i++)
        dp[i] = new int[target + 1];

    //initialize -- 不同点1 初始化的值不同
    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;
    for (int v = 1; v <= target; v++)
        dp[0][v] = NaN;

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int v = 1; v <= target; v++)
        {
            dp[i][v] = dp[i - 1][v];  // 现有容量装不下第i个物品

            // 现有容量能装下第i个物品,则面临两个选择:
            // 1 不装第i个物品-> dp[i][v] = dp[i-1][v] 
            // 2 装第i个物品，问题转化为在容量为v-Wi的背包中装前面的i-1个背包的问题(dp[i-1][v-Wi])，所以 dp[i][v] = dp[i-1][v-Wi] + Vi
            // dp[i][v]应该取1，2 两种情况里面的最大值
            if (GetWi(W, i) <= v)      // 现有容量能装下第i个物品
            {
                dp[i][v] = max(dp[i - 1][v], dp[i - 1][v - GetWi(W, i)] + GetVi(V, i));
                if (NaN == dp[i - 1][v] && NaN == dp[i - 1][v - GetWi(W, i)])
                    dp[i][v] = NaN; //不同点 2
            }
        }
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= target; j++)
            cout << setw(2) << left << dp[i][j] << " ";
        cout << endl;
    }
    return dp[n][target];
}

/*****************************************************************
*   空间压缩的动态规划算法
*   dp[i][v] = max {dp[i-1][v], dp[i-1][v-Wi] + Vi}
*   dp[i][v]的取值只与dp数组中的上一行相关，故可压缩为一维数组
*   dp[v] = max{dp[v], dp[v-Wi] + Vi}
*   初始值： dp[0...V] = 0
*   由于计算dp[v]的值时，需要用到dp[v-Wi]的值，所以需要从后向前
*   计算，因为需要保证计算dp[v]时，dp[v-Wi]中存的值仍然是dp[i-1][v-Wi]
*   的值，即上一行的值
*   for i to N
*       dp[v] = max{dp[v], dp[v-Wi] + Vi} // 计算 dp[i][v]
*******************************************************************/

int knapsack01_SpatialCompression(vector<int>& W, vector<int>& V, int target)
{
    if (target < 0)
        return 0;
    if (W.empty() || V.empty())
        return 0;
    int n = W.size();
    vector<int> dp(target+1);//initialize -- 创建dp一维数组，默认会初始化 dp[0....target] =  0

    for (int i = 1; i <= n; i++)
    {
        for (int v = target; v >=0; v--)
        {
            // 现有容量能装下第i个物品,则面临两个选择:
            // 1 不装第i个物品-> dp[v] = dp[v] 
            // 2 装第i个物品，问题转化为在容量为v-Wi的背包中装前面的i-1个背包的问题(dp[v-Wi])，所以 dp[v] = dp[v-Wi] + Vi
            // dp[i][v]应该取1，2 两种情况里面的最大值
            if (GetWi(W, i) <= v)      // 现有容量能装下第i个物品
            {
                dp[v] = max(dp[v], dp[v - GetWi(W, i)] + GetVi(V, i));
            }
        }
    }
    //output dp array
    for (auto data : dp)
        cout << data << " ";
    cout << endl;
    return dp[target];
}
