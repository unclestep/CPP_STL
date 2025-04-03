#ifndef TESTVECTOR_H
#define TESTVECTOR_H

#include <iostream>
#include <initializer_list>
#include <utility>
#include <cstring>
#include <math.h>
template <class T>
class Vector
{
private:
    size_t m_size;
    size_t m_capacity;
    T *arr;
    T *buffer;
public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = size_t;
private:
    void reserve_more_capacity(size_type size);
public:
    Vector() : m_size(0U), m_capacity(0U), arr(nullptr) {}

    explicit Vector(size_type n) : m_size(n), m_capacity(n), arr(n ? new T[n] : nullptr) {}

    Vector(std::initializer_list<value_type> const &items);

    Vector(Vector &v);

    Vector(Vector &&v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr)
    {
        v.arr = nullptr;
        v.m_size = 0;
    }

	Vector& operator=(Vector &&v) noexcept;
    ~Vector() { delete[] arr; }

    size_type size();

    reference at(size_type pos);

	reference operator[](size_type pos);

	const_reference front();

	const_reference back();

	T* data();

	bool empty();

	void shrink_to_fit();

	size_type capacity();

    void push_back(value_type v);

	iterator insert(iterator pos, const_reference value);

	size_type max_size();

	void reserve(size_type size);

	void clear();

	void erase(iterator pos);

	iterator begin();

	void pop_back();

	void swap(Vector& other);

    iterator end();

};

#endif
