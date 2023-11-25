#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include "myvector.h"
template<typename T> MyVector<T>::MyVector(int cap)//constructor of the vector

:data(new T[cap]),v_size(0),v_capacity(cap) {}

template<typename T> MyVector<T>::~MyVector()//destructor of the vector
{
if (!empty()) delete [] data;
}
template<typename T> void MyVector<T>::push_back(T element)//insert the element to the end of the vector
{
if (v_capacity==0)
{v_capacity=1;}
if(v_size==v_capacity)
{
T* A=new T[2*v_size];
for (int j=0;j<v_size;j++)
{
	A[j]=data[j];
}
if (data!=NULL) {delete [] data;}
data=A;
v_capacity=2*v_size;

}
data[v_size]=element;
v_size++;
}
template<typename T> void MyVector<T>::erase(int index)//erases the element at the given index
{
if (index<0||index>=v_size)
{throw out_of_range("illegal index in function at()");}
for (int i=index+1;i<v_size;i++)
{
	data[i-1]=data[i];
	
}
v_size--;
}
template<typename T> void MyVector<T>::insert(int index, T element)//inserts the given element at the given index
{
if (index!=0 && index>v_size)
{
	throw runtime_error("index out of range");
}
if (v_capacity==0)
{v_capacity=1;}
if(v_size==v_capacity)
{
T* A=new T[2*v_size];
for (int j=0;j<v_size;j++)
{
	A[j]=data[j];
}
if (data!=NULL) {delete [] data;}
data=A;
v_capacity=2*v_size;

}
for (int k=v_size-1;k>=index;k--)
  {data[k+1]=data[k];}
data[index]=element;
v_size++;
}
template<typename T> T&  MyVector<T>::at(int index)//returns an element at the given index
{
if (index<0 || index>=v_size)
{throw out_of_range("illegal index in function at()");}
return data[index];
}
template<typename T> const T&  MyVector<T>::front()//returns the element at the front of the vector
{
if (v_size==0)
{
	throw out_of_range("index out of range");
}

return data[0];
}
template<typename T> const T&  MyVector<T>::back()//returns the element at the back of the vector
{
if (v_size==0)
{
	throw out_of_range("index out of range");
}
return data[v_size-1];
}
template<typename T> int MyVector<T>:: size() const//returns the size of the vector
{
return v_size;
}
template<typename T> int MyVector<T>::capacity() const//returns the total capacity of the vector
{
return v_capacity;
}
template<typename T> bool MyVector<T>::empty() const//returns true if the vector is empty
{
return v_size==0;
}
template<typename T> void MyVector<T>::shrink_to_fit()//shirinks the capacity of the vector to fit its size
{
if (v_size<v_capacity)
{T* B=new T[v_size];
for (int j=0;j<v_size;j++)
{
	B[j]=data[j];
}
if (data!=NULL) delete [] data;
data=B;
v_capacity=v_size;
}
}
template class MyVector<Contact*>;

