#ifndef TREENODE_H
#define TREENODE_H

template <typename KeyT, typename ValueT> class BST;

template <typename KeyT, typename ValueT>
class TreeNode
{
	friend class BST<KeyT, ValueT>;
public:
	TreeNode(const KeyT &k, const ValueT &v) 
	{
		lchild = rchild = NULL;
		key = k;
		value = v;
	}
	KeyT getKey()		{ return key; }
	ValueT getValue()	{ return value; }

protected:
	TreeNode<KeyT, ValueT>	*lchild;
	KeyT	key;
	ValueT	value;
	TreeNode<KeyT, ValueT> *rchild;
};
#endif