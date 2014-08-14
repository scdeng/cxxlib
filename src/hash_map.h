/*
 * =====================================================================================
 *
 *       Filename:  hash.h
 *
 *    Description:  hash symbol table
 *
 *        Version:  1.0
 *        Created:  08/13/2014 09:29:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <list>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "hash_function.h"

/*	@brief function object
 */
template <class T> inline size_t hashcode(const T &t ){
	return _Hash_bytes( &t, sizeof(t) , static_cast<size_t>(0xc70f6907UL) );
}

/*	@brief hash a string to a size_t
 */
inline size_t hashcode(string str){
	return _Hash_bytes( str.c_str(), str.length(), 0 );
}

/*	@brief hash array of char into size_t
 */
inline size_t hashcode(char *p, size_t n){
	return _Hash_bytes( p, n, 0 );
}

/*	@brief hash array of char into size_t
 */
inline size_t hashcode(char const *p, size_t n){
	return _Hash_bytes( p, n, 0 );
}

inline size_t hashcode(int n){
	return static_cast<size_t>(n);
}

inline size_t hashcode(char c){
	return static_cast<size_t>(c);
}

inline size_t hashcode(unsigned char c){
	return static_cast<size_t>(c);
}

inline size_t hashcode(unsigned int n){
	return static_cast<size_t>(n);
}

inline size_t hashcode(long n){
	return static_cast<size_t>(n);
}

inline size_t hashcode(unsigned long n){
	return static_cast<size_t>(n);
}
//===================================================//



//using namespace std;
#define DEBUG
template <typename TK, typename TV> 
class Pair{
	private:
		//k,v pair
		TK k;
		TV v;
	public:
		/*	@brief constructor
		*/
		Pair(const TK &_k, const TV &_v): k(_k), v(_v) {} 
		/*	@brief copy constructor
		*/
		Pair(const Pair &from):k(from.k), v(from.v) {}
		/*	@brief copy constructor
		*/
		Pair & operator=(const Pair &that){
			k = that.k;
			v = that.v;
			return *this;
		}

		/*	@brief get key
		 *
		 *	return constant reference
		 */
		const TK & first() const {
			return k;
		}

		/*	@brief get value
		 *	return constant reference
		 */
		const TV & second()const {
			return v;
		}

		/*	@brief return reference of value
		*/
		TV& second() {
			return v;
		}
};

template <typename K, typename V>
class HashMap{

/*	largest prime <= 2^i for all i >= 3
 *	primes[] = {
 *		2, 3, 7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191, 16381,
 *		32749, 65521, 131071, 262139, 524287, 1048573, 2097143, 4194301,
 *		8388593, 16777213, 33554393, 67108859, 134217689, 268435399,
 *		536870909, 1073741789, 2147483647
 *	};
 */

	template <typename TK, typename TV>
	friend std::ostream& operator<<(std::ostream &os, const HashMap<TK,TV> & map);

	private:

		//typedef std::list<Pair<K,V> >::iterator  listPairIter;
		typedef std::vector<std::list<Pair<K,V> > > HashTable;

		typedef typename std::list<Pair<K,V> >::const_iterator Pair_constIter;
		typedef typename std::list<Pair<K,V> >::iterator Pair_Iter;

		static const size_t INIT_CAPACITY = 7u;
		//no. of <k,v> pairs
		size_t _N;
		//size of hash table
		size_t _M;
		//data
		//vector<list<Pair<K,V> > > _table;
		HashTable _table;

		/*	@brief get the minimum number power of 2
		 *		which is greater than n
		 *		eg. 7 is 3
		 *		eg. 9 is 16
		 *		eg. 8 is 8
		 */
		size_t get_least_power_2(size_t n){
			size_t bits = 0;
			while(n > 0 ){
				n = (n >> 1);
				++bits;
			}
			return bits;
		}

