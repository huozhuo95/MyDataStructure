#pragma once
/*
˳����У��Ƚ��ȳ���������
�������Ԫ�ض����Ҷˣ�����˻��п�λ�ã���ô��һ������Ԫ�ش�������
*/
#ifndef _MY_QUEUE_H
#define _MY_QUEUE_H


//�����������
template<class T>
class MyQueue
{
public:
	MyQueue(int c = 10);//Ĭ�Ϲ��캯��
	~MyQueue();//��������
	inline bool is_empty() const;//�ж��Ƿ�Ϊ��
	inline T& front_item() const;//���ض���Ԫ��
	inline T& rear_item() const;//���ض�βԪ��
	void push(const T& item);//�Ӷ�β�����Ԫ��
	void pop();//�Ӷ���ɾ��Ԫ��
private:
	T* queue;//ָ��Ԫ�ص�ָ��
	int front;//���׵��±ָ꣬���һ��Ԫ�ص�ǰһ��λ�ã����յ�λ��
	int rear;//��β���±ָ꣬�����һ��Ԫ��
	int capacity;//���е�����
};

//ģ����ĺ���ʵ�ֱ��������������ͬһ��ͷ�ļ������ܷ���
//��Ա�����Ķ���

//���캯���Ķ���
template<class T>
MyQueue<T>::MyQueue(int c)
{
	if (c <= 0)throw"The capacity must be > 0!";
	capacity = c;
	queue = new T[capacity];//�����ڴ�ռ䣬T���͵�����
	front = 0;
	rear = 0;//ָ���β���±�������±���ͬ��˵��û��Ԫ��
	//ע�⣡Ҫ�õ�һ��Ԫ�ش����queue[1]������queue[0]���ţ������±굽���Ҷ�֮������߶���ת��
}
//���������Ķ���
template<class T>
MyQueue<T>::~MyQueue()
{
	delete[] queue;//�ͷŶ�̬�ռ�
}
//�ж϶����Ƿ�Ϊ��
template<class T>
inline bool MyQueue<T>::is_empty() const
{
	return rear == front;//ָ���β���±�������±��غϣ�˵��û��Ԫ��
}
//���ض���Ԫ��
template<class T>
T& MyQueue<T>::front_item() const
{
	if (is_empty())throw"This queue has no element!";
	return queue[(front+1)%capacity];
	//�����frontʵ��ָ����ǿյ�Ԫ�أ�����Ӧ����front+1
	//����frontָ���Ҷ˵�ʱ��Ӧ��ȡ��˵�Ԫ�أ�����Ҫȡ������
}
//���ض�βԪ��
template<class T>
T& MyQueue<T>::rear_item() const
{
	if (is_empty())throw"This queue has no element!";
	return queue[rear];
}
//�Ӷ�β�����Ԫ��
template<class T>
void MyQueue<T>::push(const T& item)
{
	//����������ˣ���Ҫ�ӱ�����
	if (((rear + 1) % capacity) == front)
	{
		//�ӱ����е����������ѵ����ݣ�����
		T* new_queue = new T[capacity * 2];
		int start = (front + 1) % capacity;//start��ʾ����Ԫ�ص�λ���±�
		//�����������1.�ճ������Ǹ��ռ������ˣ�2.�ճ������Ǹ��ռ����м䣬������ֳ�������
		//����start�ж����������
		if (start == 0 || start == 1)//���1
			std::copy(queue + start, queue + start + capacity - 1, new_queue);
			/*
			copy�����Ĺ�����:
			�������һ�����ݸ���[arr,arr+n)����һ��������ȥ
			copy(�����������Ԫ��ָ�룬���������βԪ��ָ��+1����һ�������ճ��λ�õ���ʼָ��)
			*/
		else//���2
		{
			std::copy(queue + start, queue + capacity, new_queue);
			std::copy(queue, queue + rear +1, new_queue + capacity - start);
		}
		front = 2 * capacity - 1;//���ݺ�ָ���Ҷ�
		rear = capacity - 2;//���ݺ�ָ���β
		capacity *= 2;//��¼�����ı仯
		delete[] queue;//ɾ��ԭ����С��������ռ�
		queue = new_queue;//���½��Ĵ�����ָ�븳ֵ�����ݳ�Աqueue,����ָ�����µ�����
	}
	rear = (rear + 1) % capacity;//ע�⣡������һ���ǳ����ʵ���˴��Ҷ�ת����˵Ĺ���
	queue[rear] = item;
}
//�Ӷ���ɾ��Ԫ��
template<class T>
void MyQueue<T>::pop()
{
	if (is_empty())throw"This queue has no element!";
	front = (front + 1) % capacity;//����frontָ����Ƕ��׵�ǰһ��λ�ã�����Ҫ���±����һλ
	queue[front].~T();
}

#endif