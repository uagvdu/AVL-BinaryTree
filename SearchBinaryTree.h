#include<iostream>
using namespace std;

template<class K>
struct BinarySearchTreeNode
{
	BinarySearchTreeNode<K>* _left;
	BinarySearchTreeNode<K>* _right;
	K _key;
	BinarySearchTreeNode(const K& key)
		:_key(key)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class K>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K> BSNode;
public:
	BinarySearchTree()
		:_root(NULL)
	{}

	BinarySearchTree( BinarySearchTree<K>& BSTree)
	{
		 _root = _BinarySearchTree(BSTree._root);
	}

	BSNode*& operator=( BinarySearchTree<K> BSTree)
	{
		swap(_root,BSTree._root);
	}

	~BinarySearchTree()                               //类似于二叉树后序遍历的方式
	{
		if (_root != NULL)
		{
			_MakeEmptyTree(_root);
			_root = NULL;
		}
	}

public:

	bool  Insert(const K& key )   //三种情况：无_root, key已经存在， key不存在
	{
		if (_root == NULL)
		{
			 _root = new BSNode(key);
			return  true;
		}
		else 
		{
			BSNode* cur = _root;
			BSNode* parent = NULL;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else  if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
					return false;
			}
			if (parent->_key > key)
			{
				parent->_left = new BSNode(key);
			}
			else
			{
				parent->_right = new BSNode(key);
			}

			return true;
		}
	}

	bool Find(const K& key)
	{
		if (_root == NULL)
		{
			return false;
		}
		BSNode* cur = _root;
		BSNode* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return true;
		}
		return false;
	}

	bool Remove(const K& key)
		//三种情况：一：dst节点左右节点都为空，
		//二：dst节点左节点为空：其父节点指向dst节点的右节点 或者右节点为空，其父节点指向dst节点的左节点（第一种情况包含于第二种情况）
		//若删除的节点其左右子节点都不为NULL 则采用交换替代思想：dst节点与左树最大节点交换或者右树最小节点交换。 
	{
		if (_root == NULL)
		{
			return false;
		}
		else
		{
			BSNode *cur = _root;
			BSNode *parent = NULL;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					if (cur->_left == NULL)   //当前节点的左为NULL
					{
						if (parent != NULL)
						{
							if (parent->_key > key) //子节点要么全部比父节点大要么就全部比父节点小..//此处有可能出现父节点为NULL的情况：要么删除的是最后一个节点，要么就是单链：此时搜索效率最低
							{
								parent->_left = cur->_right;
								delete cur;
							}
							else
							{
								parent->_right = cur->_right;
								delete cur;
							}
							return true;
						}
						else 
						{
							_root = cur->_right;
							delete cur;
							return true;
						}
						
					}
					else if (cur->_right == NULL)             //右为NULL  此处包含左右都为NULL的节点
					{
						if (parent != NULL)
						{
							if (parent->_key > key)
							{
								parent->_left = cur->_left;
								delete cur;

							}
							else
							{
								parent->_right = cur->_left;
								delete cur;
							}
							return true;
						}
						else
						{
							_root = cur->_left;
							delete cur;
							return true;

						}
					}
					else                    
					{
						//左右不为NULL的情况,删除某个节点：要么交换该节点的下一个右节点，<优先考虑>要么交换该节点的下一个右节点的最左子节点，所以由此知if的成立条件
						parent = cur;
						BSNode* del = cur;
						del = del->_right;

						if (del->_left == NULL)
						{
							swap(parent->_key,del->_key);
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
			return false;
		}
	}


	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}
protected:


	BSNode*  _BinarySearchTree( BSNode*& root)
	{
		if (root == NULL)
			return NULL;
		BSNode* cur = root;
		BSNode* head = new BSNode(root->_key);
		head->_left = _BinarySearchTree(cur->_left);
		head->_right = _BinarySearchTree(cur->_right);
		return head;
	}

	void _MakeEmptyTree(BSNode*& root)
	{
		if (root == NULL)
			return;
		else
		{
			BSNode *cur = root;
			_MakeEmptyTree(cur->_left);
			_MakeEmptyTree(cur->_right);
			
			delete cur;
			cur = NULL;
			return;
		}

	}

	void _Inorder(BSNode* root)
	{
		if (root == NULL)
		{
			return;
		}
		BSNode* cur = root;
		_Inorder(cur->_left);
		cout << cur->_key << " ";
		_Inorder(cur->_right);
	}
protected:
	BSNode* _root;
};


void test()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BinarySearchTree<int> bs;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]);i++)
	{
		bs.Insert(a[i]);
	}

	bs.Inorder();
	cout << endl;
	cout << "Find: "<<bs.Find(3) << endl;
	cout << "Find: " << bs.Find(20) << endl;
	cout << "Remove<5>:"  ;
	bs.Remove(5);
	bs.Inorder();
	bs.Insert(a[0]);
	cout << "Remove<7>:";
	bs.Remove(7);
	bs.Inorder();

	BinarySearchTree<int> bs1(bs);
	cout << endl;
	cout << "bs1 & bs2:" << endl;
	bs1.Inorder();
	BinarySearchTree<int> bs2 = bs1;
	bs2.Inorder();


}
void test1()
{
	int a[] = { 5, 7, 8, 6, 9 };
	BinarySearchTree<int> bs;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		bs.Insert(a[i]);
	}
	bs.Inorder();
	for (int i = 0; i < sizeof(a) / sizeof(a[0]);i++)
	{
		bs.Remove(a[i]);
		cout << a[i] << endl;
		bs.Inorder();
	}
	

}