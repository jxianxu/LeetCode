//#include "knapsack01.h"
#include "ModernC++Design/Chapter_2.hpp"
#include "ModernC++Design/Chapter_3.hpp"
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
	std::cout<<"Length: "<<Length<TYPE_LIST_5(int, int, int, char, char)>::value<<std::endl;
	TypeAt<TYPE_LIST_5(int, int, int, char, char),2>::Type a;
	//TypeAt<TYPE_LIST_5(int, int, int, char, char), 7>::Type b;//error C2079: 'b' uses undefined class 'NullType'
	std::cout<<"Index of float:"<<IndexOf<TYPE_LIST_5(int, double, float, char, long), float>::value<<"\n";//2

	using tlist = typename Append<TYPE_LIST_3(int, char, long), TYPE_LIST_3(float, double, short)>::Result;
	std::cout << "tlist len: " << Length<tlist>::value << "\n";

	using elist = typename Erase<TYPE_LIST_1(double), int>::Result;
	std::cout << "elist len:" << Length<elist>::value << "\n";

	using ealist = typename EraseAll<TYPE_LIST_5(int, double, double, char, long), double>::Result;
	std::cout << "ealist len:" << Length<ealist>::value << "\n";

	using dlist = typename NoDuplicates<TYPE_LIST_5(int, double, double, char, char)>::Result;
	std::cout << "dlist len:" << Length<dlist>::value << "\n";//3

	using rlist = typename Replace<TYPE_LIST_5(int, float, double, char, short), float, std::string>::Result;
	std::cout << "rlist len:" << Length<rlist>::value << "\n";//5

	complexInfo info;
	int x = Field<0>(info)._value;
	float y = Field<1>(info)._value;
    system("pause");  
	return 0;
}

