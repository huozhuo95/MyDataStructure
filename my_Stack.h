#pragma once
//����ͷ�ļ�����ֹ���ذ���
#ifndef _MYSTACK_H
#define _MYSTACK_H

#include"my_Utility.h"//ͷ�ļ����������һ��ͷ�ļ�

//MyStack�������
template<class T>
class MyStack
{
public:
	MyStack( int c = 10 );//Ĭ�Ϲ��캯������ʼ����Ϊ10
	~MyStack();//��������

	inline bool is_empty() const;//����Ա������ֻ��ȡ�����ı����ݳ�Ա��ֵ
	inline T& top_item() const;//����ջ����Ԫ�أ�ֻ��ȡ��Ҳ��peek��
	void push(const T& item);//��ջ����ջ��ͬʱҲҪ����item
	void pop();//ɾ��ջ����Ԫ��
private:
	T* stack;//Ԫ�ص�ָ��
	int top;//ջ����λ��
	int capacity;//ջ������
};

//ģ����ĳ�Ա������������ͷ�ļ���һ���壬���ֿܷ�����һ��cpp�����
//��Ա�����Ķ���

//���캯���Ķ���
template<class T>
MyStack<T>::MyStack(int c) :capacity{ c } //ע��ģ����ĳ�Ա��������ʱ��Ҫ��<T>
{
	if (capacity < 1)throw"stack capacity must be >0!";//��������Ϊһ�������׳��쳣
	stack = new T[capacity];//����һ����̬����(ջ)�ռ䣬ָ��ָ���һ��Ԫ�ص�λ��
	top = -1;//�յ�ջ��top��û��ָ���κ�Ԫ�أ�������ָ������±�Ϊ0��Ԫ�أ���������Ϊ-1
}
//���������Ķ���
template<class T>
MyStack<T>::~MyStack()
{
	delete[] stack;//ɾ�����캯�����洴���Ķ�̬���飬�ͷ��ڴ�
}
//��ջ�����Ķ���
template<class T>
void MyStack<T>::push(const T& item)
{
	//�ж�ջ�Ƿ����ˣ����ֻʣһ����λ�ˣ��ǾͰ���������һ������push����Ԫ��
	if (top == capacity - 1)
	{
		change_size1D(stack, capacity, capacity * 2);//�������ݺ���
		capacity *= 2;//������������ɹ�ִ���ˣ�û���׳��쳣���ͼ�¼�����Ѿ��ı�
	}
	stack[++top] = item;//��ջ������һ����λ��ֵ��Ԫ��
}
//�ж��Ƿ�Ϊ��ջ
template<class T>
inline bool MyStack<T>::is_empty() const//�������ú���������ʱֱ��Ƕ���ϼ��������ٶȱȽϿ�
{
	return top == -1;//bool�����ķ���ֵ����Ϊһ�����ʽ����������������
	//������صı��ʽΪ�棬��ô�����������ص���1������Ϊ0
}
//����ջ��Ԫ�ص�����
template<class T>
inline T& MyStack<T>::top_item() const//���ú�����������Ƶ�����ã��������С�ĺ���
{
	if (is_empty())throw"The stack is empty!";
	return stack[top];//���ص�Ԫ��ʵ���Ͼ���һ��T���͵ı���
}
//ɾ��ջ��Ԫ��
template<class T>
void MyStack<T>::pop()
{
	if (is_empty())throw"The stack is empty! Cannot delete!";
	stack[top].~T();//ע�⣡���������Ԫ���п�������Ķ�������Ҫ������������Ϊ��
	top--;
}
#endif