#include "s21_vector.h"
template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &items) : m_size(items.size()), m_capacity(0U), arr(nullptr){
    reserve_more_capacity(m_capacity);
    std::memcpy(arr, items.begin(), items.size() * sizeof(T));
};

template <typename T>
void Vector<T>::reserve_more_capacity(size_type size) {
    if(arr == NULL){
        arr = new value_type[size];
        return;
    }
    m_capacity = m_size * 2;
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
