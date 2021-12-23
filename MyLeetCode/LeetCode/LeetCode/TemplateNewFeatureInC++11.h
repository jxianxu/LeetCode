#pragma once
#include <map>
#include <string>
#include <vector>
//In C++11, we can make template parameter type (Type)
//to be the friend of template class Base
template<typename Type> class Base {
	friend Type; //give access permission to 'Type', 
				 //'Type' can be a class, a function and a built-in type is also allowed
};

//Before C++11, we can only create a type alias for instantiation of a template
typedef std::vector<int> IntVector;
//C++11 allow us define a type alias for a template
template<typename T> using twins = std::pair<T, T>;
twins<std::string> authors;
template<typename T> using part = std::pair<T, int>;
part<std::string> pa; //pa is part<std::string, int>


//Before C++11, we can only provide default template argument for template class
//From C++11, we can provide default  template argument for both template class and function
template<typename T, typename F = std::less<T>>
bool compare(const T& t1, const T& t2, F f = F()) {
	//...
	return true;
}
//In above code, the default value for typename F is std::less<T>
//we also give f a default value, a instantiation of less<T>
template<typename T = int> class Base {

};
Base<> base1; //<> represents that we hope to use default value for T


//C++11, explicit instantiation
extern template class Blob<std::string>;  //Blob<std::string> is defined in other file
extern template bool compare(const int&, const int&);// function compare is defined in other file
//in other file we can instantiation compare<int>() with following code:
template bool compare(const int&, const int&) { return true; }