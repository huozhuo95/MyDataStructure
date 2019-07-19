#pragma once
//保护头文件，防止多重包含
#ifndef _MYUTILITY_H
#define _MYUTILITY_H

#include<iostream>

//工具函数，用来将数组的容量扩大一倍
template<class T>
void change_size1D(T*& a, const int old_size, const int new_size);

//工具函数，用来将数组的容量扩大一倍
template<class T>
void change_size1D(T*& a, const int old_size, const int new_size)
{
	//如果新的数组大小小于零，就抛出异常
	if (new_size < 0)throw "New length must be >= 0";

	T* temp = new T[new_size];
	int number = old_size < new_size ? new_size : old_size;
	std::copy(a, a + number, temp);
	delete[] a;
	a = temp;
}

#endif