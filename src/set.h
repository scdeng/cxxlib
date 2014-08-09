/*
 * =====================================================================================
 *
 *       Filename:  set.h
 *
 *    Description:  set class unique set
 *
 *        Version:  1.0
 *        Created:  08/09/2014 10:17:23 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */
#ifndef SET_H
#define SET_H

#include "rbtree.h"

template <typename K> class Set{
	
	template <typename T>
		friend std::ostream & operator<<(std::ostream &os, const Set<T> &set);

	private:
		typedef RBTree<K,bool> BST;
		BST rbt;
	public:
		/*	@brief default constructor
		 */
		Set():rbt( BST() ) {}
		
		/*	@brief copy constructor
		 *		deep copy......
		 */
		Set(const Set &from):rbt(from.rbt) {}
	
		/*	@brief assignment operator
		 *		deep copy......
		 */
		Set& operator=(const Set &that){
			if(this != &that){
				this->rbt = that.rbt;
			}
			return *this;
		}

		/*	@brief return an copied object(not a reference) of idx th key
		 */
		K operator[](int idx)const{
			return rbt.select(idx);
		}

		/*	@brief insert an element of k 
		 */
		void insert(const K &k){
			rbt.insert(k,false);
		}

		/*	@brief remove an element of k
		 */
		void erase(const K &k){
			rbt.remove(k);
		}

		/*	@brief clear set
		 */
		void clear(){
			rbt.clear();
		}
		/*	@brief check if set is empty
		 */
		bool empty() const {
			return rbt.empty();
		}
		/*	@brief check if k is contained
		 */
		bool isContain(const K &k){
			return rbt.contain(k);
		}
		/*	@brief return size of set(no. of elements)
		 */
		size_t size()const{
			return rbt.size();
		}

		/*	@brief return manimum key(not reference) of set
		 */
		K min()const{
			return rbt.min();
		}
		/*	@brief return maximum key(not reference) of set
		 */
		K max()const{
			return rbt.max();
		}
		
		/*	@brief return a vector of all keys(in ascending order) in set
		 */
		std::vector<K> getAllKeys()const{
			retur rbt.getAllKeys();
		}

};

template <typename T>
std::ostream & operator<<(std::ostream &os, const Set<T> &set){
	os<<"===============set begins==================="<<std::endl<<std::endl;
	os<<set.rbt;
	os<<"===============set ends====================="<<std::endl;
	return os;
}

#endif
