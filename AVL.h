#pragma once
#include<iostream>
using namespace std;

template <class K,class V>
struct AVLNode
{
	AVLNode* _left;
	AVLNode* _right;
	AVLNode* _parent;
	int _bf;
	K _key;
	V _value;
	AVLNode(const K& key,const V& value )
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		,_bf(0)
		, _key(key)
		, _value(value)
	{}
};

template <class K, class V>
class AVLTree
{
	typedef  AVLNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	bool Insert(const K& key,const V& value )
	{
		return _Insert(key,value);
	}
	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}
	int Height()
	{
		return _Height(_root);
	}

	bool IsBlance()
	{
		return _IsBlance(_root);
	}
protected:

	bool _IsBlance(Node* root)           //判断是否平衡，不仅需要看bf ,还需要看子树的高度差，只有当子树高度差与bf相等且小于2大于-2
	{
		if (root == NULL)
		{
			return false;
		}

		Node *cur = root;
		int left = _Height(root->_left);
		int right = _Height(root->_right);
	
		if (cur->_bf != (right - left)||abs(right-left)>1)
		{
			cout << "平衡因子异常: " << cur->_key << " " << endl;
		}
		else
		{
			return true;
		}
	}

	int _Height(Node *root)    //当前子树节点的高度 = 左右子树中大的高度+1
	{
		if (root == NULL)
		{
			return 0;
		}
		int LeftH = _Height(root->_left);
	    int RightH = _Height(root->_right);
		return LeftH > RightH ? LeftH+1 : RightH+1;

	}

	bool _Insert( const K& key, const V& value)  //凡是搜索二叉树：必有step1 ：想插入就必须找该树的NULL节点，只在此处进行插入,不论什么类型的搜索二叉树
	{
		if (_root == NULL)
		{
			_root = new Node (key,value);
			return true;
		}
		else
		{
			Node* cur = _root;
			Node * parent = NULL;
			while (cur)
			{
				if (cur->_key > key)    //key在左
				{
					parent = cur;
					cur = cur->_left;
					if (cur!=NULL)
					    cur->_parent = parent;
				}
				else if(cur->_key < key)   //key在右
				{
					parent = cur;
					cur = cur->_right;
					if (cur != NULL)
						cur->_parent = parent;
				}
				else                     //找到key
				{
					return false;
				}

			}
			cur = new Node (key,value);
			cur->_parent = parent;//在此之前代表： 找到NULL节点以及在该位置插入新的节点，
		
			if (parent->_key > key)
			{
				parent->_left = cur;
			}
			else
				parent->_right = cur;//插入数据之后还有进行平衡因子的判断
			//每插入新的节点的时候，需要考虑：_bf<平衡因子>的变化。三种情况：父节点为零，则到此终止，继续执行插入操作，父节点为- +1，往上走，父节点为+ - 2的时候，进行旋转调整。
			//平衡因子的符号取决于插入的节点是父节点的左还是右
			while (parent)
			{
				if (parent->_left == cur)
				{
					parent->_bf--;

				}
				else
					parent->_bf++;

				if (parent->_bf == 0) //因为没有影响树的高度
					break;

				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					cur = parent;
					parent = parent->_parent;
				}
				else                  //   _bf == + - 2 ;会出现四种旋转情况，但又该如何判断是哪种情况呢？
				{
					if (cur->_bf == 1)          //AVL满足条件 左右子树高度差不能大于1，而不是指在parent ->_bf = 2 时 ，其插入的新的节点距离parent节点中间只有一个cur
					{                         //一开始我写的条件判断if(parent->_left ==NULL &&cur->_left ==NULL) 认为由此可得左旋，就是认为_bf = 2的时候，只能出现parent，cur，和cur的子节点，
						                       //parent的左或者右不一定为NULL，cur的左或者右同样也不一定为NULL
						if (parent->_bf == 2)          //左旋  ：方法：假设parent，cur和新插入的节点，都有子节点，但可以看作只有这三个节点，来确定该执行哪种旋转
						{
							_LRotate(parent );

						}
						else                            //左右旋  :向左凸
						{
							_LRRotate(parent );

						}
					}
					else 
					{
						if (parent->_bf == 2)                //右左旋
						{
							_RLRotate(parent );

						}
						else                                //右旋
						{
							_RRotate(parent );

						}
						
					}
					break;
				}
			}
			return true;

		}
	}


	
protected:
	void _Inorder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		else
		{
			_Inorder(root->_left);
			cout << root->_key<<" ";
			_Inorder(root->_right);
		}
	}

	void _RRotate(Node* parent )
	{
		Node *Lsub = parent->_left;
		Node *LRsub = Lsub->_right;
		Node *ppNode = parent->_parent;
		Lsub->_right = parent;
		parent->_left = LRsub;
		parent->_parent = Lsub;
		
		if (LRsub != NULL)
		{
			LRsub->_parent = parent;
		 
		}
		if (ppNode == NULL)
		{
			_root = Lsub;
			_root->_parent = NULL;
		}
		else
		{
			Lsub->_parent = ppNode;
			if (ppNode->_left == parent)
			{
				ppNode->_left = Lsub;
			}
			else
				ppNode->_right = Lsub;
		}
		parent->_bf = Lsub->_bf= 0;   

	}

	void _LRotate(Node* parent )
	{
	
		Node* Rsub = parent->_right;
		Node* RLsub = Rsub->_left;
		Node* ppNode = parent->_parent;
		Rsub->_left = parent;
		parent->_parent = Rsub;
		parent->_right = RLsub;
		if (RLsub != NULL)
		{
			RLsub->_parent = parent;
		}

		if (ppNode == NULL)
		{
			_root = Rsub;
			Rsub->_parent = NULL;
		}
		else
		{
			Rsub->_parent = ppNode;
			if (ppNode->_left == parent)
			{
				ppNode->_left = Rsub;
			}
			else
				ppNode->_right = Rsub;
		}
		parent->_bf = Rsub->_bf = 0;

	}

	void _LRRotate(Node* parent )
	{
		Node* Lsub = parent->_left;
		Node* LRsub = Lsub->_right;
		_LRotate(Lsub);
		_RRotate(parent);
		if (LRsub->_bf==0)
		{
			LRsub->_bf = parent->_bf = Lsub->_bf;
		}
		else if (LRsub->_bf == 1)
		{
			Lsub->_bf = -1;
			parent->_bf = 0;
			LRsub->_bf = 0;
		}
		else
		{
			Lsub->_bf = 0;
			parent->_bf = 1;
			LRsub->_bf = 0; 
		}

	}

	void _RLRotate(Node* parent )
	{
		Node * Rsub = parent->_right;
		Node* RLsub = Rsub->_left;
		_RRotate(Rsub);
		_LRotate(parent);
		if (RLsub->_bf == 0)          //代表新插入的节点，
		{
			RLsub->_bf = parent->_bf = RLsub->_bf = 0;
		}
		else if (RLsub->_bf == 1)              //新插入的节点，将旧节点由零变为1 或者-1
		{
			Rsub->_bf = 0;
			parent->_bf = -1;
			RLsub->_bf = 0;
		}
		else
		{
			Rsub->_bf = 1;
			parent->_bf = 0;
			RLsub->_bf = 0;
		}
	}
	
	

private:
	Node* _root;

};


void test4()
{
	int a[ ] = {16,3,7,11,9,26,18,14,15};
	AVLTree<int, int> v;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		v.Insert(a[i],0);
	}
	v.Inorder();
	cout << endl;
	cout<< "Height:"<<v.Height()<<endl;
	cout<<"Blance: "<<v.IsBlance()<<endl;
}