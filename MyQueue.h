/*
顺序队列，先进先出，后进后出
如果队列元素都在右端，而左端还有空位置，那么下一个新增元素存放在左端
*/
#ifndef _MYQUEUE_H
#define _MYQUEUE_H


//队列类的声明
template<class T>
class MyQueue
{
public:
	MyQueue(int c = 10);//默认构造函数
	~MyQueue();//析构函数
	inline bool is_empty() const;//判断是否为空
	inline T& front_item() const;//返回队首元素
	inline T& rear_item() const;//返回队尾元素
	void push(const T& item);//从队尾添加新元素
	void pop();//从队首删除元素
private:
	T* queue;//指向元素的指针
	int front;//队首的下标，指向第一个元素的前一个位置，即空的位置
	int rear;//队尾的下标，指向最后一个元素
	int capacity;//队列的容量
};

//模板类的函数实现必须和类声明放在同一个头文件，不能分离
//成员函数的定义:

//构造函数的定义
template<class T>
MyQueue<T>::MyQueue(int c)
{
	if (c <= 0)throw"The capacity must be > 0!";
	capacity = c;
	queue = new T[capacity];//开辟内存空间，T类型的数组
	front = 0;
	rear = 0;//指向队尾的下标与队首下标相同，说明没有元素
	//注意！要让第一个元素存放在queue[1]，而把queue[0]空着，便于下标到了右端之后在左边队首转移
}
//析构函数的定义
template<class T>
MyQueue<T>::~MyQueue()
{
	delete[] queue;//释放动态空间
}
//判断队列是否为空
template<class T>
inline bool MyQueue<T>::is_empty() const
{
	return rear == front;//指向队尾的下标与队首下标重合，说明没有元素
}
//返回队首元素
template<class T>
T& MyQueue<T>::front_item() const
{
	if (is_empty())throw"This queue has no element!";
	return queue[(front+1)%capacity];
	//这里的front实际指向的是空的元素，所以应该是front+1
	//而当front指向右端的时候，应该取左端的元素，所以要取余运算
}
//返回队尾元素
template<class T>
T& MyQueue<T>::rear_item() const
{
	if (is_empty())throw"This queue has no element!";
	return queue[rear];
}
//从队尾添加新元素
template<class T>
void MyQueue<T>::push(const T& item)
{
	//如果容量满了，就要加倍容量
	if (((rear + 1) % capacity) == front)
	{
		//加倍队列的容量，重难点内容！！！
		T* new_queue = new T[capacity * 2];
		int start = (front + 1) % capacity;//start表示队首元素的位置下标
		//分两种情况：1.空出来的那个空间在两端；2.空出来的那个空间在中间，即数组分成两部分
		//利用start判断这两种情况
		if (start == 0 || start == 1)//情况1
			std::copy(queue + start, queue + start + capacity - 1, new_queue);
			/*
			copy函数的功能是:
			将数组的一段数据复制[arr,arr+n)到另一个数组中去
			copy(复制数组的首元素指针，复制数组的尾元素指针+1，另一个数组的粘贴位置的起始指针)
			*/
		else//情况2
		{
			std::copy(queue + start, queue + capacity, new_queue);
			std::copy(queue, queue + rear +1, new_queue + capacity - start);
		}
		front = 2 * capacity - 1;//扩容后指向右端
		rear = capacity - 2;//扩容后指向队尾
		capacity *= 2;//记录容量的变化
		delete[] queue;//删除原来的小容量数组空间
		queue = new_queue;//把新建的大容量指针赋值给数据成员queue,它就指向了新的数组
	}
	rear = (rear + 1) % capacity;//注意！！！这一语句非常精妙，实现了从右端转到左端的功能
	queue[rear] = item;
}
//从队首删除元素
template<class T>
void MyQueue<T>::pop()
{
	if (is_empty())throw"This queue has no element!";
	front = (front + 1) % capacity;//由于front指向的是队首的前一个位置，所以要把下标后移一位
	queue[front].~T();
}

#endif
