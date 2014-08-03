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
#define NON_ITERATOR
//list node
template <typename T> struct ListNode{
	T data;
	ListNode<T> *prev;
	ListNode<T> *next;
	ListNode(const T &t):data(t),prev(NULL),next(NULL){}
};


template <typename T> 
class List{
	template <class U> friend std::ostream& operator<<(std::ostream&, const List<U>&);
	private:
	//head
	ListNode<T> *head;
	//tail 
	ListNode<T> *tail;
	//no. of nodes
	size_t sz;

	void copy_list(const List &from){

		//get from head
		ListNode<T> *node = from.head;

		if(!node){
			head = NULL;
			tail = NULL;
		}else{
			//non-empty list

			//create a new ListNode as head and tail
			head = new ListNode<T>(node->data);

			tail = head;
			node = node->next;

			//deep copy all data
			while( node ){
				//create a new node and append
				ListNode<T> *tmp = new ListNode<T>(node->data);
				tail->next = tmp;
				tmp->prev = tail;

				//move p to next
				tail = tail->next;
				node = node->next;
			}
		}
		sz = from.sz;
	}
	

	//destroy will release all data node 
	//and set head,tail to be 0
	//set sz to be 0
	void destroy(){
		//get head
		ListNode<T> *p = head;
		ListNode<T> *q = head;
		//free every node
		while(p){
			p = p->next;
			delete q;
			q = p;
		}
		//set head tail sz to 0
		head = NULL;
		tail = NULL;
		sz = 0;
	}

	public:
	List():head(NULL), tail(NULL), sz(0){}

	List( const List &from){
		copy_list(from);
	}

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
	}
	
	//insert an item into head
	void push_front(const T &t){
		//create a new node
		ListNode<T> *node = new ListNode<T>(t);
		
		//if list is empty
		//set head tail
		if( empty() ){
			head = tail = node;
		}else{
		//if list is not empty
		//insert 
			//link new node to list
			node->next = head;
			head->prev = node;
			//set head to be new node
			head = node;
		}
		//increament sz
		++sz;
	}

	//append an item to the list
	void push_back( const T &t){
		//create a new node
		ListNode<T> *node = new ListNode<T>(t);
		//if this is empty
		//set head and tail to the new node
		if (empty()){
			head = tail = node;
		}else{

			//if this is non-empty
			tail->next = node;
			node->prev = tail;

			//append and update tail
			tail = node;
		}
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
			ListNode<T> *p = head;
			//move head to next
			head = head->next;

			//delete head 
			delete p;
			p = NULL;
			
			//if head is null then tail should be null
			if( !head ){
				tail = head;
			}else{
				// if head is not null
				// set head's prev to be null
				head->prev = NULL;	
			}
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
			//non-empty

			//move tail to previous node
			ListNode<T> *p = tail;
			tail = tail->prev;
			//delete last element
			delete p;
			p = NULL;
			//check if head has been deleted
			if( !tail ){
				//set head to NULL
				head = tail;
			}else{
				//set tail's next to NULL
				tail->next = NULL;
			}
		}
		//decrease sz
		--sz;
		return true;
	}
	
	//return the first element
	//calling the on an empty list will cause undefined behavior
	T front() const {
		//if list is empty
		//Oh, no why are you doing so?
		if(empty()){
			std::cerr << "calling front() on an empty list..." <<std::endl;
			std::cerr << "data returned is not defined..." << std::endl;
			return T();
		}else{
		//return head's data
			return head->data;
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
			return head->data;
		}
	}
	
	//clear all element
	void clear(){
		//destroy it
		destroy();
	}




	//return size of list
	size_t size() const {return sz;}
	
	bool empty() const { return sz == 0; }



};

template <class U> std::ostream& operator<<(std::ostream &os, const List<U> &list){
	os << "{";
	ListNode<U> *p = list.head;
	while( p != list.tail ){
		os << p->data <<", ";
		p = p->next;
	}
	if(list.tail){
		os<< list.tail->data;
	}
	os<< "}" <<std::endl;
	return os;
}


#endif
