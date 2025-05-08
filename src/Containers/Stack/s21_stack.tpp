#ifndef CPP2_S21_CONTAINERS_1_S21_STACKWDW_H
#define CPP2_S21_CONTAINERS_1_S21_STACKWDW_H

#include "s21_stack.h"

namespace s21{
	template<class T, class Container>
	Stack<T, Container>::Stack() : vector() {}

	template<class T, class Container>
	Stack<T, Container>::~Stack() {}

	template<class T, class Container>
	Stack<T, Container>::Stack(std::initializer_list<value_type> const &items) : vector(items){}

	template<class T, class Container>
	Stack<T, Container>::const_reference Stack<T, Container>::top(){
		return *(vector.end() - 1);
	}
	template<class T, class Container>
	bool Stack<T, Container>::empty(){
		return vector.empty();
	}
	template<class T, class Container>
	Stack<T, Container>::size_type Stack<T, Container>::size(){
		return vector.size();
	}
	template<class T, class Container>
	void Stack<T, Container>::push(const_reference value){
		vector.push_back(value);
	}
	template<class T, class Container>
	void Stack<T, Container>::pop(){
		vector.pop_back();
	}
	template<class T, class Container>
	void Stack<T, Container>::swap(Stack<T, Container> &other) {
		vector.swap(other.vector);
	}
	template<class T, class Container>
	Stack<T, Container>::Stack(const Stack &s) : vector(s.vector){}

	template<class T, class Container>
	Stack<T, Container>::Stack(Stack &&s) : vector(std::move(s.vector)){}

    template<class T, class Container>
	Stack<T, Container>& Stack<T, Container>::operator=(Stack<T, Container>&& s) noexcept {
    	vector = std::move(s.vector);
    	return *this;
	}

}



#endif //CPP2_S21_CONTAINERS_1_S21_STACKWDW_H
