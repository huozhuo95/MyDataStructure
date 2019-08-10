//保护头文件，防止多重包含
#ifndef _MYSTACK_H
#define _MYSTACK_H

#include"my_Utility.h"//需要包含另一个头文件，用来扩大数组容量

//MyStack类的声明
template<class T>
class MyStack
{
public:
	MyStack( int c = 10 );//默认构造函数，初始容量为10
	~MyStack();//析构函数

	inline bool is_empty() const;//常成员函数，只读取，不改变数据成员的值
	inline T& top_item() const;//返回栈顶的元素，只读取（也叫peek）
	void push(const T& item);//往栈顶入栈，同时也要保护item
	void pop();//删除栈顶的元素
private:
	T* stack;//元素的指针
	int top;//栈顶的位置
	int capacity;//栈的容量
};

//模板类的成员函数，必须在头文件里一起定义，不能分开在另一个cpp里面放
//成员函数的定义

//构造函数的定义
template<class T>
MyStack<T>::MyStack(int c) :capacity{ c } //注意模板类的成员函数定义时，要加<T>
{
	if (capacity < 1)throw"stack capacity must be >0!";//容量至少为一，否则抛出异常
	stack = new T[capacity];//开辟一个动态数组(栈)空间，指针指向第一个元素的位置
	top = -1;//空的栈，top还没有指向任何元素，而即将指向的是下标为0的元素，所以现在为-1
}
//析构函数的定义
template<class T>
MyStack<T>::~MyStack()
{
	delete[] stack;//删除构造函数里面创建的动态数组，释放内存
}
//入栈函数的定义
template<class T>
void MyStack<T>::push(const T& item)
{
	//判断栈是否满了，如果只剩一个空位了，那就把容量扩大一倍，再push入新元素
	if (top == capacity - 1)
	{
		change_size1D(stack, capacity, capacity * 2);//调用扩容函数
		capacity *= 2;//如果上述函数成功执行了，没有抛出异常，就记录容量已经改变
	}
	stack[++top] = item;//往栈顶的下一个空位赋值新元素
}
//判断是否为空栈
template<class T>
inline bool MyStack<T>::is_empty() const//做成内置函数，编译时直接嵌入上级函数，速度比较快
{
	return top == -1;//bool函数的返回值可以为一个表达式，这样程序简洁明了
	//如果返回的表达式为真，那么函数真正返回的是1，否则为0
}
//返回栈顶元素的引用
template<class T>
inline T& MyStack<T>::top_item() const//内置函数，适用于频繁调用，函数体短小的函数
{
	if (is_empty())throw"The stack is empty!";
	return stack[top];//返回的元素实际上就是一个T类型的变量
}
//删除栈顶元素
template<class T>
void MyStack<T>::pop()
{
	if (is_empty())throw"The stack is empty! Cannot delete!";
	stack[top].~T();//注意！！！这里的元素有可能是类的对象，所以要调用析构函数为好
	top--;
}
#endif
