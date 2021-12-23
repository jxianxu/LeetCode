#pragma once
#include "common.h"

const int rootIndex = 1;

template<typename T>
struct Node
{
	int left;
	int right;
	T value;
	T lazy_flag;

	Node() { left = NaN; right = NaN; value = 0; lazy_flag = 0; }
	T	getValue() { return value; }
	int getLeft() { return left; }
	int getRight() { return right; }
	T   getLazyFlag() { return lazy_flag; }

	void setValue(T val) { value = val; }
	void setLeft(int l) { left = l; }
	void setRight(int r) { right = r; }
	void setLazyFlag(T lazy) { lazy_flag = lazy; }
	void dumpNode() { cout << "Left=" << left << " Right=" << right << " Value=" << value << " lazy="<<lazy_flag<< endl; }
};
template<typename T>
class SegmentTree
{
public:
	SegmentTree(vector<T> data);
	SegmentTree(const SegmentTree& other);
	SegmentTree(const SegmentTree&& other);
	~SegmentTree();

	T buildTree(vector<T> data, int l, int r,int idx);
	

	void setIndexedLeftValue(int i, int l);
	void setIndexedRightValue(int i, int r);
	void setIndexedValue(int i , T value);
	void setIndexedLazy(int i, T lazy);
	void setLength(int len) { m_len = len; }

	int getIndexedLeftValue(int idx);
	int getIndexedRightValue(int idx);
	T getIndexedValue(int idx);
	T getIndexedLazy(int idx) { return m_tree[idx].getLazyFlag(); }
	Node<T>& getIndexedNode(int idx);
	int getLength() { return m_len; };
	void change(int idx, int k, T y);
	T search(int idx, int l, int r);
	void changeSection(int idx, int a, int b, T y);
	
	void singlePointAdding(int k, T y);
	void sectionAdding(int a, int b, T y);
	T searchSection(int l, int r);
	void lazyPushDown(int idx);

private:
	Node<T>* m_tree;
	int m_len;
};

/////////////////////////////////////////////////////////////////
template<typename T>
T SegmentTree<T>::buildTree(vector<T> data, int l, int r, int idx)
{
	m_tree[idx].setLeft(l);
	m_tree[idx].setRight(r);
	if (l == r)
	{
		m_tree[idx].setValue(data[l]);
		return data[l];
	}
	int mid = (l + r) >> 1;
	T value = 0;
	value += buildTree(data, l, mid, 2 * idx);
	value += buildTree(data,mid+1,r,2*idx+1);
	m_tree[idx].setValue(value);
	return value;

}

template<typename T>
SegmentTree<T>::SegmentTree(vector<T> data)
{
	if (!data.empty())
	{
		 m_len = 4*data.size()+1;
		 m_tree = new Node<T>[m_len];
		 buildTree(data, 0, data.size()-1, rootIndex);
	}
	else
	{
		m_tree = nullptr;
		m_len = 0;
	}	
}

template<typename T>
SegmentTree<T>::SegmentTree(const SegmentTree& other)
{
	if (&other != this)
	{
		m_len = other.getLength();
		m_tree = new Node<T>[m_len];
		//::memcpy(m_tree, other.getTree(), m_len * sizeof(Node<T>));
		for (int i = 0; i < m_len; ++i)
		{
			setIndexedLeftValue(i, other.getIndexedLeft(i));
			setIndexedRightValue(i, other.getIndexedRight(i));
			setIndexedValue(i, other.getIndexedValue(i));
		}
	}
}
template<typename T>
SegmentTree<T>::SegmentTree(const SegmentTree&& other)
{
	*this = std::move(other);
}
template<typename T>
SegmentTree<T>::~SegmentTree()
{
	if (!m_tree)
	{
		delete[] m_tree;
		m_len = 0;
	}
}

template<typename T>
void 
SegmentTree<T>::setIndexedLeftValue(int i, int l)
{
	if (i < 0 || i >= m_len)
		return NaN;
	m_tree[i].setLeft(l);
}
template<typename T>
void 
SegmentTree<T>::setIndexedRightValue(int i, int r)
{
	if (i < 0 || i >= m_len)
		return NaN;
	m_tree[i].setRight(r);
}
template<typename T>
void 
SegmentTree<T>::setIndexedValue(int i, T value)
{
	if (i < 0 || i >= m_len)
		return ;
	m_tree[i].setValue(value);
}
template<typename T>
int
SegmentTree<T>::getIndexedLeftValue(int i)
{
	if (i < 0 || i >= m_len)
		return NaN;
	return m_tree[i].getLeft();
}

