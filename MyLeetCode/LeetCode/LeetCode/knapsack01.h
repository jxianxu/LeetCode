#pragma once
#include "common.h"

/***************************************************************
*   0-1 ��������
*   ���壺�� N ����Ʒ��һ������Ϊ V �ı���������� i ����Ʒ�ķѵķ���
*   �� Wi���õ��ļ�ֵ�� Ci����⽫��Щ��Ʒװ�뱳����ʹ��ֵ�ܺ����
*   (ÿ����Ʒ���ֻ�ܷ���һ��)
*   dp[i][v] ��ʾ��ǰi����Ʒ���뵱ǰ����Ϊv�ı�����ʱ����������Ʒ�ļ�
*   ֵ���ֵ��
*
*   ��������
*   vector<int> W = {1,2,3};
*   vector<int> V = { 6,10,12 };
*   target = 5
*   ������Ʒ���������ķѣ��ֱ�Ϊ1,2,3�� ��ֵ�ֱ�Ϊ6,10��12
*   ���ӵ�����Ϊ5
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
            dp[i][v] = dp[i - 1][v];  // ��������װ���µ�i����Ʒ

            // ����������װ�µ�i����Ʒ,����������ѡ��:
            // 1 ��װ��i����Ʒ-> dp[i][v] = dp[i-1][v] 
            // 2 װ��i����Ʒ������ת��Ϊ������Ϊv-Wi�ı�����װǰ���i-1������������(dp[i-1][v-Wi])������ dp[i][v] = dp[i-1][v-Wi] + Vi
            // dp[i][v]Ӧ��ȡ1��2 ���������������ֵ
            if (GetWi(W, i) <= v)      // ����������װ�µ�i����Ʒ
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
*   0-1��������ĵڶ����ʷ���������ǡ�ñ�װ��ʱ����������Ʒ�����ֵ
*   ��������һ������NaN=-1 ��ʾ���ɴ�״̬�����Ա�ʾ����ǰi����Ʒ�޷�
*   ���������Ϊv�ı���ʱ��dp[i][v]��ֵ���������У�dp�ĵ��ƹ�ʽ��Ȼ
*   ����֮ǰ��ͬ�ģ�
*
*   dp[i][v] = max {dp[i-1][v], dp[i-1][v-Wi] + Vi}
*   ��������������01����������������ͬ�㣺

*   --------------------------------------------------------------
*   ��ͬ�� 1
*   ��ʼ��ֵ��ͬ���������У�dp[i][0] = 0, dp[0][v]�г�dp[0][0] = 0
*   ֮�ⶼΪNaN(���ɴ�״̬),������������
*   0   -1  -1  -1
*   0
*   0
*   0
*   0
*   --------------------------------------------------------------
*   ��ͬ�� 2
*       �������ƹ�ʽ������ǰ���ǵ�dp[i-1][v] , dp[i-1][v-Wi] ������
*       һ����ΪNaN�������Ƕ�ΪNaNʱ��dp[i][v]��ֵҲӦ��ΪNaN����˵��
*       ���ܷŲ��ŵ�i�����壬ǰi����Ʒ���޷�װ����ǰ����Ϊv�Ĵ���
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

    //initialize -- ��ͬ��1 ��ʼ����ֵ��ͬ
    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;
    for (int v = 1; v <= target; v++)
        dp[0][v] = NaN;

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int v = 1; v <= target; v++)
        {
            dp[i][v] = dp[i - 1][v];  // ��������װ���µ�i����Ʒ

            // ����������װ�µ�i����Ʒ,����������ѡ��:
            // 1 ��װ��i����Ʒ-> dp[i][v] = dp[i-1][v] 
            // 2 װ��i����Ʒ������ת��Ϊ������Ϊv-Wi�ı�����װǰ���i-1������������(dp[i-1][v-Wi])������ dp[i][v] = dp[i-1][v-Wi] + Vi
            // dp[i][v]Ӧ��ȡ1��2 ���������������ֵ
            if (GetWi(W, i) <= v)      // ����������װ�µ�i����Ʒ
            {
                dp[i][v] = max(dp[i - 1][v], dp[i - 1][v - GetWi(W, i)] + GetVi(V, i));
                if (NaN == dp[i - 1][v] && NaN == dp[i - 1][v - GetWi(W, i)])
                    dp[i][v] = NaN; //��ͬ�� 2
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
*   �ռ�ѹ���Ķ�̬�滮�㷨
*   dp[i][v] = max {dp[i-1][v], dp[i-1][v-Wi] + Vi}
*   dp[i][v]��ȡֵֻ��dp�����е���һ����أ��ʿ�ѹ��Ϊһά����
*   dp[v] = max{dp[v], dp[v-Wi] + Vi}
*   ��ʼֵ�� dp[0...V] = 0
*   ���ڼ���dp[v]��ֵʱ����Ҫ�õ�dp[v-Wi]��ֵ��������Ҫ�Ӻ���ǰ
*   ���㣬��Ϊ��Ҫ��֤����dp[v]ʱ��dp[v-Wi]�д��ֵ��Ȼ��dp[i-1][v-Wi]
*   ��ֵ������һ�е�ֵ
*   for i to N
*       dp[v] = max{dp[v], dp[v-Wi] + Vi} // ���� dp[i][v]
*******************************************************************/

int knapsack01_SpatialCompression(vector<int>& W, vector<int>& V, int target)
{
    if (target < 0)
        return 0;
    if (W.empty() || V.empty())
        return 0;
    int n = W.size();
    vector<int> dp(target+1);//initialize -- ����dpһά���飬Ĭ�ϻ��ʼ�� dp[0....target] =  0

    for (int i = 1; i <= n; i++)
    {
        for (int v = target; v >=0; v--)
        {
            // ����������װ�µ�i����Ʒ,����������ѡ��:
            // 1 ��װ��i����Ʒ-> dp[v] = dp[v] 
            // 2 װ��i����Ʒ������ת��Ϊ������Ϊv-Wi�ı�����װǰ���i-1������������(dp[v-Wi])������ dp[v] = dp[v-Wi] + Vi
            // dp[i][v]Ӧ��ȡ1��2 ���������������ֵ
            if (GetWi(W, i) <= v)      // ����������װ�µ�i����Ʒ
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
