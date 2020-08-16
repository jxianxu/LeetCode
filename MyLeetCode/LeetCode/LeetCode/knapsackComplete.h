#pragma once
#include "common.h"

/***************************************************************
*   完全背包问题
*   定义：有 N 件物品和一个容量为 V 的背包。放入第 i 件物品耗费的费用
*   是 Ci，得到的价值是 Vi。求解将哪些物品装入背包可使价值总和最大。
*	(每件物品可以放入多次, 这是与0-1背包问题的区别)
*
*   dp[i][c] 表示将前i个物品放入当前容量为c的背包中时，背包中物品的价
*   值最大值。
*
*   测试数据
*   vector<int> W = ;
*   vector<int> V = ;
*   capacity = 5
*   三个物品，重量（耗费）分别为， 价值分别为
*   袋子的容量为
****************************************************************/

int knapsackComplete(vector<int>& costVec, vector<int>& valueVec, int capacity)
{
	if (capacity <= 0)
		return 0;
	if (costVec.empty() || valueVec.empty())
		return 0;

	const int n = costVec.size();
	const int rowCount = n + 1;
	const int colCount = capacity + 1;

	int** dp = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		dp[i] = new int[colCount];

	//初始化 - dp[i][c] = max {dp[i-1][c], dp[i][c-Ci]}
	//dp[0][0...col_count] = 0, dp[0...row_count][0] = 0;
	for (int i = 0; i < rowCount; i++)
		dp[i][0] = 0;
	for (int j = 0; j < colCount; j++)
		dp[0][j] = 0;

	for (int i = 1; i < rowCount; i++)
	{
		for (int c = 1; c < colCount; c++)
		{
			dp[i][c] = dp[i - 1][c]; //当前容量装不下第i个物品
			const int Ci = cost(costVec, i);
			const int Vi = value(valueVec, i);
			//当前容量装得下第i个物品，并且选择装第i个物品， 则问题转化为前i个物品装入当前
			//剩余容量为c-Ci的背包里的问题(注意：这是与0-1背包问题的一个最大不同， 因为第i
			//个物品可以装入无限多次，所以是dp[i][c-Ci]而不是01背包问题中的dp[i-1][c-Ci])
			if (Ci >= c)
				dp[i][c] = max(dp[i-1][c], dp[i][c-Ci] + Vi);
		}
	}
	return dp[n][capacity];
}
int knapsackComplete_SptialCompression(vector<int>& costVec, vector<int>& valueVec, int capacity)
{
	if (capacity <= 0)
		return 0;
	if (costVec.empty() || valueVec.empty())
		return 0;

	const int n = costVec.size();
	const int rowCount = n + 1;
	const int colCount = capacity + 1;

	//定义并初始化 - dp[c] = max {dp[c], dp[c-Ci]}
	//dp[0...col_count] = 0
	vector<int> dp(colCount);
	
	for (int i = 1; i < rowCount; i++)
	{
		for (int c = 1; c < colCount; c++)
		{
			const int Ci = cost(costVec, i);
			const int Vi = value(valueVec, i);
			//当前容量装得下第i个物品，并且选择装第i个物品， 则问题转化为前i个物品装入当前
			//剩余容量为c-Ci的背包里的问题.
			//注意内层循环的顺序，与0-1背包问题的空间压缩算法不同，在这里我们采取c递增的顺序
			//(01背包问题中，c从colCount递减，因为我们需要dp[i-1]行的结果),在完全背包问题中
			//第i个物品可放入多次，从二维递推公式dp[i][c-Ci]中我们可以发现，我们不在需要保留
			//前一行的结果了，所以需要正向遍历。
			if (Ci >= c)
				dp[c] = max(dp[c], dp[c - Ci] + Vi);
		}
	}
	return dp[capacity];
}