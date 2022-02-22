#pragma once
#include "Chapter_2.hpp"
//namespace TL
//{
	template<typename T, typename U>
	struct TypeList
	{
		using Head = T;
		using Tail = U;
	};

#define TYPE_LIST_1(T1) TypeList<T1, NullType>
#define TYPE_LIST_2(T1, T2) TypeList<T1, TYPE_LIST_1(T2)>
#define TYPE_LIST_3(T1, T2, T3) TypeList<T1, TYPE_LIST_2(T2, T3)>
#define TYPE_LIST_4(T1, T2, T3, T4) TypeList<T1, TYPE_LIST_3(T2, T3, T4)>
#define TYPE_LIST_5(T1, T2, T3, T4, T5) TypeList<T1, TYPE_LIST_4(T2, T3, T4, T5)>

//3.4 计算长度
	template<typename T> struct Length;
	template<> struct Length<NullType> {
		enum {value = 0};
	};
	template<typename T, typename U> struct Length<TypeList<T, U> >
	{
		enum {value = 1 + Length<U>::value};
	};

	//TypeAt(i) 索引式访问
	template<typename TList, unsigned int i> struct TypeAt;
	template<typename Head, typename Tail> struct TypeAt<TypeList<Head, Tail>, 0 >
	{
		using Type = Head;
	};
	template<int i> struct TypeAt<NullType, i>
	{
		using Type = NullType;
	};
	template<typename Head, typename Tail, int i> struct TypeAt<TypeList<Head, Tail>, i>
	{
		using Type = typename TypeAt<Tail, i - 1>::Type;
	};
	//IndexOf, 查找某个类型的位置
	template<typename TList, typename T> struct IndexOf;
	template<typename T> struct IndexOf<NullType, T>
	{
		enum {value = -1};
	};
	template<typename T, typename U> struct IndexOf<TypeList<T,U>, T>
	{
		enum {value = 0};
	};
	template<typename Head, typename Tail, typename T> struct IndexOf<TypeList<Head, Tail>, T>
	{
	private:
		enum { temp = IndexOf<Tail, T>::value};
	public:
		enum { value = temp == -1 ? -1 : 1 + temp };
	};

	//Append 附加元素至TypeList
	template<typename TList, typename T> struct Append;
	template<> struct Append<NullType, NullType>
	{
		using Result = NullType;
	};
	template<typename T> struct Append<NullType, T>
	{
		using Result = TYPE_LIST_1(T);
	};
	template<typename Head, typename Tail> struct Append<NullType, TypeList<Head, Tail>>
	{
		using Result = TypeList<Head, Tail>;
	};
	template<typename Head, typename Tail, typename T> struct Append<TypeList<Head, Tail>, T>
	{
		using NewTail = typename Append<Tail, T>::Result;
		using Result = TypeList<Head, NewTail>;
	};

	//3.9 Erase 移除TypeList中的某个类型
	template<typename TList, typename T> struct Erase;
	template<typename T> struct Erase<NullType, T>
	{
		using Result = NullType;
	};
	template<typename Head, typename Tail> struct Erase<TypeList<Head, Tail>, Head>
	{
		using Result = Tail;
	};
	template<typename Head, typename Tail, typename T> struct Erase<TypeList<Head, Tail>, T>
	{
		using NewTail = typename Erase<Tail, T>::Result;
		using Result = TypeList<Head, NewTail>;
	};
	//3.9.1 EraseAll 移除某个型别的所有个体
	template<typename TList, typename T> struct EraseAll;
	template<typename T> struct EraseAll<NullType, T>
	{
		using Result = NullType;
	};
	template<typename Head, typename Tail> struct EraseAll<TypeList<Head, Tail>, Head>
	{
		using Result = typename Erase<Tail, Head>::Result;
	};
	template<typename Head, typename Tail, typename T> struct EraseAll<TypeList<Head, Tail>, T>
	{
		using NewTail = typename EraseAll<Tail, T>::Result;
		using Result = TypeList<Head, NewTail>;
	};

	//3.10 移除重复元素
	template<typename TList> struct NoDuplicates;
	template<> struct NoDuplicates<NullType>
	{
		using Result = NullType;
	};
	template<typename Head, typename Tail> struct NoDuplicates<TypeList<Head, Tail>>
	{
	private:
		using Tail1 = typename NoDuplicates<Tail>::Result;
		using Tail2 = typename Erase<Tail1, Head>::Result;
	public:
		using Result = TypeList<Head, Tail2>;
	};

	//3.11 用DST型别取代list中的SRC型别,
	template<typename TList, typename SRC, typename DST> struct Replace;
	template<typename SRC, typename DST> struct Replace<NullType, SRC, DST>
	{
		using Result = NullType;
	};
	template<typename Head, typename Tail, typename DST> struct Replace<TypeList<Head, Tail>, Head, DST>
	{
		using Result = TypeList<DST, Tail>;
	};
	template<typename Head, typename Tail, typename SRC, typename DST> struct Replace<TypeList<Head, Tail>, SRC, DST>
	{
		using NewTail = typename Replace<Tail, SRC, DST>::Result;
		using Result = TypeList<Head, NewTail>;
	};

	//3.12.1 Most Derived, 找到类Base的最深层子类，如果找不到则返回Base本身
	template<typename TList, typename Base> struct MostDerived;
	template<typename Base> struct MostDerived<NullType, Base>
	{
		using Result = Base;
	};
	template<typename Head, typename Tail, typename Base> struct MostDerived<TypeList<Head, Tail>, Base>
	{
	private:
		using Candidate = typename MostDerived<Tail, Base>::Result;
	public:
		using Result = typename Select<SUPERSUBCLASS(Head, Candidate), Candidate, Head>::Result;
	};
	//3.12.2 列表中，子类排在父类的前面
	template<typename TList> struct DerivedToFront;
	template<typename Head, typename Tail> struct DerivedToFront<TypeList<Head, Tail>>
	{
	private:
		using TheMostDerived = typename MostDerived<Tail, Head>::Result;
		using NewTail = typename Replace<Tail, TheMostDerived, Head>::Result;
	public:
		using Result = TypeList<TheMostDerived, NewTail>;
	};


	//3.13 运用TypeList自动产生一系列class
	template<typename TList, template<typename> class Unit> class GenScatterHierachy;
	//Specialization
	template<typename T1, typename T2, template<typename> class Unit>
	class GenScatterHierachy<TypeList<T1, T2>, Unit>
		:public GenScatterHierachy<T1, Unit>
		,public GenScatterHierachy<T2, Unit>
	{};
	template<typename atomicType, template<typename> class Unit>
	class GenScatterHierachy :public Unit<atomicType>
	{};
	//do nothing for Null Type
	template<template<typename> class Unit>
	class GenScatterHierachy<NullType, Unit>
	{};
	template<typename T>
	struct Holder {
		T _value;
	};
	typedef GenScatterHierachy<TYPE_LIST_3(int, float,double), Holder> complexInfo;
	//complexInfo info;
	//string name = (static_cast<std::string>(info))._value;

	//Access function
	
	template<typename TList, template<typename> class Unit>
	Unit<typename TList::Head>& FieldHelper(GenScatterHierachy<TList, Unit>& obj, Int2Type<0>)
	{
		GenScatterHierachy<TList::Head, Unit>& leftBase = obj;
		return leftBase;
	}
	
	template<int index, typename TList, template<typename> class Unit>
	Unit<typename TypeAt<TList, index>::Type>& FieldHelper(GenScatterHierachy<TList, Unit> obj, Int2Type<index>)
	{
		GenScatterHierachy<typename TList::Tail, Unit>& rightBase = obj;
		return FieldHelper(rightBase, Int2Type<index-1>());
	}

	template<int index, typename TList, template<typename> class Unit>
	Unit<typename TypeAt<TList, index>::Type>& Field(GenScatterHierachy<TList, Unit>& obj)
	{
		return FieldHelper(obj, Int2Type<index>());
	}
	//complexInfo info;
	//int x = Field<0>(info)._value;

	//3.13.3 产生线性继承体系
	template<typename T, typename Base>
	class EventHandler : public Base
	{
	public:
		virtual void OnEvent(T& obj, int eventId) {}
	};

	template<typename TList, template<typename AtomicType, typename Base> class Unit, class Root=EmptyType>
	class GenLinearHierachy;

	//specialization
	template<typename Head, typename Tail, template<typename AtomicType, typename Base> class Unit, class Root = EmptyType>
	class GenLinearHierachy<TypeList<Head, Tail>, Unit, Root>
		: public Unit<Head, GenLinearHierachy<Tail, Unit, Root>>
	{};

	template<typename T, template<class, class> class Unit, typename Root>
	class GenLinearHierachy<TYPE_LIST_1(T), Unit, Root>
		: public Unit<T, Root>
	{};
	//typedef GenLinearHierachy<TYPE_LIST_3(int, float, double), EventHandler> MyEventHandler




//}