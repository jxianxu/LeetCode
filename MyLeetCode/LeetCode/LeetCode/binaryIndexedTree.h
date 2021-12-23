#pragma once
#include "common.h"

template<typename T>
class FenWickTree
{
public:
	FenWickTree(vector<T> src);
	~FenWickTree();

	T getSum(int m);
	
	void update(int idx, T value);
	inline int lowbit(int m) { return m & (-m); }
	void dump();
private:
	T* m_tree;
	T* m_source;
	int m_len;
};
template<typename T>
T FenWickTree<T>::getSum(int m)
{
	T sum = 0;
	while (m > 0)
	{
		sum += m_tree[m];
		m -= lowbit(m);
	}
	return sum;
}
template<typename T>
void FenWickTree<T>::update(int idx, T value)
{
	m_source[idx] += value;
	while (idx <= m_len)
	{
		m_tree[idx] += value;
		idx += lowbit(idx);
	}
}

template<typename T>
FenWickTree<T>::FenWickTree(vector<T> src)
{
	if (!src.empty())
	{
		m_len = src.size();
		m_tree = new T[m_len+1];
		m_source = new T[m_len + 1];
		//memset(m_tree, 0, m_len+1);
		//memset(m_source, 0, m_len + 1);
		for (int i = 0; i < m_len + 1; i++)
		{
			m_tree[i] = m_source[i] = 0;
		}
		
		for (size_t i = 0; i < src.size(); ++i)
		{
			update((int)i+1, src[i]);
		}
	}
}
template<typename T>
FenWickTree<T>::~FenWickTree()
{
	if (!m_tree)
		delete[] m_tree;
	if (!m_source)
		delete[] m_source;
	m_len = 0;
}
template<typename T>
void FenWickTree<T>::dump()
{
	cout << "m_tree:" << endl;
	for (int i = 1; i <= m_len; ++i)
	{
		cout << m_tree[i] << " ";
	}
	cout << endl;
	cout << "m_source:" << endl;
	for (int i = 1; i <= m_len; ++i)
	{
		cout << m_source[i] << " ";
	}
	cout << endl;
}

