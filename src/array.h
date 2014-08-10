/*
 * =====================================================================================
 *
 *       Filename:  array.h
 *
 *    Description:  sequence array 
 *
 *        Version:  1.0
 *        Created:  08/02/2014 09:27:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include <stdlib.h>

template <typename T> class Array;
template <typename T> std::ostream & operator<<(std::ostream &os, const Array<T> &a);

//=============================================
//iterator class of List
template <typename U> class Iterator__Seq{
	template <typename TYPE> friend class Array;
	
	private:
		U *ptr;
		unsigned offset;
	public:

	//default constructor
	//dereference this iterator occurs an error
	Iterator__Seq(): ptr(NULL), offset(0) { }

	//construct Iterator__Seq at node
	Iterator__Seq(U *_ptr, int _offset) : ptr(_ptr), offset(_offset) {}

	//copy constructor
	Iterator__Seq(const Iterator__Seq &from){
		ptr = from.ptr;
		offset = from.offset;
	}

	//copy assignment
	Iterator__Seq& operator=(const Iterator__Seq &that){
		ptr = that.ptr;
		offset = that.offset;
		return *this;
	}

	//compare 
	bool operator!=(const Iterator__Seq &that) const {

		return ( ptr != that.ptr  || offset != that.offset  );
	}

	bool operator==(const Iterator__Seq &that) const {
		return ( ptr == that.ptr  && offset == that.offset );
	}

	//dereference returning an object 
	U& operator*() const {
		return *(ptr + offset);
	}

	//I don't know what happens
	//Just write like stl
	U * operator->() const {
		return ptr+offset;
	}

	//prefix ++operator
	Iterator__Seq& operator++(){
		++offset;
		return *this;
	}
	//suffix ++operator
	Iterator__Seq operator++(int){
		Iterator__Seq __tmp(*this);
		++offset;
		return __tmp;
	}

	//prefix -- operator
	Iterator__Seq& operator--(){
		--offset;
		return *this;
	}
	//suffix -- operator
	Iterator__Seq operator--(int){
		Iterator__Seq __tmp(*this);
		--offset;
		return __tmp;
	}

	//operator +
	Iterator__Seq& operator+(int n){
		offset + n;
		return *this;
	}
};
//==========================================================


template <typename T> class Array{

	//friend std::ostream& operator<<(std::ostream &, const Array<T> &);
	private:
		//no. of elements
		size_t sz;
		//no. of capacity
		size_t cap;
		//the real element
		T * ptr;
		//reference count
		//int *ref_count;
		
		/*	@brief get the minimum number of power of 2 which is greater than n
		 */
		size_t get_least_power_2(size_t n){
			size_t bits = 0;
			while(n > 0 ){
				n = (n >> 1);
				++bits;
			}
			return 1 << bits;
		}
		
		/*	@brief check if index is out of bounds
		 */
		void check_index(size_t i) const {
			if( i >= sz || i < 0){
				//delete pointer
				delete [] ptr;
				std::cerr<< "index is " << i <<std::endl;
				std::cerr<<"index out of bounds error..." 
					<< "\nprogram exits......" <<std::endl;
				exit(1);
			}
		}
	
		/*	@brief insert t at position idx
		 */
		void __insert__(size_t idx, const T &t){
			//there is no room for new item
			if ( sz == cap ){
				//allocate new space
				T * new_ptr = new T[cap << 1];
				//copy from old to new space
				//index [0...idx-1]
				for(unsigned i=0; i<idx; ++i){
					*(new_ptr+i) = *(ptr+i);
				}
				//set ptr[idx] to t
				*(new_ptr+idx) = t;
				//copy the remaining data
				//index [idx+1 ... sz
				for(unsigned i=idx; i<sz; ++i){
					*(new_ptr+i+1) = *(ptr+i);
				}
				//increament sz
				++sz;
				//double capacity
				cap *= 2;
				//delete old space
				delete [] ptr;
				//reset ptr
				ptr = new_ptr;
			}else{
				//move data  
				for(unsigned i=sz; i>idx; --i){
					*(ptr+i) = *(ptr+i-1);
				}
				//push data
				*(ptr+idx) = t;
				//increase data
				++sz;
			}
		}
		/*	@brief remove idx th element
		 */
		void __erase__(size_t idx){
			if( idx >= sz ){
				return ;
			}
			//move data
			for(unsigned i=idx; i<sz-1; ++i){
				*(ptr+i) = *(ptr+i+1);
			}
			ptr[sz] = T();
			//decreament sz
			--sz;
		}
		
		/*	@brief destroy this array
		 */
		void destroy(){
			sz = 0;
			delete [] ptr;
		}

		/*	@brief deep copy data from src pointer to destination
		 *	@param src	copy from
		 *	@param dest	copy to
		 *	@param n	number of elements
		 */
		void deep_copy_data(T *src, T* dest, size_t n){
			for(size_t i=0; i<n; ++i){
				*(dest+i) = *(src+i);
			}
		}

	public:
		typedef Iterator__Seq<T> iterator;
		/*	@brief default constructor 
		 * 		initialize size to 0 ,capacity to 1
		 */
		Array(): sz(0), cap(1), ptr(new T[1]){ }
		
		/* @brief construct an Array contain size of T
		 * @param 	size	number of elements
		 * 			if size < 1 make an empty array
		 * @param 	t		
		 */
		Array(size_t size, const T &t) {
			if(size < 1){
				sz = 0; 
				cap = 1;
				ptr = new T[1];
			}else{
				sz = size;
				cap = get_least_power_2(size);
				ptr = new T[cap];
				for(unsigned i=0; i<size; ++i){
					*(ptr+i) = t;
				}
			}
		}
	
		/*	@brief copy constructor
		 *		deep copy data
		 */
		Array(const Array &from) {
			ptr = new T[from.cap];
			sz = from.sz;
			cap = from.cap;
			deep_copy_data(from.ptr, ptr, sz);
		}
		
		/*	@brief assignment operator
		 *		deep copy data
		 */
		Array& operator=(const Array &that){
			if( this != &that ){
				destroy();
				sz = that.sz;
				cap = that.cap;
				ptr = new T[cap];
				deep_copy_data(that.ptr, ptr, sz);
			}
			return *this;
		}

		/*	@brief destructor
		 */
		~Array(){
			destroy();
		}
		
		/* 	@brief push t to the end of Array 
		 *  	if there is no room reallocate enough memory
		 */
		void push_back(const T &t){
			__insert__(sz, t);
		}
		
		/*	@brief erase the last element of Array
		 */
		T pop_back(){
			T t = *(ptr+sz-1);
			__erase__(sz-1);
			return t;
		}

		/* 	@brief overload operator[] 
		 * 	@param i:	i should be greater than or equal to 0 
		 * 		and smaller than sz
		 */
		T& operator[](size_t i){
			check_index(i);
			return *(ptr+i);
		}
		
		const T& operator[](size_t i)const {
			check_index(i);
			return *(ptr+i);
		}


		/*	@brief insert t into position idx
		 */
		void insert(size_t idx, const T &t){
			//check_index(idx);
			if( idx > sz ){
				std::cerr<<"Index out of bounds error" << std::endl;
				exit(-1);
			}
			__insert__(idx, t);
		}

		/*	@brief erase element at position idx
		 *		it is less efficient than linked list
		 */
		void erase(size_t idx){
			if(idx >= sz){
				std::cerr<<"Index out of Bounds error" <<std::endl;
				exit(1);
			}
			__erase__(idx);
		}

		/*	@brief clear the element of Array
		 */
		void clear(){
			destroy();
			ptr = new T[1];
			sz = 0;
			cap = 1;
		}
		
		/*	@brief return an iterator (the first element)
		 */
		iterator begin() const {
			return Iterator__Seq<T>(ptr,0);
		}
	
		/*	@brief return one off the end iterator
		 */
		iterator end() const {
			return Iterator__Seq<T>(ptr,sz);
		}
	
		/*	@brief insert t into pos
		 */
		void insert(iterator pos, const T &t){
			size_t p = pos.offset;
			__insert__(p, t);
		}
	
		/*	@brief delete element 
		 */
		void erase(iterator pos){
			size_t p = pos.offset;
			__erase__(p);
		}
		
	
		/*	@brief swap two element
		 */
		void swap(iterator one, iterator another){
			T t = *one;
			*one = *another;
			*another = t;
		}

		/*	@brief return the size of Array
		 */
		size_t size()const{
			return sz;
		}
		
		/*	@brief return the capacity of Array
		 */
		size_t capacity()const{
			return cap;
		}
	
		/*	@brief check if array is empty
		 */
		bool empty() const {
			return sz == 0;
		}
};

template <class T> std::ostream & operator<<(std::ostream &os, const Array<T> &a){
	os << "{";
	int sz = a.size();
	for(int i=0; i<sz-1; ++i){
		os << a[i] << ", ";
	}
	if( sz - 1 >= 0){
		os << a[sz - 1];
	}
	os << "}" << std::endl;
	return os;
}

#endif
