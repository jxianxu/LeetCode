
#include "treeNode.h"


bool isRightNext(string& p, int index, int step)
{
    if ('z' == p[index + step - 1])
        return p[index + step] == 'a';

    int iNext = (int)(p[index + step - 1] - 'a') + 1;
    char cNext = (char)(iNext + (int)'a');
    return cNext == p[index + step];
}
bool isRepeat(vector< vector<int> >& dp, string& p, int i, int j)
{
    for (int k = 0; k < j; ++k)
    {
        if (1 == dp[i][k] && p[k] == p[j])
            return true;
    }
    return false;
}
int findSubstringInWraproundString(string p) {
    if (0 == p.length())
        return 0;
    int n = p.length();
    vector< vector<int> > dp;
    for (int i = 0; i < n; ++i)
    {
        vector<int> row(n);
        dp.push_back(row);
    }
    for (int j = 0; j < n; j++)
    {
        dp[0][j] = 1;
    }

        for (int row = 1; row < n; ++row)
        {
            cout << row << endl;
            for (int col = 0; col < n - row; ++col)
            {
                if (1 == dp[row - 1][col] && isRightNext(p, col, row))
                {
                    dp[row][col] = 1;
                }
                else
                {
                    dp[row][col] = 0;
                }
            }
        }
    
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //cout << dp[i][j] << " ";
            if (dp[i][j] == 1 && !isRepeat(dp, p, i, j))
                sum += 1;
        }
        //cout << endl;
    }
    return sum;
}
int main()
{
    string str = "opqrstuvwvwxyzbcdefghijklmnopqrststubcdefghijklmnopqrstuvrscdefghijklmnoprstcdefgpqrstuvwxnopqrbcdefghijklmnopqrstcdefghijklmnopqrstuvwtuvwhbcdefghijklmnopijkbcdefghijklmnopqrstuvwxyefgbcdefghituvwxyghijkzefghijklmnopqrstuvwxyzlmnopqrstuvwxyzqrstuvwxmnopqrstuvwxfghijklmnopqrefghijklmijklmnopqrstqrstuvwefghijdefghijklmnopqrstuvlmnopqrstuvwxylmnopqrstuvwxghijklmnopqrstuvwcdefghijklmnopcdefghijklmnopqrstuvwxyzqrstuvwxyzcdefghijklmnopnopqpqrstuvwxynopqrsnopqstuvwxyjklmstknopqrstuvwxyzcdefghijklmnopqbcdefghijklmnopqrstunopqropqrstuvwxyjklmnopqrstuvwabcdefghijklbcqrbcdefghijklmnopqrsijklmnopqrstfghijklmnopqrstuvwxuvwxyzijbcdetucdefghijklmnklmnopabcdefghijklmnopqrabcdopqrstqhghijklefghijklmnopqrstuvbcdefghijklmnopqrstujklmnopqrstuvabcdefwxyzrstuvwfghijklmnopghdefghijklmcdefghijklmnopqrstuvwxghijklmnopqrstuhijklmnoijklmnopqrsthijklmnopqrstuvwxjklmnopqrstuvjklmnopqrstuvwxabcdefghijklmfghijklmnopqrscdefghijklmnopqrstufghijklmnopqrscdeffghijklmnopqrstuvbcdefghijklmnijklfghijabcdefghijklmnopqrstuvwxybcde";
    
    int re = findSubstringInWraproundString(str);
    cout << "ret=" <<re << endl;
    cout << "length=" << str.length() << endl;
	system("pause");
	return 0;
}