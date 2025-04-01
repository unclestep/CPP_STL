#include "s21_vector.h"
template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &items) : m_size(items.size()), m_capacity(0U), arr(nullptr){
	reserve_more_capacity(m_size);
    std::memcpy(arr, items.begin(), items.size() * sizeof(T));
};

template <typename T>
void Vector<T>::reserve_more_capacity(size_type size) {
    if(arr == NULL){
        arr = new value_type[size];
		m_capacity = size;
        return;
    }
    if(size > m_capacity){
        value_type *buff = new value_type[size];
        for (size_t i = 0; i < m_size; ++i) {
            buff[i] = std::move(arr[i]);
        }
        if(arr != NULL){
            delete[] arr;
        }
        arr = buff;
        m_capacity = size;
    }
}

template <typename T>
Vector<T>::iterator Vector<T>::begin(){
    return arr;
}
template <typename T>
Vector<T>::iterator Vector<T>::end(){
    return arr + m_size;
}

template <typename T>
void Vector<T>::push_back(value_type v){
    if (m_size == m_capacity)
    {
        reserve_more_capacity(m_size * 2);
    }
    arr[m_size++] = v;
}

template <typename T>
Vector<T>::size_type Vector<T>::size(){
    return m_size;
}

template <typename T>
Vector<T>::reference Vector<T>::at(size_type pos)
{
    return arr[pos];
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &&v){
	if(this != &v){
		arr = v.arr;
		m_size = v.m_size;
		m_capacity = v.m_capacity;

		v.arr = nullptr;
		v.m_size = 0;
		v.m_capacity = 0;
	}
	return *this;
}

template <typename T>
Vector<T>::reference Vector<T>::operator[](size_type pos){
	return arr[pos];
}

template <typename T>
Vector<T>::const_reference Vector<T>::front(){
	return arr[0];
}

template <typename T>
Vector<T>::const_reference Vector<T>::back(){
	return arr[m_size-1];
}

template <typename T>
T* Vector<T>::data(){
	return arr;
}
template <typename T>
bool Vector<T>::empty(){
	return m_size == 0;
}
template <typename T>
Vector<T>::size_type Vector<T>::max_size(){
	return (size_t)(pow(2, 63))/(sizeof(T)) - (size_t)1;
}
template <typename T>
void Vector<T>::shrink_to_fit() {
	if(m_capacity > m_size){
		value_type *buff = new value_type[m_size];
		for (size_t i = 0; i < m_size; ++i) {
			buff[i] = std::move(arr[i]);
		}
		if(arr != NULL){
			delete[] arr;
		}
		arr = buff;
		m_capacity = m_size;
	}
}
template <typename T>
Vector<T>::size_type Vector<T>::capacity(){
	return m_capacity;
}