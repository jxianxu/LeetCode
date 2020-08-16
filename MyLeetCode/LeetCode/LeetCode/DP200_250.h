#pragma once
#include "common.h"
/*
221. ���������
��һ���� 0 �� 1 ��ɵĶ�ά�����ڣ��ҵ�ֻ���� 1 ����������Σ��������������

ʾ��:

����: 

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

���: 4
vector<vector<char>> vec = { {'1', '0', '1', '0', '0'}, {'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'} };
*/
class Solution {
public:
    int min(int a, int b, int c)
    {
        if (a < b)
        {
            return (a < c) ? a : c;
        }
        else
        {
            return (b < c) ? b : c;
        }
    }
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty())
            return 0;
        int row = matrix.size();
        int col = matrix[0].size();
        int** dp = new int* [row];
        for (int i = 0; i < row; ++i)
            dp[i] = new int[col];

        for (int i = 0; i < col; ++i)
            dp[0][i] = (matrix[0][i] == '1') ? 1 : 0;

        for (int i = 0; i < row; ++i)
            dp[i][0] = (matrix[i][0] == '1') ? 1 : 0;

        for (int i = 1; i < row; ++i)
        {
            for (int j = 1; j < col; ++j)
            {
                if (matrix[i][j] == '1')
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1;
                else
                    dp[i][j] = 0;
            }
        }
        int max = dp[0][0];
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; j++)
            {
                if (dp[i][j] > max)
                    max = dp[i][j];
            }
        }
        return max * max;

    }
};

//dp[i, j] ��ʾ������(i, j)Ϊ���½ǵ���������εı߳�
//dp[i, j] = min { dp[i-1, j], dp[i, j-1], dp[i-1, j-1]} + 1
//dp[0, j] = (matrix[0,j] == '1') ? 1 : 0
//dp[i, 0] = (matrix[i,0] == '1') ? 1 : 0
//�ռ��Ż���dpֱ��ʹ��matrix�Ŀռ�
