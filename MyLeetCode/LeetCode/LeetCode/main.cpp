//#include "knapsack01.h"
#include "ModernC++Design.h"
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <string>
#include <list>
#include <memory>
#include <stdio.h>
//#include "segmentTree.h"
//#include "binaryIndexedTree.h"
#include <windows.h>
#include <stdlib.h>
#include <math.h>   
#include <iostream>
#include <regex>
#include <new>
#include <ostream>
#include <vector>
typedef unsigned int	ub4;
typedef unsigned long 	        ub8;
static const int FractionalBits = 24;
ub4	genTimeCounter = 0;
static const ub8 FractionalMask = (1 << FractionalBits) - 1;
ub8 setTimeWithSequence(ub8 t) 
{
	unsigned long gen_Time = (t << FractionalBits) | (genTimeCounter & FractionalMask);
	return gen_Time;
}

class Base {
	int data;
};
class Child :public Base {
	char c;
};

int main()
{
	
	Int2TypeTest<int, true> i2t;
	i2t.doSomethings(3);
	
    system("pause");
	return 0;
}