		/*	@brief hash k int 0...M-1
		 *	return a unsigned interger range [0...M-1)
		 */
		size_t hash(const K &k)const{
			//return (hashcode(k) & 0x7fffffffffffffffU) % M;
			return (hashcode(k) & 0x7fffffffffffffffU) % _M;
		}
	
		/*	@brief insert pair index it's corresponding list
		 */
		void __insert(size_t idx, Pair<K,V> pair){

			//find iterator	
			Pair_Iter it = __find(idx, pair.first());
			//if k is not contained
			if( it == _table[idx].end() ){
				//insert
				_table[idx].push_front(pair);
			}else{
				//if k is contained change value
				it->second() = pair.second();
			}
			//increase size of hash map
			++_N;
			//if load factor is more than ten
			//resize hash table
			if( _N > 10 * _M ){
				size_t bits = get_power_of_2(_N);
#ifdef DEBUG
				std::cout << "#of bits of " << _N << std::endl;
#endif
				resize(5 * _M);
			}
		}

		/*	@brief remove k
		 */
		void __remove(const K &k){
			//get index of k
			size_t idx = hash(k);
			//find k	
			Pair_Iter it = __find(idx, k);
			//if it == _table[idx].end() 
			//it is not contained in this hash map
			if( it == _table[idx].end() ){
				return ;
			}else{
				_table[idx].erase(it);
			}
			--_N;
		}

		/*	@brief check if k is contain in hash table
		 */	
		bool __contain(const K &k) const {
			size_t idx = hash(k);
			//find k	
			Pair_constIter it = __find(idx, k);
			if( it == _table[idx].end() ){
				return false;
			}else{
				return true;
			}
		}

		/*	@brief find k in chain list of index idx
		 *		if k is contained at chain list of idx
		 *		return a non-const iterator
		 *		return _table[idx].end() if not contained
		 */
		Pair_Iter __find(size_t idx, const K &k){
			Pair_Iter it;
			for(it = _table[idx].begin(); it != _table[idx].end(); ++it){
				if( it->first() == k ) {
					break;
				}
			}
			return it;
		}

		/*	@brief find k in chain list of index idx
		 *		if k is contained at chain list of idx
		 *		return a const iterator
		 *		return _table[idx].end() if not contained
		 */
		Pair_constIter __find(size_t idx, const K &k)const{
			Pair_constIter it;
			for(it = _table[idx].begin(); it != _table[idx].end(); ++it){
				if( (it->first()) == k ) {
					break;
				}
			}
			return it;
		}

		/*	@brief resize of hash table
		 *		rehash every k and insert every <k,v> pair into new hash table
		 */
		void resize(size_t sz){
			HashTable tmp( HashTable( sz, std::list<Pair<K,V> >() ) );
			//update size of table
			size_t prev_table_size = _M;
			_M = sz;
			_N = 0;
			//for every k,v pair rehash k and insert into tmp
			for(size_t i=0; i<prev_table_size; ++i){
				Pair_Iter it;
				for(it = _table[i].begin(); it != _table[i].end(); ++it){
					//rehash k
					size_t idx = hash(it->first());
					//insert <k,v> pair into tmp
					tmp[idx].push_front(*it);
				}
			}
			//update hash table
			_table = tmp;
		}


	public:
		
		/*	@brief default constructor
		 */
		HashMap(size_t M = INIT_CAPACITY): _N(0), _M(M),
			_table(std::vector<std::list<Pair<K,V> > >( M, std::list<Pair<K,V> >() ) )
		{ }


		/*	@brief copy constructor
		 */
		HashMap(HashMap &from){
			_N = from._N;
			_M = from._M;
			_table = from._table;
		}

		/*	@brief assignment operator
		 */
		HashMap& operator=(HashMap &that){
			_N = that._N;
			_M = that._M;
			_table = that._table;
		}
		

