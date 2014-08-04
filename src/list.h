/*
 * =====================================================================================
 *
 *       Filename:  list.h
 *
 *    Description:  linked list
 *
 *        Version:  1.0
 *        Created:  08/02/2014 11:15:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <iostream>
#define DEBUG_MODE
#define NON_ITERATOR
//list node
template <typename T> struct ListNode{
	T data;
	ListNode<T> *prev;
	ListNode<T> *next;
	ListNode(const T &t):data(t),prev(NULL),next(NULL){}
};

//iterator class of List
template <typename U> class Iterator__Linked{
	template <typename TYPE> friend class List;
	private:
	ListNode<U> *cur;
	public:

	//default constructor
	//dereference this iterator occurs an error
	Iterator__Linked(): cur(NULL) { }

	//construct Iterator__Linked at node
	Iterator__Linked(ListNode<U> *node){
		cur = node;
	}

	//copy constructor
	Iterator__Linked(const Iterator__Linked &from){
		cur = from.cur;
	}

	//copy assignment
	Iterator__Linked& operator=(const Iterator__Linked &that){
		this->cur = that.cur;
		return *this;
	}

	//compare 
	bool operator!=(const Iterator__Linked &that) const {
		return cur != that.cur;
	}

	bool operator==(const Iterator__Linked &that) const {
		return cur == that.cur;
	}

	//dereference returning an object 
	U& operator*() const {
		return cur->data;
	}

	//I don't know what happens
	//Just write like stl
	U * operator->() const {
		return (U*) cur->data;
	}

	//prefix ++operator
	Iterator__Linked& operator++(){
		cur = cur->next;
		return *this;
	}
	//suffix ++operator
	Iterator__Linked operator++(int){
		Iterator__Linked tmp(*this);
		cur = cur->next;
		return tmp;
	}

	//prefix -- operator
	Iterator__Linked& operator--(){
		cur = cur->prev;
		return *this;
	}
	//suffix -- operator
	Iterator__Linked operator--(int){
		Iterator__Linked tmp(*this);
		cur = cur->prev;
		return tmp;
	}

	//			//move n items
	//			//n can be any integer
	//			//move forward when n is positive
	//			//move backward when n i negative
	//			//no move when n is 0
	//			Iterator__Linked& advance(int n){
	//				//move forward
	//				if (n > 0){
	//					while( cur->next && n-- > 0){
	//						cur = cur->next;
	//					}
	//					
	//				}else if( n < 0 ){
	//				//move backward
	//
	//				}else{
	//				//no move
	//				}
	//			}

	U& next(){	
		cur = cur->next;
		return cur->prev->data;
	}

	//java style iterator
	//
	bool hasNext()const{
		return cur->next != NULL;
	}
};



/*
 *	template class List
 *	List is bidirectional linked list
 *	
 *
 */
