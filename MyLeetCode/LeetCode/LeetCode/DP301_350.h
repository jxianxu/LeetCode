#pragma once
#include "common.h"
/*
给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。​

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
示例:

输入: [1,2,3,0,2]
输出: 3
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
我们用 f[i]f[i] 表示第 ii 天结束之后的「累计最大收益」。根据题目描述，由于我们最多只能同时买入（持有）一支股票，并且卖出股票后有冷冻期的限制，因此我们会有三种不同的状态：

我们目前持有一支股票，对应的「累计最大收益」记为 f[i][0]f[i][0]；

我们目前不持有任何股票，并且处于冷冻期中，对应的「累计最大收益」记为 f[i][1]f[i][1]；

我们目前不持有任何股票，并且不处于冷冻期中，对应的「累计最大收益」记为 f[i][2]f[i][2]。

f[i][0]=max(f[i−1][0],f[i−1][2]−prices[i])
f[i][1]=f[i−1][0]+prices[i]
f[i][2]=max(f[i−1][1],f[i−1][2])

max(f[n−1][1],f[n−1][2])
作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/solution/zui-jia-mai-mai-gu-piao-shi-ji-han-leng-dong-qi-4/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int maxProfit(vector<int>& prices) {
    if (prices.empty())
        return 0;

    int dp0 = -prices[0];
    int dp1 = 0;
    int dp2 = 0;

    for (int i = 1; i < prices.size(); ++i)
    {
        int idp0 = (dp0 > dp2 - prices[i]) ? dp0 : dp2 - prices[i];
        int idp1 = dp0 + prices[i];
        int idp2 = (dp1 > dp2) ? dp1 : dp2;
        dp0 = idp0;
        dp1 = idp1;
        dp2 = idp2;
    }
    return (dp1 > dp2) ? dp1 : dp2;
}
