/*
二叉查找树，每个节点最多有两个子节点：左子节点和右子节点
左边的节点比根小，右边的比根大
并且左子节点和右子节点也都是二叉查找树
缺点：如果每次都添加更小(或更大)的元素，它会变得和链表一样了，不会自动平衡
*/

#ifndef _BINARYTREE_H
#define _BINARYTREE_H
#include<iostream>
#include"MyQueue.h"//层序遍历需要用到队列

/*
类的声明
*/

//前置声明
template<class T>
class BinaryTree;
template<class T>
class TreeIterator;

//节点类
template<class T>
class TreeNode
{
	friend class BinaryTree<T>;
	friend class TreeIterator<T>;
private:
	TreeNode() { data = T(); left_child = 0; right_child = 0; }//构造函数
	T data;//存放的数据
	TreeNode<T>* left_child;//指向左子节点
	TreeNode<T>* right_child;//指向右子节点
};

//树类
template<class T>
class BinaryTree
{
	friend class TreeIterator<T>;
public:
	BinaryTree() { root = 0; }//默认构造函数为空树
	bool insert(const T&);//插入一个节点，参数为节点数据元素，如果插入成功，返回真
	bool search(const T&);//查找某个元素
	bool search(TreeNode<T>*, const T&);//函数重载
	void visit(TreeNode<T>*);//打印节点数据
	void prev_order();//前序遍历：根、左子、右子
	void prev_order(TreeNode<T>*);//重载
	void mid_order();//中序遍历：左子、根、右子，得到从小到大的排序
	void mid_order(TreeNode<T>*);//重载
	void post_order();//后序遍历：左子、右子、根
	void post_order(TreeNode<T>*);//重载
	void level_order();//层序遍历：顶层、第二层、第三层……
private:
	TreeNode<T>* root;//指向根节点的指针
};

template<class T>
class TreeIterator
{
	friend class BinaryTree<T>;
public:
	TreeIterator(const BinaryTree<T>& bst) :bs_tree(bst), current(bst.root) {}//构造函数
	inline bool not_null()const;//判断当前节点不为空
	inline bool left_not_null()const;//判断左子节点不为空
	inline bool right_not_null()const;//判断右子节点不为空
	T* point();//返回当前指向的元素地址
	T* root();//指向二叉搜索树的根节点，并返回元素地址
	T* left_child();//指向左子节点，并返回元素地址
	T* right_child();//指向右子节点，并返回元素地址
private:
	const BinaryTree<T>& bs_tree;//与迭代器关联的树
	TreeNode<T>* current;//迭代器当前指向的节点
};

/*
成员函数的实现
*/

/*
二叉树的成员函数
*/

//插入数据元素节点
template<class T>
bool BinaryTree<T>::insert(const T& item)
{
	TreeNode<T>* p = root;//p用来遍历二叉树，要查找item该插入的位置
	TreeNode<T>* q = 0;//q指向p的根结点
	while (p)
	{
		q = p;//保存p节点的指针
		if (item == p->data)//如果重复，添加节点失败
			return false;
		if (item < p->data)//小于根，就放左边
			p = p->left_child;
		else//大于根，就放右边
			p = p->right_child;
	}
	//退出循环的时候，找到的位置就是q的下面
	//创建新的节点并初始化
	p = new TreeNode<T>;
	p->left_child = 0;
	p->right_child = 0;
	p->data = item;
	if (root == 0)//如果树根为NULL，就直接把root指向新节点
		root = p;
	else if (item < q->data)
		q->left_child = p;
	else
		q->right_child = p;
	return true;
}

//查找某个元素
template<class T>
bool BinaryTree<T>::search(const T& item)
{
	return search(root, item);
}

//查找函数的重载
template<class T>
bool BinaryTree<T>::search(TreeNode<T>* current, const T& item)
{
	if (current == 0)//如果指针为空，表示没有找到
		return false;
	if (current->data == item)//如果找到了，返回真
		return true;
	if (item < current->data)//如果比当前节点元素小，就往左子节点递归找
		return search(current->left_child, item);
	else//如果比当前节点元素大，就往右子节点递归找
		return search(current->right_child, item);
}

//打印当前节点
template<class T>
void BinaryTree<T>::visit(TreeNode<T>* current)
{
	std::cout << current->data <<" ";
}

//前序遍历
template<class T>
void BinaryTree<T>::prev_order()
{
	prev_order(root);
}

//前序遍历的函数重载
template<class T>
void BinaryTree<T>::prev_order(TreeNode<T>* current)
{
	if (current == 0)//递归出口
		return;
	visit(current);	//显示当前节点
	prev_order(current->left_child);//再遍历左子树
	prev_order(current->right_child);//再遍历右子树
}

//中序遍历
template<class T>
void BinaryTree<T>::mid_order()
{
	mid_order(root);
}

//中序遍历的函数重载
template<class T>
void BinaryTree<T>::mid_order(TreeNode<T>* current)
{
	if (current == 0)//递归出口
		return;
	mid_order(current->left_child);//先遍历左子树
	visit(current);//再显示当前节点
	mid_order(current->right_child);//再遍历右子树
}

//后序遍历
template<class T>
void BinaryTree<T>::post_order()
{
	post_order(root);
}

//后序遍历的函数重载
template<class T>
void BinaryTree<T>::post_order(TreeNode<T>* current)
{
	if (current == 0)//递归出口
		return;
	post_order(current->left_child);//先遍历左子树
	post_order(current->right_child);//再遍历右子树
	visit(current);//再显示当前节点
}

//层序遍历
template<class T>
void BinaryTree<T>::level_order()
{
	MyQueue<TreeNode<T>*> que;//创建一个队列
	TreeNode<T>* current = root;//创建一个节点指针用来遍历，初始化为根节点
	while (current)
	{
		visit(current);//显示该节点
		if (current->left_child)//先添加左子节点入队
			que.push(current->left_child);
		if (current->right_child)//后添加右子节点入队
			que.push(current->right_child);
		if (que.is_empty())//如果队列为空了，就跳出循环
			break;
		else//否则指针改为队首的元素，即指向刚刚节点的左子节点，并出队
		{
			current = que.front_item();
			que.pop();
		}
	}
}

/*
迭代器的成员函数实现
*/

//判断当前节点不为空
template<class T>
inline bool TreeIterator<T>::not_null()const
{
	return current ? true : false;
}

//判断左子节点不为空
template<class T>
inline bool TreeIterator<T>::left_not_null()const
{
	if (current)
	{
		if (current->left_child)
			return true;
		else
			return false;
	}
	else
		return false;
}

//判断右子节点不为空
template<class T>
inline bool TreeIterator<T>::right_not_null()const
{
	if (current)
	{
		if (current->right_child)
			return true;
		else
			return false;
	}
	else
		return false;
}

//返回当前指向的元素地址
template<class T>
T* TreeIterator<T>::point()
{
	if (current)
		return &current->data;
	else
		throw"The tree has no node.";
}

//指向二叉搜索树的根节点，并返回元素地址
template<class T>
T* TreeIterator<T>::root()
{
	current = bs_tree.root;
	return current ? &current->data : 0;
}

//指向左子节点，并返回元素地址
template<class T>
T* TreeIterator<T>::left_child()
{
	if (not_null()&&left_not_null())
	{
		current = current->left_child;
		return &current->data;
	}
	else
		return 0;
}

//指向右子节点，并返回元素地址
template<class T>
T* TreeIterator<T>::right_child()
{
	if (not_null() && right_not_null())
	{
		current = current->right_child;
		return &current->data;
	}
	else
		return 0;
}

#endif
