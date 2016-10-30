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

	bool _IsBlance(Node* root)           //�ж��Ƿ�ƽ�⣬������Ҫ��bf ,����Ҫ�������ĸ߶Ȳֻ�е������߶Ȳ���bf�����С��2����-2
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
			cout << "ƽ�������쳣: " << cur->_key << " " << endl;
		}
		else
		{
			return true;
		}
	}

	int _Height(Node *root)    //��ǰ�����ڵ�ĸ߶� = ���������д�ĸ߶�+1
	{
		if (root == NULL)
		{
			return 0;
		}
		int LeftH = _Height(root->_left);
	    int RightH = _Height(root->_right);
		return LeftH > RightH ? LeftH+1 : RightH+1;

	}

	bool _Insert( const K& key, const V& value)  //��������������������step1 �������ͱ����Ҹ�����NULL�ڵ㣬ֻ�ڴ˴����в���,����ʲô���͵�����������
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
				if (cur->_key > key)    //key����
				{
					parent = cur;
					cur = cur->_left;
					if (cur!=NULL)
					    cur->_parent = parent;
				}
				else if(cur->_key < key)   //key����
				{
					parent = cur;
					cur = cur->_right;
					if (cur != NULL)
						cur->_parent = parent;
				}
				else                     //�ҵ�key
				{
					return false;
				}

			}
			cur = new Node (key,value);
			cur->_parent = parent;//�ڴ�֮ǰ���� �ҵ�NULL�ڵ��Լ��ڸ�λ�ò����µĽڵ㣬
		
			if (parent->_key > key)
			{
				parent->_left = cur;
			}
			else
				parent->_right = cur;//��������֮���н���ƽ�����ӵ��ж�
			//ÿ�����µĽڵ��ʱ����Ҫ���ǣ�_bf<ƽ������>�ı仯��������������ڵ�Ϊ�㣬�򵽴���ֹ������ִ�в�����������ڵ�Ϊ- +1�������ߣ����ڵ�Ϊ+ - 2��ʱ�򣬽�����ת������
			//ƽ�����ӵķ���ȡ���ڲ���Ľڵ��Ǹ��ڵ��������
			while (parent)
			{
				if (parent->_left == cur)
				{
					parent->_bf--;

				}
				else
					parent->_bf++;

				if (parent->_bf == 0) //��Ϊû��Ӱ�����ĸ߶�
					break;

				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					cur = parent;
					parent = parent->_parent;
				}
				else                  //   _bf == + - 2 ;�����������ת��������ָ�����ж�����������أ�
				{
					if (cur->_bf == 1)          //AVL�������� ���������߶Ȳ�ܴ���1��������ָ��parent ->_bf = 2 ʱ ���������µĽڵ����parent�ڵ��м�ֻ��һ��cur
					{                         //һ��ʼ��д�������ж�if(parent->_left ==NULL &&cur->_left ==NULL) ��Ϊ�ɴ˿ɵ�������������Ϊ_bf = 2��ʱ��ֻ�ܳ���parent��cur����cur���ӽڵ㣬
						                       //parent��������Ҳ�һ��ΪNULL��cur���������ͬ��Ҳ��һ��ΪNULL
						if (parent->_bf == 2)          //����  ������������parent��cur���²���Ľڵ㣬�����ӽڵ㣬�����Կ���ֻ���������ڵ㣬��ȷ����ִ��������ת
						{
							_LRotate(parent );

						}
						else                            //������  :����͹
						{
							_LRRotate(parent );

						}
					}
					else 
					{
						if (parent->_bf == 2)                //������
						{
							_RLRotate(parent );

						}
						else                                //����
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
		if (RLsub->_bf == 0)          //�����²���Ľڵ㣬
		{
			RLsub->_bf = parent->_bf = RLsub->_bf = 0;
		}
		else if (RLsub->_bf == 1)              //�²���Ľڵ㣬���ɽڵ������Ϊ1 ����-1
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