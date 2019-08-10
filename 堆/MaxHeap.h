/*
大顶堆（完全二叉树），每层节点，都是上层的比下层的大，
最下面一层的节点，从左到右依次排满，都是相同的深度
*/

#ifndef _MAXHEAP_H
#define _MAXHEAP_H
#include"MyUtility.h"//需要包含工具头文件，用来实现数组容量扩充

template<class T>
class MaxHeap
{
public:
	MaxHeap(int m = 10);//构造函数
	~MaxHeap();//析构函数，因为要创建数组，要释放数组内存
	bool is_empty();
	void push(const T&);
	void pop();//删除根节点的元素
	const T& top()const;//查看堆顶元素，不修改它
private:
	void bubble_up(int idx);//向上渗透
	void bubble_down(int idx);//向下渗透
	T* heap_arr;//用数组存放数据
	int max_size;//最大存放多少个数据
	int cur_size;//当前的数据个数
};

/*
成员函数的实现
*/

//构造函数
template<class T>
MaxHeap<T>::MaxHeap(int m)
{
	if (m <= 0)//数组容量必须大于0
		throw"max size must be > 0.";
	max_size = m;
	cur_size = 0;
	heap_arr = new T[max_size];//创建数组
}

//析构函数
template<class T>
MaxHeap<T>::~MaxHeap()
{
	delete[] heap_arr;
}

//判断堆是否为空
template<class T>
bool MaxHeap<T>::is_empty()
{
	return cur_size == 0;
}

//插入新的节点
template<class T>
void MaxHeap<T>::push(const T& item)
{
	if (cur_size == max_size)
	{
		change_size1D(heap_arr, max_size, max_size * 2);//调用扩容函数
		max_size *= 2;//如果上述函数成功执行了，没有抛出异常，就记录容量已经改变
	}
	heap_arr[cur_size] = item;//先把数据放在最后
	//再向上渗透,即冒泡
	bubble_up(cur_size);
	cur_size++;//数据增加了一个，要更新坐标
}

//删除根节点的元素
template<class T>
void MaxHeap<T>::pop()
{
	cur_size--;//指向最后一个数据的坐标
	heap_arr[0] = heap_arr[cur_size];//根被最后一个数据覆盖，即被删除
	bubble_down(0);//把根节点元素向下渗透
}

//查看堆顶的元素数据
template<class T>
const T& MaxHeap<T>::top()const
{
	return heap_arr[0];
}

//向上渗透
template<class T>
void MaxHeap<T>::bubble_up(int idx)
{
	/*
	规律：对于二叉树，每个节点的子节点的坐标，都是它的2倍(左子)，或2倍加1(右子)，
	所以，每个节点的根节点，就是它的位置减1，再被2整除
	*/
	int parent = (idx - 1) / 2;//得到父节点的坐标
	T temp = heap_arr[idx];//临时保存准备交换的数据
	while (idx > 0 && heap_arr[parent] < temp)//idx没有到树根，或父节点较小，就继续向上
	{
		heap_arr[idx] = heap_arr[parent];//把父节点的数据放到下面来
		idx = parent;//更新当前节点的坐标
		parent = (parent - 1) / 2;//更新父节点坐标
	}
	heap_arr[idx] = temp;
}

//向下渗透
template<class T>
void MaxHeap<T>::bubble_down(int idx)
{
	int larger;
	T temp = heap_arr[idx];
	while (idx < cur_size / 2)//循环到最后一层的上一层
	{
		int left = idx * 2;//左子节点坐标
		int right = left + 1;//右子节点坐标
		//注意！！要判断右子节点是否存在
		if (right < cur_size && heap_arr[left] < heap_arr[right])//如果右子节点存在并且比左子大
			larger = right;
		else//否则大的为左子节点
			larger = left;
		if (temp > heap_arr[larger])//如果根节点数据比大的节点还要大，就停止
			break;
		heap_arr[idx] = heap_arr[larger];//把大的子节点数据往上面放
		idx = larger;//更新idx
	}
	heap_arr[idx] = temp;//找到位置之后，把根元素放上去
}

#endif
