/*
链表，分为节点和链表两个类
节点有两个私有属性：数据区、链接区
*/

#ifndef _MYLIST_H
#define _MYLIST_H

/*
类的声明
*/

template<class T>
class MyList;//前置声明，因为节点类里面要把MyList设置成友元类，而它还没有定义

//节点类
template<class T>
class ListNode
{
friend class MyList<T>;//把链表类设为友元类，则数据成员可以让链表类调用
private:
	ListNode(T);//参数为数据元素，构造函数为私有，只能用链表类来调用，不能外界创建Node类的对象
	T data;//数据区，存放元素
	ListNode* next;//链接区，指向下一个节点
};

//链表类
template<class T>
class MyList
{
public:
	MyList();//默认构造函数，初始指针为0
	void insert_node(T);//插入节点
	void delete_node(T);//删除节点
	void invert();//反转
	void concatenate(MyList<T>);//将两个链表连接
	void show();//测试函数，用来展示节点的数据
private:
	ListNode<T>* first;//私有数据成员为：指向第一个节点的指针，注意加上类型<T>
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
链表类的成员函数的实现
*/

//链表构造函数
template<class T>
MyList<T>::MyList()
{
	first = 0;//指针为空，作用等于=NULL
}

//在链表头部插入新的节点，参数为节点的数据元素
template<class T>
void MyList<T>::insert_node(T item)
{
	//定义一个ListNode类型的指针，开辟一个节点类型空间，初始值为item，让指针指向这个对象
	ListNode<T>* new_node = new ListNode<T>(item);
	//把这个新的节点对象放在链表头部，因此，此节点的下一个位置是链表的第一个节点
	//所以，新节点对象的链接区为原来链表的first指针
	new_node->next = first;
	//现在新节点为第一个节点了，链表的first指针也要指向这个新节点
	first = new_node;
}

//删除节点，参数为要删除的节点里的数据元素
template<class T>
void MyList<T>::delete_node(T item)
{
	//找出那个元素所在的节点，即找到指向那个节点的指针
	//要把那个指针改为指向下一个节点
	ListNode<T>* previous = 0;
	ListNode<T>* current;
	for (current = first;//初始指针为first
		current != 0 && current->data != item; //判断是否指向空值，或者是否找到了item
		previous = current, current = current->next)//每次进行下轮循环之前，记录上一个节点的指针
	{ }//上面这个for循环为空循环
	if (current)//如果找到了
	{
		//分两种情况：1.找到的为第一个节点；2.找到的不是第一个节点
		//情况1，不存在上一个节点，直接将first后移
		if (previous == 0) first = first->next;
		//情况2，将上一个节点的next指向要删除节点的下一个节点
		else previous->next = current->next;
		delete current;//释放current指向的内存空间
	}
}

//反转
template<class T>
void MyList<T>::invert()
{
	ListNode<T>* p_current = first;//当前结点，初始化为头结点
	ListNode<T>* p_prev = 0;//前一个结点，初始化为NULL
	ListNode<T>* p_end = 0;//尾节点，找到尾节点后再赋值，作为反转后的首结点地址
	while (p_current != 0)
	{
		ListNode<T>* p_temp = p_current->next;//存放下一个结点的地址，否则改变链接域之后找不到下一个结点了
		if (p_temp == 0)//判断当前结点是否为尾节点
			p_end = p_current;//如果是，就把它赋值给p_end指针
		p_current->next = p_prev;//改变当前结点的链接域，使其指向前一个结点
		p_prev = p_current;//当前结点的反转也完成，现在更新前一个结点的地址，为后续循环使用
		p_current = p_temp;//更新当前结点的地址
	}
	first = p_end;//把头结点地址更新
}

//连接两个链表
template<class T>
void MyList<T>::concatenate(MyList<T> ls)//参数中的链表为第二个
{
	//如果第一个链表是空的
	if (!first)
	{
		first = ls.first;
		return;
	}
	//如果第二个链表不是空的
	if (ls.first)
	{
		ListNode<T>* p = first;
		//遍历第一个链表，找出最后一个节点
		while (p->next)
			p = p->next;
		//连接第二个链表的头节点
		p->next = ls.first;
	}
}

//显示链表内的所有节点的元素
template<class T>
void MyList<T>::show()
{
	ListNode<T>* p = first;//开始指向第一个节点
	while (p != 0)//如果指针为空，那么退出循环
	{
		std::cout << p->data;//打印当前节点的数据元素
		p = p->next;//打印完了立马让指针指向下一个节点
		if (p == 0)
		{
			std::cout << std::endl;
			return;
		}
		std::cout << "->";
	}
}

#endif
