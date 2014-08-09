/*
 * =====================================================================================
 *
 *       Filename:  map.h
 *
 *    Description:  map base red black tree
 *
 *        Version:  1.0
 *        Created:  08/08/2014 09:00:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef MAP_H
#define MAP_H
#include "rbtree.h"

template <typename K, typename V>
class Map{
	template <typename TK, typename TV>
		friend std::ostream& operator<<(std::ostream &os, const Map<TK,TV> &map);
	private:
		typedef RBTree<K,V> Tree;
		//red black tree
		Tree rbt;

		bool isValidIndex(int i){
			return i<rbt.size() && i>=0;
		}
	public:
		/*	@brief default constructor
		 */
		Map():rbt(Tree()) { }
		
		/*	@brief copy constructor
		 */
		Map(const Map &from):rbt(from.rbt) {}
	
		/*	@brief overload assignment 
		 *		destroy and deep copy
		 */
		Map& operator=(const Map &that){
			//check self assignment
			if( this != &that ){
				rbt = that.rbt;
			}
			return *this;
		}
	
		/*	@brief get key whose index (in-order traverse BST) is idx
		 */
		K getKey(size_t idx){
			if( !isValidIndex(idx) ){
				std::cerr<< "Index out of bounds" << std::endl;
			}
			return rbt.select(idx);
		}

		/*	@brief const operator[] overload
		 *		return an object of V
		 */
		V operator[](const K &k) const {
			return rbt.get(k);
		}

		/*	@brief operator[] overload
		 *		return reference
		 *		if k is not contained 
		 *			insert k
		 */
		V& operator[](const K &k) {
			return rbt.get(k);
		}
			
		K min() const {
			return rbt.min();
		}

		/*	@brief return size of elements
		 */
		size_t size()const{
			return rbt.size();
		}
	
		/*	@brief clear map
		 */
		void clear(){
			rbt.clear();
		}
		
		/*	@brief insert k, v pair
		 */
		void insert(const K &k, const V &v){
			rbt.insert(k,v);
		}

		/*	@brief erase a element with key equals to k
		 */
		void erase(const K &k){
			rbt.remove(k);
		}
		
		/*	@brief check if map is empty
		 *		return true is map is empty
		 */
		bool empty()const {
			return rbt.empty();
		}

		/*	@brief chech if key is contained
		 */
		bool isContain(const K &k)const{
			return rbt.contain(k);
		}

		/*	@brief return vector of all keys in ascending order
		 */
		std::deque<K> getAllKeys(){
			rbt.keys();
		}
};

template <typename TK, typename TV>
std::ostream& operator<<(std::ostream &os, const Map<TK,TV> &map){
	os<<"=====================map starts====================" << std::endl;
	os << map.rbt;
	os<<"=====================map ends======================" << std::endl;
	return os;
}
#endif




