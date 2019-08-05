/*
双向链表，分为节点、链表、迭代器三个类
节点有三个私有属性：数据域、左链接域、右链接域
表头为空节点，不存放数据
*/

#ifndef _DBLIST_H
#define _DBLIST_H

//前置声明，设置友元
template<class T>
class DbList;
template<class T>
class MyIterator;

//节点类的声明
template<class T>
class ListNode
{
	friend class DbList<T>;
	friend class MyIterator<T>;
private:
	ListNode() { data = T(); left = 0; right = 0; }//默认构造函数，用来创建表头
	ListNode(T);//有参数的构造函数，用来添加元素
	T data;//数据域
	ListNode<T>* left;//左链接域
	ListNode<T>* right;//右链接域
};

//双向链表类
template<class T>
class DbList
{
	friend class MyIterator<T>;
public:
	DbList();
	void insert_left(T);//在左端插入节点
	void insert_right(T);//在右端插入节点
	void delete_node(T);//删除节点
private:
	ListNode<T>* first;
};

//迭代器类
template<class T>
class MyIterator
{
public:
	MyIterator(const DbList<T>& ls) :list(ls), current(ls.first->right) {}//构造函数
	bool not_null();
	bool left_not_null();
	bool right_not_null();
	T* first();
	T* left();
	T* right();
private:
	DbList<T> list;
	ListNode<T>* current;
};

/*
成员函数的实现
*/

/*
节点类的成员函数
*/

//节点的含有参数的构造函数
template<class T>
ListNode<T>::ListNode(T item)
{
	data = item;
	left = 0;
	right = 0;
}

/*
双向链表类的成员函数
*/

//双向链表的默认构造函数
template<class T>
DbList<T>::DbList()
{
	ListNode<T>* new_node = new ListNode<T>;//新建一个节点作为表头，不存放数据
	first = new_node;//让first指针指向该节点
	first->left = first;//左链接域指向自己
	first->right = first;//右链接域也指向自己
}

//在链表左端添加节点，实际在表头的右边一个
template<class T>
void DbList<T>::insert_left(T item)
{
	ListNode<T>* new_node = new ListNode<T>(item);
	new_node->left = first->left;//左连接域指向表头
	if (first->right == first)//如果链表为空，
		new_node->right = new_node;
	else
	{
		new_node->right = first->right;//右链接域指向第二个节点
		first->right->left = new_node;//第二个节点的左链接域指向新节点
	}
	first->right = new_node;//表头的右链接域指向新节点
}

//在链表右端添加节点，速度较慢
template<class T>
void DbList<T>::insert_right(T item)
{
	ListNode<T>* new_node = new ListNode<T>(item);//创建新节点
	new_node->right = new_node;//新节点在右端，所以它的右链接域指向它自己
	ListNode<T>* current = first;//current用来遍历链表，找出最右边的节点
	while (current->right != current)
		current = current->right;
	current->right = new_node;//找到之后，把最右边的节点的right指向新节点
	new_node->left = current;//新节点的left指向原来的最右节点
}

//删除第一个(最左边)数据为item的节点
template<class T>
void DbList<T>::delete_node(T item)
{
	ListNode<T>* current = first;
	while (current->right != current && current->data != item)
		current = current->right;
	if (current->data == item)
	{
		if (current->right == current)//如果是最右边的节点
			current->left->right = current->left;//把倒数第二个节点的right指向它自己
		else//如果要删除的节点在中间
		{
			current->left->right = current->right;//它左边的节点的right指向它右边
			current->right->left = current->left;//它右边的节点的left指向它左边
		}
		delete current;//删除节点释放内存
	}
}

/*
迭代器类的成员函数
*/

//判断当前节点是否为空节点
template<class T>
bool MyIterator<T>::not_null()
{
	if (current != list.first)//如果不是表头，就不为空
		return true;
	else
		return false;
}

//判断左边不为空，即当前节点不是最左边的那个
template<class T>
bool MyIterator<T>::left_not_null()
{
	if (current->left != list.first)//如果左边的节点不是链表的表头，返回真
		return true;
	else
		return false;
}

//判断右边不为空，即当前节点不是最右边的那个
template<class T>
bool MyIterator<T>::right_not_null()
{
	if (current->right != current)//如果右链接域不指向它自己，返回真
		return true;
	else
		return false;
}

//获取第一个元素的指针
template<class T>
T* MyIterator<T>::first()
{
	if (list.first->right != list.first)//如果表头右边有节点，就返回该节点数据的地址
	{
		current = list.first->right;//修改数据成员current，使它指向第一个数据节点
		return &current->data;
	}
	else
		return 0;
}

//获取当前节点的左边节点的数据指针
template<class T>
T* MyIterator<T>::left()
{
	if (left_not_null())//如果它不是最左边的节点
	{
		current = current->left;//修改数据成员current，让它指向左边节点
		return &current->data;//返回左边节点的数据地址
	}
	else
		return 0;
}

//获取当前节点的右边节点的数据指针
template<class T>
T* MyIterator<T>::right()
{
	if (right_not_null())//如果它不是最右边的节点
	{
		current = current->right;//修改数据成员current，让它指向右边节点
		return &current->data;//返回右边节点的数据地址
	}
	else
		return 0;
}

#endif
