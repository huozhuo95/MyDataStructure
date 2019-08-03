/*
单向循环链表，头节点不存放数据，空链表为一个指向自身的头节点
节点有两个私有属性：数据区、链接区
*/

#ifndef _LOOPLIST_H
#define _LOOPLIST_H


/*
类的声明
*/

template<class T>
class LoopList;//前置声明，因为节点类里面要把MyList设置成友元类，而它还没有定义
template<class T>
class MyIterator;//同理，前置声明迭代器类

//节点类
template<class T>
class ListNode
{
	friend class LoopList<T>;//把链表类设为友元类，则数据成员可以让链表类调用
	friend class MyIterator<T>;//把迭代器类设为友元类
private:
	ListNode(){}//默认构造函数，用来构造表头节点，不存放数据
	ListNode(T);//有参数的构造函数
	T data;//数据区，存放元素
	ListNode* next;//链接区，指向下一个节点
};

//链表类
template<class T>
class LoopList
{
	friend class MyIterator<T>;//把迭代器类设为友元类
public:
	LoopList();//默认构造函数，初始指针为0
	void insert_node(T);//插入节点
	void delete_node(T);//删除节点
private:
	ListNode<T>* first;//私有数据成员为：指向第一个节点的指针，注意加上类型<T>
};

//迭代器类
template<class T>
class MyIterator
{
public:
	MyIterator(const LoopList<T>& ls) :list(ls), current(ls.first->next) {}//构造函数
	bool not_null();//用来判断指向的当前节点是否为空
	bool next_not_null();//判断下一个节点是否为空
	T* first();//返回指针，指向链表的第一个节点
	T* next();//返回当前节点的下一个节点的指针，同时current移到下一个节点
private:
	//私有数据成员：链表和指向当前节点的指针
	const LoopList<T>& list;
	ListNode<T>* current;
};

/*
成员函数的实现
*/

/*
节点类的成员函数的实现
*/

//节点构造函数
template<class T>
ListNode<T>::ListNode(T element)
{
	data = element;
	next = 0;//指针为空，作用等于=NULL
}


/*
循环链表类的成员函数的实现
*/

//循环链表构造函数
template<class T>
LoopList<T>::LoopList()
{
	first = new ListNode<T>;//创建一个节点，不存放实际元素
	first->next = first;//节点的链接域指向自己
}

//在表头与第一个存放数据的节点之间插入新的节点，参数为节点的数据元素
template<class T>
void LoopList<T>::insert_node(T item)
{
	ListNode<T>* new_node = new ListNode<T>(item);//创建新节点
	new_node->next = first->next;//新节点的链接域指向表头的下一个节点
	first->next = new_node;//表头的链接域指向新节点
}

//删除节点，参数为要删除的节点里的数据元素
template<class T>
void LoopList<T>::delete_node(T item)
{
	//找出那个元素所在的节点，即找到指向那个节点的指针
	//要把那个指针改为指向下一个节点
	ListNode<T>* previous = first;
	ListNode<T>* current;
	for (current = first->next;//初始指针指向第二个节点
		current != first && current->data != item; //判断是否指向表头，或者是否找到了item
		previous = current, current = current->next)//每次进行下轮循环之前，记录上一个节点的指针
	{
	}//上面这个for循环为空循环
	if (current != first)//如果找到了
	{
		previous->next = current->next;//将前一个的链接域和当前节点的后面节点连接
		delete current;//删除当前节点，释放内存
	}
}

/*
迭代器类的成员函数的实现
*/

//迭代器指向的当前节点是否为空
template<class T>
bool MyIterator<T>::not_null()
{
	if (current != list.first)//如果当前节点的指针指向表头，说明链表为空
		return true;
	else
		return false;
}

//迭代器指向的当前节点的下一个节点是否为空
template<class T>
bool MyIterator<T>::next_not_null()
{
	if (current->next != list.first)//first指向表头，不存数据
		return true;
	else
		return false;
}

//返回一个指针，它指向所属链表的第一个数据(即第二个节点)
template<class T>
T* MyIterator<T>::first()
{
	if (list.first->next != list.first)//如果第二个节点不是第一个节点
		return &list.first->next->data;//返回第二个节点指向的节点的数据域的地址
	else
		return 0;
}

//返回一个指针，指向当前节点的下一个节点的数据，同时current向后移
template<class T>
T* MyIterator<T>::next()
{
	current = current->next;//由于是环形链表，必定可以向后移
	if (current == list.first)//如果当前节点为表头，要再后移一次
		current = current->next;
	return &current->data;//返回数据域的地址
	//注意！！此时迭代器的数据成员已经改变，不必像STL中的迭代器一样对迭代器进行加减
}


#endif
