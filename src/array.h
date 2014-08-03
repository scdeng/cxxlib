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

		//get the least power of 2 which is greater than n
		size_t get_least_power_2(size_t n){
			size_t bits = 0;
			while(n > 0 ){
				n = (n >> 1);
				++bits;
			}
			
			return 1 << bits;
		}
		
		void check_index(size_t i) const {
			if( i >= sz || i < 0){
				//delete pointer
				delete [] ptr;
				std::cerr<< "index is " << i <<std::endl;
				std::cerr<<"index out of bounds error..." << "\nprogram exits......" <<std::endl;
				exit(1);
			}
		}

	public:
		//default constructor
		//initialize size to 0 ,capacity to 1
		Array(): sz(0), cap(1), ptr(new T[1]){ }
		
		//construct an Array contain size of T
		Array(size_t size, const T &t) {
			sz = size;
			cap = get_least_power_2(size);
			ptr = new T[cap];
			for(int i=0; i<size; ++i){
				*(ptr+i) = t;
			}
		}
		
		~Array(){
			delete []ptr;
		}

		//copy constructor
		//deep copy constructor
		Array(const Array &from){
			sz = from.sz;
			cap = get_least_power_2(sz);
			ptr = new T[cap];
#ifdef MEMCOPY
			memcpy(ptr, from.ptr, sizeof(T) * sz);
#else
			for(int i=0; i<sz; ++i){
				*(ptr + i) = from[i];
			}
#endif
		}
		

		//assignment operator
		//deep copy assignment
		Array& operator=( const Array &that){
			//check self assignment
			if (this != &that){
				delete []ptr;
				sz = that.sz;
				cap = get_least_power_2(sz);
				ptr = new T[cap];
#ifdef MEMCOPY
				//if T has reference count
				//bugs occur
				memcpy(ptr, that.ptr, sizeof(T) * sz);
#else	
				for(int i=0; i<sz; ++i){
					*(ptr+i) = that[i];
				}
#endif
			}
		}
		

		//push t to the end of Array
		//if there is no room reallocate enough memory
		void push_back(const T &t){
			//no capacity to push 
			//increase cap to 2*cap
			if(sz == cap){
				T *new_ptr = new T[2*cap];
#ifdef MEMCOPY
				//bug prone
				memcpy(new_ptr, ptr, sizeof(T) * sz);
#else
				for(unsigned i=0; i<sz;++i){
					*(new_ptr+i) = *(ptr+i);
				}
#endif
				new_ptr[sz++] = t;
				cap *= 2;
				delete [] ptr;
				ptr = new_ptr;
			}else{
				ptr[sz++] = t;
			}
		}
		
		//erase the last element of Array
		T pop_back(){
			T t = *(ptr+sz-1);
			this->erase(sz-1);
			return t;
		}

		//overload operator[] 
		//@param i:	i should be greater than or equal to 0
		//and smaller than sz
		T& operator[](size_t i)
		{
			check_index(i);
			return *(ptr+i);
		}
		const T& operator[](size_t i)const 
		{
			check_index(i);
			return *(ptr+i);
		}


		//insert t into position idx
		void insert(size_t idx, const T &t){
			check_index(idx);
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
				ptr = new_ptr;

			}else{
				//move data  
				for(unsigned i=sz; i>idx; --i){
					*(ptr+i) = *(ptr+i-1);
				}
				*(ptr+idx) = t;
				++sz;
			}
		}

		//erase element in position idx 
		//it is less efficient than linked list
		void erase(size_t idx){
			check_index(idx);
			//move data
			for(unsigned i=idx; i<sz-1; ++i){
				*(ptr+i) = *(ptr+i+1);
			}	
			//decreament sz
			--sz;
		}

		//clear the element of Array
		//
		void clear(){
			delete [] ptr;
			ptr = new T[1];
			sz = 0;
			cap = 1;
		}

		//return the size of Array
		size_t size()const{
			return sz;
		}
		
		//return the capacity of Array
		size_t capacity()const{
			return cap;
		}
		
		bool empty() const {
			return sz == 0;
		}
};

template <class T> std::ostream & operator<<(std::ostream &os, const Array<T> &a){
	os << "{";
	for(unsigned  i=0; i<a.size()-1; ++i){
		os << a[i] << ", ";
	}
	if( a.size() -1 >= 0){
		os << a[a.size()-1];
	}
	os << "}" << std::endl;
	return os;
}

#endif