template<typename T>
int 
SegmentTree<T>::getIndexedRightValue(int i)
{
	if (i < 0 || i >= m_len)
		return NaN;
	return m_tree[i].getRight();
}
template<typename T>
T
SegmentTree<T>::getIndexedValue(int i)
{
	if (i < 0 || i >= m_len)
		return (T)NaN;
	return m_tree[i].getValue();
}
template<typename T>
void
SegmentTree<T>::change(int idx, int k, T y) //idx: trees' index, k: point's index, y: target value
{
	//把原始数组中（原始数组，即生成线段树的数组）下标为k的元素的值，加上y， idx 是树中节点的下标
	int left = getIndexedLeftValue(idx);
	int right = getIndexedRightValue(idx);
	T value = getIndexedValue(idx);
	if (left == right)
	{
		setIndexedValue(idx, value+y);
		return;
	}
	int mid = (left + right) >> 1;
	if (k <= mid)
	{
		change(2*idx,k, y);
	}
	else
	{
		change(2 * idx+1, k, y);
	}
	setIndexedValue(idx, getIndexedValue(2*idx) + getIndexedValue(2*idx+1));
	return ;
}
template<typename T>
T SegmentTree<T>::search(int idx, int l, int r)
{
	int left = getIndexedLeftValue(idx);
	int right = getIndexedRightValue(idx);
	T lazy = getIndexedLazy(idx);
	if (left == l && right == r)
		return getIndexedValue(idx) + (right - left + 1)* lazy;

	int mid = (left + right) >> 1;
	if (lazy > 0)
		lazyPushDown(idx);
	T sum = 0;
	if (r <= mid)
	{
		sum += search(2*idx,l,r);
	}
	else if (l >= mid + 1)
	{
		sum += search(2 * idx +1, l, r);
	}
	else
	{
		sum += search(2 * idx, l,mid);
		sum += search(2 * idx + 1, mid+1, r);
	}

	return sum;
}

template<typename T>
void SegmentTree<T>::changeSection(int idx, int a, int b, T y)
{
	int left = getIndexedLeftValue(idx);
	int right = getIndexedRightValue(idx);
	int sum = getIndexedValue(idx) + (b - a + 1) * y;
	if (left == a && right == b)
	{
		int lazy = getIndexedLazy(idx)+y;
		setIndexedLazy(idx, lazy);
		
		setIndexedValue(idx, sum);
		return;
	}
	setIndexedValue(idx, sum);
	int mid = (left + right) >> 1;
	if (b <= mid)
	{
		changeSection(idx << 1, a, b, y);
	}
	else if (a >= mid + 1)
	{
		changeSection(idx << 1|1, a, b, y);
	}
	else
	{
		changeSection(idx << 1, a, mid, y);
		changeSection(idx << 1 | 1, mid+1, b, y);
	}
}
template<typename T>
void 
SegmentTree<T>::setIndexedLazy(int i, T lazy)
{
	m_tree[i].setLazyFlag(lazy);
}
template<typename T>
void SegmentTree<T>::singlePointAdding(int k, T y)
{
	if (m_len <= 0)
		return;
	int left = getIndexedLeftValue(rootIndex);
	int right = getIndexedRightValue(rootIndex);
	if (k < left || k > right)
		return;

	change(rootIndex, k, y);
		
}
template<typename T>
void SegmentTree<T>::sectionAdding(int a, int b, T y)
{
	if (m_len <= 0)
		return;

	int left = getIndexedLeftValue(rootIndex);
	int right = getIndexedRightValue(rootIndex);
	if (a < left)
		a = left;
	if (b > right)
		b = right;
	changeSection(rootIndex,a,b,y);
}
template<typename T>
T SegmentTree<T>::searchSection(int l, int r)
{
	if (m_len <= 0)
		return NaN;

	int left = getIndexedLeftValue(rootIndex);
	int right = getIndexedRightValue(rootIndex);
	if (l < left)
		l = left;
	if (r > right)
		r = right;

	return search(rootIndex, l, r);
}
template<typename T>
void SegmentTree<T>::lazyPushDown(int idx)
{
	int l = getIndexedLeftValue(idx);
	int r = getIndexedRightValue(idx);
	int v = getIndexedValue(idx);
	int lazy = getIndexedLazy(idx);
	setIndexedValue(idx, v+(r-l+1)*lazy);
	setIndexedLazy(idx,0);

	T llazy = getIndexedLazy(idx << 1);
	T rlazy = getIndexedLazy(idx << 1 | 1);
	setIndexedLazy(idx << 1, llazy+lazy);
	setIndexedLazy(idx << 1 | 1, rlazy+lazy);
}

template<typename T>
Node<T>& SegmentTree<T>::getIndexedNode(int idx)
{
	return m_tree[idx];
}
template <typename T>
void dumpSegTree(SegmentTree<T>& tree)
{
	int len = tree.getLength();
	for (int i = 1; i < len; i++)
	{
		if (tree.getIndexedRightValue(i) != NaN)
		{
			cout << i << " --> ";
			auto node = tree.getIndexedNode(i);
			node.dumpNode();
			cout << endl;
		}
	}
}