template <typename T>  class List{

#ifdef DEBUG_MODE
	template <class U> friend bool assert_list(const List<U> &);
#endif

	template <class U> friend std::ostream& operator<<(std::ostream&, const List<U>&);
	//template <class Tp> friend class Iterator__Linked;

	



	private:

	//head
	ListNode<T> *head;
	//tail 
	ListNode<T> *tail;
	//no. of nodes
	size_t sz;

	void copy_list(const List &from){	
		//get from's element
		ListNode<T> *pf = from.head->next;
		//while != from's tail
		//deep copy ListNode
		ListNode<T> *node = NULL;
		while( pf != from.tail){
			//create a new node using pf's data
			node = new ListNode<T>(pf->data);
			//insert to last
			insert_after(tail->prev, node);
			//move pf to next
			pf = pf->next;
			node = NULL;
		}
		//set sz
		sz = from.sz;
	}


	//destroy will release all data node 
	//and set head,tail to be 0
	//set sz to be 0
	void destroy(){
		ListNode<T> *p = head->next;
		ListNode<T> *q = head->next;
		while(p != tail){
			p = p->next;
			delete q;
			q = p;
		}

		head->next = tail;
		tail->prev = head;
		sz = 0;
	}

	//remove node p helper 
	void pop_node(ListNode<T> *p){
		p->next->prev = p->prev;
		p->prev->next = p->next;
		p->next = p->prev = NULL;
		delete p;
	}

	//insert node after p
	void insert_after(ListNode<T> *p, ListNode<T> *node){
		node->next = p->next;
		node->prev = p;
		p->next->prev = node;
		p->next = node;
	}
	
	//insert node before p
	void insert_before(ListNode<T> *p, ListNode<T> *node){
		node->prev = p->prev;
		node->next = p;
		p->prev->next = node;
		p->prev = node;
	}
	bool remove(ListNode<T> *node){
		//ignore head and tail
		if(node == head || node == tail){
			return false;
		}
		//relink next and previous node
		node->next->prev = node->prev;
		node->prev->next = node->next;
		delete node;
		return true;
	}




	public:
	
	typedef Iterator__Linked<T> iterator;

	List(){
		head = new ListNode<T>(T());
		tail = new ListNode<T>(T());
		head->next = tail;
		tail->prev = head;
		sz = 0;
	}

	List( const List &from){
		head = new ListNode<T>(T());
		tail = new ListNode<T>(T());
		head->next = tail;
		tail->prev = head;
		//copy_list(from);
		//not complete
		copy_list(from);
	}

	//non-virtual destructor
	~List(){
		destroy();
		delete head;
		delete tail;
	}

	//assignment operator
	List& operator=(const List &that){
		//if this is not equal to that
		//destroy this and copy that to this
		if(this != &that){
			//destroy this
			destroy();
			//copy list from that
			copy_list(that);
		}
		//if this is equal to that 
		//do nothing
		return &this;
	}

	//insert an item into head
	void push_front(const T &t){
		//create a new node
		ListNode<T> *node = new ListNode<T>(t);

		//insert after head
		insert_after(head, node);

		//increament sz
		++sz;
	}

	//append an item to the list
	void push_back( const T &t){
		//create a new node
		ListNode<T> *node = new ListNode<T>(t);

		//insert after tail's prev
		insert_after(tail->prev, node);

		//increate sz
		++sz;
	}


	//pop front
	//return true is list is not empty
	bool pop_front(){
		//if empty
		//Oh, my god, are you serious?
		//do you really want to pop something from an empyt list?
		if( empty() ){
			std::cerr << "pop from empty list error..." << std::endl;
			//std::cerr << "program's exits......" << std::endl;
			return false;
		}else{
			//if not empty
			//get node to be popped
			ListNode<T> *p = head->next;
			//pop it
			pop_node(p);
			//avoid dangling pointer
			p = NULL;
		}
		//decrease sz
		--sz;
		return true;
	}

	//pop the last element
	bool pop_back(){
		//if list is empty
		//It's a bad call
		if(empty()){
			std::cerr << "bad call pop_back on empty list..." << std::endl;
			return false;
		}else{

			//create a new node
			ListNode<T> *p = tail->prev;

			//delete node p
			pop_node(p);

			//avoid dangling pointer
			p = NULL;

		}
		//decrease sz
		--sz;
		return true;
	}
	
	//return a reference of first element
	T& front(){
		//if list is empty
		//Oh, no why are you doing so?
		if(empty()){
			std::cerr << "calling front() on an empty object..." <<std::endl;
			std::cerr << "data returned is not defined..." << std::endl;
			return head->data;
		}else{
			//return head's data
			return head->next->data;
		}

	}
	//return a reference of last element
	T& back(){
		//if list is empty
		//Oh, no!!!
		if(empty()){
			std::cerr << "calling back() on an empty list..." <<std::endl;
			std::cerr << "data returned is not defined..." << std::endl;
			return head->data;
		}else{
			//return head's data
			return tail->prev->data;
		}
	}


	//return the first element
	//calling the on an empty list will cause undefined behavior
	T front() const {
		//if list is empty
		//Oh, no why are you doing so?
		if(empty()){
			std::cerr << "calling front() on an empty object..." <<std::endl;
			std::cerr << "data returned is not defined..." << std::endl;
			return T();
		}else{
			//return head's data
			return head->next->data;
		}
	}




	//return the last element
	//calling the function on empty list will cause undefined behavior
	T back()const {
		//if list is empty
		//Oh, no!!!
		if(empty()){
			std::cerr << "calling back() on an empty list..." <<std::endl;
			std::cerr << "data returned is not defined..." << std::endl;
			return T();
		}else{
			//return head's data
			return tail->prev->data;
		}
	}

	//insert 
	void insert( iterator pos, const T &t){
		//create new node
		ListNode<T> *node = new ListNode<T>(t);
		//get cur;
		ListNode<T> *p = pos.cur;
		//insert before cur
		insert_after(p->prev, node);
		//increase sz
		++sz;
	}
	
	//insert [beg...end) before pos
	template <typename InputIter>
	void insert( iterator pos, InputIter beg, InputIter end){
		ListNode<T> *p = pos.cur;
		ListNode<T> *node = NULL;
		InputIter it = beg;
		while(it != end){
			node = new ListNode<T>(*it);
			insert_before(p, node);
			++sz;
		}
	}
	
	//insert n t's before pos
	void insert(iterator pos, int n, const T &t){
		//get cur
		ListNode<T> *p = pos.cur;
		//create new node
		ListNode<T> *node = NULL;
		//increase sz by n
		sz += n;
		//insert n times
		while ( n-- > 0 ){
			//create new node 
			node = new ListNode<T>(t);
			insert_before(p, node);
		}
	}


	//remove 
	iterator remove(iterator pos){
		iterator next_iter(pos.cur->next);
		//get cur
		ListNode<T> *p = pos.cur;
		//remove node
		if (remove(p)){
			--sz;
			p=NULL;
			return next_iter;
		}
		return pos;
	}

	//remove
	iterator remove(iterator beg, iterator end){
		//
		iterator it = beg;
		//remove all
		while (it != end){
			it = remove(it);
			
		}
		return it;
	}


	//clear all element
	void clear(){
		//destroy it
		destroy();
	}

	//first element
	iterator begin(){
		return Iterator__Linked<T>(head->next);
	}
		
	//end iterator
	iterator end(){
		return Iterator__Linked<T>(tail);
	}
	
	void swap(iterator one, iterator another){
		T t = *one;
		*one = *another;
		*another = t;
	}

	//return size of list
	size_t size() const {return sz;}

	bool empty() const { return sz == 0; }
};

