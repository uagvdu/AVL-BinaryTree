#include<iostream>
using namespace std;

template<class K>
struct RBinarySearchTreeNode//递归
{
	RBinarySearchTreeNode<K>* _left;
	RBinarySearchTreeNode<K>* _right;
	K _key;
	RBinarySearchTreeNode(const K& key)
		:_key(key)
		, _left(NULL)
		, _right(NULL)
	{}
};
template<class K>
class SearchBinaryTree
{
	typedef RBinarySearchTreeNode<K> RNode;
public:
	bool Find(const K& key)
	{
		return _Find(_root,key);
	}

	bool  Insert(const K& key)
	{
		return _Insert(_root,key);

	}

	bool Remove(const K& key)
	{
		return _Remove(_root,key);
	}

	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

protected:
	void _Insert(RNode*& root,const K& key)
	{
		if (root == NULL)
		{
			root = new RNode(key);
			return true;
		}
		else
		{
			RNode* cur = root;
			if (cur->_key > key)
			{
				_Insert(cur->_left, key);
				return true;
			}
			else	if (cur->_key < key)
			{
				_Insert(cur->_right,key);
				return true;
			}
			else
				return false;
		}
	}

	bool _Find(RNode*& root, const K& key)
	{
		if (root == NULL)
		{
			return false;
		}
		else
		{
			RNode* cur = root;
			if (cur->_key > key)
			{
				return _Find(cur->_left, key);;
			}

			else 	if (cur->_key < key)
			{
				return _Find(cur->_right, key);

			}
			else
				return true;
		}
	}
	bool  _Remove(RNode*& root,const K& key)   //引用代表别名，
	{
		if (root == NULL)
			return false;
		else
		{
			RNode* cur = root;
			RNode* parent = NULL;
			if (cur->_key > key)
			{
				return _Remove(cur->_left);
			}
			else if (cur->_key < key)
			{
				return _Remove(cur->_left);
			}
			else
			{
				if (cur->_left == NULL)
				{
					RNode* del = cur;
					cur = cur->_right;             
				//因为引用代表别名，那么此处的cur不就是上一个节点的左子节点，所以当cur发生改变的时候，其上一个节点的左子节点自然而然的也指向cur->right,别名的好处。
					
					delete del;
				}
				else if (cur->_right ==NULL)
				{
					RNode* del = cur;
					cur = cur->_left;
					delete del;

				}
				else
				{
					parent = cur;
					BSNode* del = cur;
					del = del->_right;

					if (del->_left == NULL)
					{
						swap(parent->_key, del->_key);
						parent->_right = del->_right;
						delete del;
						return true;
					}

					else
					{
						while (del->_left)
						{
							parent = del;
							del = del->_left;
						}
						swap(cur->_key, del->_key);
						parent->_left = del->_right;
						delete del;
						return true;
					}
				}
			}
		}
	}

	void _Inorder(RNode* root)
	{
		if (root ==NULL)
		{
			return;
		}
		else
		{
			_Inorder(root->_left);
			cout << root->_key;
			_Inorder(root->_right);
		}
	}
protected:
	RNode* _root;
};

void test2()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BinarySearchTree<int> bs;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		bs.Insert(a[i]);
	}
	bs.Inorder();
	cout << endl;
	
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		cout << "Find: " << bs.Find(1) << endl;
	}
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		bs.Remove(a[i]);
		cout << a[i] << endl;
		bs.Inorder();
	}

}