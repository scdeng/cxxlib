/*
 * =====================================================================================
 *
 *       Filename:  stack.h
 *
 *    Description:  stack LIFO
 *
 *        Version:  1.0
 *        Created:  08/04/2014 02:05:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef STACK_H
#define STACK_H
#include "list.h"

template <typename T> class Stack{
	template <typename Tp> friend std::ostream& operator<<(std::ostream&, const Stack<Tp>&);
	private:
		List<T> data;
	public:
		
		typedef Iterator__Linked<T> iterator;

		Stack(): data( List<T>() ) { }
	
		//push an item into stack
		void push(const T &t){
			data.push_front(t);
		}
		
		//pop front
		void pop(){
			data.pop_front();
		}
		
		//return object of top
		T top() const {
			return data.front();
		}
		
		//return the reference of top
		T& top() {
			return data.front();
		}

		size_t size(){
			return data.size();
		}

		bool empty(){
			return data.empty();
		}
		
		iterator begin() {
			return data.begin();
		}

		iterator end(){
			return data.end();
		}


};
template <typename Tp>
std::ostream & operator<<( std::ostream& os, const Stack<Tp> &stack){
	return (os << stack.data);
}



#endif