template <class U> std::ostream& operator<<(std::ostream &os, const List<U> &list){
	if (list.head->next == list.tail){
		os <<"{}"<<std::endl;
		return os;
	}
	os << "{";
	ListNode<U> *p = list.head->next;
	while( p != list.tail->prev ){
		os << p->data <<", ";
		p = p->next;
	}
	if(list.tail->prev != list.head){
		os<< list.tail->prev->data;
	}
	os<< "}" <<std::endl;
	return os;
}

template <class U>  bool assert_list(const List<U> &list){
	size_t n = 0;
	ListNode<U> *p = list.head;
	//ListNode<U> *q = list.tail;
	if( list.tail->next != NULL){
		std::cerr << "tail's next is not null..." << std::endl;
		return false;
	}

	while(p){
		++n;
		//check p's next and p's previous
		//p is head
		if(p == list.head){
			if( p->prev != NULL ){
				std::cerr << "head's prev is not null..." <<std::endl;
			}

			if (p->next->prev != p){
				std::cerr << "not link back..." <<std::endl;
				return false;
			}
		}else if(p == list.tail){
			//p is tail
			if( p->prev->next != p){
				std::cerr << "not link..." << std::endl;
				std::cerr << "data = " << p->data << std::endl;
				return false;
			}
		}else{
			if( p->next->prev != p ){
				std::cerr << "not link back..." <<std::endl;
				std::cerr << "data = " << p->data << std::endl;
				return false;
			}
			if( p->prev->next != p){
				std::cerr << "not link..." << std::endl;
				std::cerr << "data = " << p->data << std::endl;
				return false;
			}
		}
		p = p->next;
	}

	if (n != list.sz + 2){
		std::cerr<< "no. of element is incorrect..." <<std::endl;
		std::cerr<< "n = " << n << std::endl;
		std::cerr << "sz = " << list.sz << std::endl;
		return false;
	}
	return true;
}
#endif
