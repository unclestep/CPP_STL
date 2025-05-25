#include "s21_vector.h"
namespace s21{

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &items) : m_size(items.size()), m_capacity(0U), arr(nullptr){
	arr = new value_type[items.size()];
	int i = 0;
	for (auto it = items.begin(); it != items.end(); it++)
	{
		arr[i] = *it;
		i++;
	}
	m_size = items.size();
	m_capacity = items.size();
};

template <typename T>
void Vector<T>::reserve_more_capacity(size_type size) {
	if (size == 0) {
        size = 1;
    }

	if (size > m_capacity)
	{
		value_type *buff = new value_type[size];
		for (size_t i = 0; i < m_size; ++i){
			buff[i] = std::move(arr[i]);
		}
		delete[] arr;
		arr = buff;
		m_capacity = size;
	}
}

template <typename T>
Vector<T>::iterator Vector<T>::begin(){
    return arr;
}
template <typename T>
Vector<T>::iterator Vector<T>::begin() const{
	return arr;
}

template <typename T>
Vector<T>::iterator Vector<T>::end(){
    return arr + m_size;
}

template <typename T>
Vector<T>::iterator Vector<T>::end() const{
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
	if (pos >= m_size) {
		throw std::out_of_range("Vector index out of range");
	}
    return arr[pos];
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &&v) noexcept {
	if(this != &v){
		delete[] arr;
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
	return arr[(int)pos];
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

template <typename T>
void Vector<T>::reserve(size_type size){
	reserve_more_capacity(size);
}

template <typename T>
void Vector<T>::clear(){
	m_size = 0;
}
template <typename T>
void Vector<T>::erase(iterator pos){
	for(iterator i = pos; i < end()-1; i++){
		*i = *(i + 1);
	}
	m_size = m_size - 1;
}

template <typename T>
Vector<T>::iterator Vector<T>::insert(iterator pos, const_reference value){
	 if (pos < begin() || pos > end()) {
        throw std::out_of_range("Vector::insert - invalid position");
    }
	
	size_type index = pos - begin();

	reserve(m_size + 1);

	pos = index + begin();

	for (auto i = end(); i > pos; --i) {
        *i = *(i - 1); 
    }
	*pos = value;
	m_size = m_size + 1;
	return pos;
};

template <typename T>
void Vector<T>::pop_back(){
	if (m_size > 0) {
		--m_size;
	}
}

template <typename T>
void Vector<T>::swap(Vector& other){
	auto tmp_arr = other.arr;
	auto tmp_msize = other.m_size;
	auto tmp_mcapacity = other.m_capacity;

	other.arr = this->arr;
	other.m_size = this->m_size;
	other.m_capacity = this->m_capacity;

	this->arr = tmp_arr;
	this->m_size = tmp_msize;
	this->m_capacity = tmp_mcapacity;
}

template <typename T>
Vector<T>::Vector(const Vector &v) : m_size(v.m_size), m_capacity(v.m_capacity){
	arr = new value_type[v.m_size];

	for(auto it = v.begin(), it1 = begin(); it < v.end(); it++, it1++){
		*it1 = *it;
	}
	m_size = v.m_size;
	m_capacity = v.m_capacity;


};
}
