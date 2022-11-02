#ifndef __MYARRAY_HPP__
#define __MYARRAY_HPP__

#include <cstring>
#include <iostream>
using namespace std;

template<typename Type>
class MyArray
{
public:
    /***********迭代器***********/
    class iterator
    {    
    public:
        //构造函数
        iterator(Type *pos):m_pos{pos}{}
        //++运算符重载
        iterator &operator++()
        {
            m_pos++;
            return *this;
        }
        //--运算符重载
        iterator &operator--()
        {
            m_pos--;
            return *this;
        }
        //+=运算符重载
        iterator &operator+=(int index)
        {
            m_pos += index;
            return *this;
        }
        //==运算符重载
        bool operator==(const iterator&other)
        {
            return m_pos == other.m_pos;
        }
        //!=运算符重载
        bool operator!=(const iterator&other)
        {
            return m_pos != other.m_pos;
        }
        //*运算符重载
        Type &operator*()
        {
            return *m_pos;
        }

    private:
        Type *m_pos;
    };
    //获取第一个元素的迭代器
    iterator begin()
    {
        return iterator{m_pdata};
    }
    
    //获取最后一个元素的迭代器
    iterator end()
    {
        return iterator{m_pdata+m_length};
    }

public:
    //构造函数
    MyArray(unsigned int n = 10);
    
    //析构函数
    ~MyArray();
    
    //拷贝构造函数
    MyArray(const MyArray&);
    
    //赋值运算符函数
    MyArray &operator=(const MyArray&);
    
    //插入元素
    void push(Type value);
    
    //删除指定下标的元素
    void delete_pos(int index);
    
    //删除指定值的元素
    void delete_value(Type value);
    
    //访问指定下标的元素
    Type &at(int index);
    
    //获取数组的长度
    int length();
    
    //获取数组的容量
    int capcaity();
    
    //判断数组是否为空
    bool isEmpty();
    
    //下标运算符重载
    Type &operator[](int index);
    const Type &operator[](int index)const;

private:
    Type *m_pdata;  //指向数据存储区(数组)的指针
    int m_length;   //当前数组的长度
    int m_capacity; //当前数组的容量
};


//构造函数
template<typename Type>
MyArray<Type>::MyArray(unsigned int n):m_length(0),m_capacity(n)
{   
    if (m_capacity == 0)
    {
        m_pdata = nullptr;//防止变为野指针
    }
    else
    {
        m_pdata = new Type[m_capacity];
    }
}

//析构函数
template<typename Type>
MyArray<Type>::~MyArray()
{
    delete[] m_pdata;
}

//拷贝构造函数
template<typename Type>
MyArray<Type>::MyArray(const MyArray<Type>&a)
{
    //分配新的空间
    m_capacity = a.m_capacity;
    m_pdata = new Type[m_capacity];
    //拷贝数据
    m_length = a.m_length;
    memcpy(m_pdata,a.m_pdata,sizeof(Type)*m_length);
}

//赋值运算符函数
template<typename Type>
MyArray<Type> &MyArray<Type>::operator=(const MyArray<Type>&a)
{
    //防止自赋值
    if (this == &a)
    {
        return *this;
    }
    //释放掉已有的空间
    delete[] m_pdata;
    //重新分配空间
    m_capacity = a.m_capacity;
    m_pdata = new Type[m_capacity];
    //拷贝数据
    m_length = a.m_length;
    memcpy(m_pdata,a.m_pdata,sizeof(Type)*m_length);
    
    return *this;
}

//插入元素
template<typename Type>
void MyArray<Type>::push(Type value)
{
    if (m_length >= m_capacity)
    {
        //存满了，需要扩容
        //重新分配一块更大的内存
        Type *p = new Type[2*m_capacity];
        //将原来的数据拷贝过来
        memcpy(p,m_pdata,sizeof(Type)*m_capacity);
        m_capacity *= 2;
        //释放原有的空间
        delete[] m_pdata;
        m_pdata = p;
        p = nullptr;
    }
    m_pdata[m_length++] = value;
}

//删除指定下标的元素
template<typename Type>
void MyArray<Type>::delete_pos(int index)
{
    if (index < 0 || index >= m_length)
    {
        //越界保护
        throw out_of_range("delete_pos error:not have this index");
    }

    for (int i = index; i < m_length-1; i++)
    {
        m_pdata[i] = m_pdata[i+1];
    }
    m_length--;
}

//删除指定值的元素
template<typename Type>
void MyArray<Type>::delete_value(Type value)
{
    int index;
    for (index = 0; index < m_length; index++)
    {
        if (m_pdata[index] == value)
        {
            //找到了
            delete_pos(index);
        }
    }
}

//访问指定下标的元素
template<typename Type>
Type &MyArray<Type>::at(int index)
{
    if (index < 0 || index >= m_length)
    {
        //越界保护
        throw out_of_range("at error:not have this index");
    }
    return m_pdata[index];
}

//获取数组的长度
template<typename Type>
int MyArray<Type>::length()
{
    return m_length;
}

//获取数组的容量
template<typename Type>
int MyArray<Type>::capcaity()
{
    return m_capacity;
}

//判断数组是否为空
template<typename Type>
bool MyArray<Type>::isEmpty()
{
    return m_length == 0;
}

//下标运算符重载
template<typename Type>
Type &MyArray<Type>::operator[](int index)
{
    if (index < 0 || index >= m_length)
    {
        //越界保护
        throw out_of_range("[] error:not have this index");
    }
    return m_pdata[index];
}

template<typename Type>
const Type &MyArray<Type>::operator[](int index)const
{
    if (index < 0 || index >= m_length)
    {
        //越界保护
        throw out_of_range("[] error:not have this index");
    }
    return m_pdata[index];
}

#endif