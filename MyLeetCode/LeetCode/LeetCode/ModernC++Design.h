#pragma once

//Chapter 2.7 编译期间获得可转换性
template<typename T, typename U>
class Converstion
{
public:
	using Small = char;
	class Big {
		char data[2];
	};
	static Small Test(U);// test function return Small type
						 //, has a U type argument
	static Big Test(...);
	static T MakeT(); // return T type
public:
	enum { exists = sizeof(Test(MakeT())) == sizeof(Small) };
	enum { exists2Way = exists && Converstion<U, T>::exists}; //T 和 U 是否可以双向转换
	enum { sameType = false };
};
#define SUPERSUBCLASS(T, U) \
	Converstion<U*, T*>::exists && \
	!Converstion<T*, void*>::sameType

//Chapter 2.10 type_traits
class NullType;//no definition, is used as a placeholder
template<typename T>
class MyTypeTraits
{
	//Pointer Traits
	template<typename U> struct PointerTraits {
		enum {result = false};
		using PointeeType = NullType;
	};
	template<typename U> struct PointerTraits<U*> {
		enum { result = true };
		using PointeeType = U;
	};

	// Reference Traits
	template<typename U> struct ReferenceTraits {
		enum { result = false};
		using ReferencedType = NullType;
	};
	template<typename U> struct ReferenceTraits<U&> {
		enum { result = true};
		using ReferencedType = U;
	};

	// remove const
	template<typename U> struct RemoveConst {
		using result = U;
	};
	template<typename U> struct RemoveConst<const U> {
		using result = U;
	};
public:
	enum { isPointer = PointerTraits<T>::result };
	using PointeeType = typename PointerTraits<T>::PointeeType;
	
	
	enum { isReference = ReferenceTraits<T>::result};
	using ReferencedType = typename ReferenceTraits<T>::ReferencedType;

	using UnConstType = typename RemoveConst<T>::result;
};



