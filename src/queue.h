/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  FIFO
 *
 *        Version:  1.0
 *        Created:  08/04/2014 10:34:57 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"

template <typename T> class Queue{
	template <typename Tp> friend std::ostream& operator<<(std::ostream&, const Queue<Tp>&);
	private:
		List<T> data;

	public:
		
		typedef Iterator__Linked<T> iterator;
		//default constructor
		Queue():data(List<T>()) {}

		//push an iterm
		void enqueue(const T &t){
			data.push_back(t);
		}

		//pop front
		//return value not reference
		void dequeue(){
			data.pop_front();
		}

		//return object
		T front() const {
			return data.front();
		}
		//return object	
		T rear()const{
			return data.back();
		}
	
		T& front() {
			return data.front();
		}
		T& back() {
			return data.back();
		}

		//modify the first element
		void change_head(const T &t){
			front() = t;
		}
		
		void clear(){
			data.clear();
		}

		size_t size(){
			return data.size();
		}

		bool empty(){
			return data.empty();
		}

		iterator begin(){
			return data.begin();
		}

		iterator end(){
			return data.end();
		}
};
template <typename Tp> 
std::ostream& operator<<(std::ostream &os, const Queue<Tp> &q){
	return (os << q.data);
}
#endif
