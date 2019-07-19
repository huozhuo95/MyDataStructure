#pragma once
//����ͷ�ļ�����ֹ���ذ���
#ifndef _MYUTILITY_H
#define _MYUTILITY_H

#include<iostream>

//���ߺ������������������������һ��
template<class T>
void change_size1D(T*& a, const int old_size, const int new_size);

//���ߺ������������������������һ��
template<class T>
void change_size1D(T*& a, const int old_size, const int new_size)
{
	//����µ������СС���㣬���׳��쳣
	if (new_size < 0)throw "New length must be >= 0";

	T* temp = new T[new_size];
	int number = old_size < new_size ? new_size : old_size;
	std::copy(a, a + number, temp);
	delete[] a;
	a = temp;
}

#endif