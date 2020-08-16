#pragma once
#include "common.h"

/***************************************************************
*   ��ȫ��������
*   ���壺�� N ����Ʒ��һ������Ϊ V �ı���������� i ����Ʒ�ķѵķ���
*   �� Ci���õ��ļ�ֵ�� Vi����⽫��Щ��Ʒװ�뱳����ʹ��ֵ�ܺ����
*	(ÿ����Ʒ���Է�����, ������0-1�������������)
*
*   dp[i][c] ��ʾ��ǰi����Ʒ���뵱ǰ����Ϊc�ı�����ʱ����������Ʒ�ļ�
*   ֵ���ֵ��
*
*   ��������
*   vector<int> W = ;
*   vector<int> V = ;
*   capacity = 5
*   ������Ʒ���������ķѣ��ֱ�Ϊ�� ��ֵ�ֱ�Ϊ
*   ���ӵ�����Ϊ
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

	//��ʼ�� - dp[i][c] = max {dp[i-1][c], dp[i][c-Ci]}
	//dp[0][0...col_count] = 0, dp[0...row_count][0] = 0;
	for (int i = 0; i < rowCount; i++)
		dp[i][0] = 0;
	for (int j = 0; j < colCount; j++)
		dp[0][j] = 0;

	for (int i = 1; i < rowCount; i++)
	{
		for (int c = 1; c < colCount; c++)
		{
			dp[i][c] = dp[i - 1][c]; //��ǰ����װ���µ�i����Ʒ
			const int Ci = cost(costVec, i);
			const int Vi = value(valueVec, i);
			//��ǰ����װ���µ�i����Ʒ������ѡ��װ��i����Ʒ�� ������ת��Ϊǰi����Ʒװ�뵱ǰ
			//ʣ������Ϊc-Ci�ı����������(ע�⣺������0-1���������һ�����ͬ�� ��Ϊ��i
			//����Ʒ����װ�����޶�Σ�������dp[i][c-Ci]������01���������е�dp[i-1][c-Ci])
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

	//���岢��ʼ�� - dp[c] = max {dp[c], dp[c-Ci]}
	//dp[0...col_count] = 0
	vector<int> dp(colCount);
	
	for (int i = 1; i < rowCount; i++)
	{
		for (int c = 1; c < colCount; c++)
		{
			const int Ci = cost(costVec, i);
			const int Vi = value(valueVec, i);
			//��ǰ����װ���µ�i����Ʒ������ѡ��װ��i����Ʒ�� ������ת��Ϊǰi����Ʒװ�뵱ǰ
			//ʣ������Ϊc-Ci�ı����������.
			//ע���ڲ�ѭ����˳����0-1��������Ŀռ�ѹ���㷨��ͬ�����������ǲ�ȡc������˳��
			//(01���������У�c��colCount�ݼ�����Ϊ������Ҫdp[i-1]�еĽ��),����ȫ����������
			//��i����Ʒ�ɷ����Σ��Ӷ�ά���ƹ�ʽdp[i][c-Ci]�����ǿ��Է��֣����ǲ�����Ҫ����
			//ǰһ�еĽ���ˣ�������Ҫ���������
			if (Ci >= c)
				dp[c] = max(dp[c], dp[c - Ci] + Vi);
		}
	}
	return dp[capacity];
}