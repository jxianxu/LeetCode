#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <iomanip>
#include <initializer_list>
#include <memory>
using namespace std;
#define NIL -10000000

const int NaN = -1;              // 表示不可达状态

int max(int a, int b)
{
    return (a > b) ? a : b;
}
int GetWi(vector<int>& W, int i)
{
    return W[i - 1];
}
int GetVi(vector<int>& V, int i)
{
    return V[i - 1];
}

const int cost(vector<int>& costVec, int i)
{
    return costVec[i - 1];
}
const int value(vector<int>& valueVec, int i)
{
    return valueVec[i - 1];
}