		/*	@brief overload subscript operator
		 *		return a reference of k's corresponding value
		 *
		 */
		V& operator[](const K &k){
			//get index 
			size_t idx = hash(k);
			Pair_Iter it = __find(idx, k);
			if( it == _table[idx].end() ){
				//k is not contained
				//insert k with a random value
				V v = V();
				Pair<K,V> pair(k,v);
				__insert(idx, pair);
				//get index again
				//because __insertion may change hash table
				idx = hash(k);
				it = __find(idx, k);
			}
			return it->second();
		}

		/*	@brief overload subscript operator
		 *		return a const reference of k's corresponding value
		 */
		const V& operator[](const K &k)const{
			size_t idx = hash(k);
			Pair_constIter it = __find(idx, k);
			//k is not contained
			if( it == _table[idx].end() ){
				std::cerr<<"fatal error: key is not contained"<<std::endl;
				std::cerr<<"program crashed..."<<std::endl;
				exit(-1);
			}
			return it->second();	
		}

		/*	@brief insert a <k,v> pair
		 */
		void insert(const K &k, const V &v){
			//make a pair and insert this pair
			Pair<K,V> pair(k,v);
			insert(pair);
		}
	
		/*	@brief insert a pair into hash map
		 */
		void insert(const Pair<K,V> &pair){
			//get index of k
			size_t idx = hash(pair.first());
			//insert
			__insert(idx,pair);

		}
	
		/*	@brief remove key k in hash map
		 */
		void remove(const K &k){
			__remove(k);

		}

		/*	@brief return reference of k's associated value
		 *		if k is not contained, it's a fatal error
		 */
		V& at(const K &k){
			size_t idx = hash(k);
			Pair_Iter it = __find(idx, k);
			if( it == _table[idx].end() ){
				std::cerr<<"fatal error: key is not contained"<<std::endl;
				std::cerr<<"program crashed..."<<std::endl;
				exit(-1);
			}
			return it->second();	
		}

		/*	@brief return const reference of k's associated value
		 *		if k is not contained, it's a fatal error
		 */
		const V& at(const K &k)const{
			//get index of hash table
			size_t idx = hash(k);
			Pair_constIter it = __find(idx, k);
			//not found 
			if( it == _table[idx].end() ){
				std::cerr<<"fatal error: key is not contained"<<std::endl;
				std::cerr<<"program crashed..."<<std::endl;
				exit(-1);
			}
			return it->second();	
		}

		/*	@brief query if k is contain 
		 */
		bool contain(const K &k)const{
			return __contain(k);
		}

		/*	@brief get size of hash map
		 */
		size_t size()const{
			return _N;
		}

		/*	@brief 
		 *		return # of buckets
		 */
		size_t bucket_count() const {
			return _M;
		}

		/*	@brief 	
		 *		return # of elements in bucket idx
		 *		idx shall be less than bucket_count
		 */
		size_t bucket_size(size_t idx)const {
			return _table[idx].size();
		}
	
		/*	@brief return load factor which is
		 *		_N / _M
		 */
		double load_factor() const {
			return 1.0 * _N / _M ;
		}

#ifdef DEBUG
		const HashTable & getHashTable() const{
			return _table;
		}

		size_t max_bucket_size() const {
			size_t max_bs = 0;
			for(size_t i=0; i<_table.size(); ++i){
				if( _table[i].size() > max_bs ){
					max_bs = _table[i].size();
				}
			}
			return max_bs;
		}
#endif
};

template <typename K, typename V>
std::ostream& operator<<(std::ostream &os, const HashMap<K,V> & map){
	os << map._N << " elements in hash map" << std::endl; 
	os << map._M << " # of hash size" << std::endl;
	for(size_t i=0; i<map._M; ++i){
		os << "index " << i << " :\t";
		typename std::list<Pair<K,V> >::const_iterator it; 
		for(it=map._table[i].begin(); it != map._table[i].end(); ++it){
			os<<"<"<<it->first()<<", "<<it->second()<<"> ";
		}
		os<<std::endl;
	}
	return os;
}

#endif
