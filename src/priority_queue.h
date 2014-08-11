/*
 * =====================================================================================
 *
 *       Filename:  priority_queue.h
 *
 *    Description:  priority min queue and index priority min queue
 *
 *        Version:  1.0
 *        Created:  08/09/2014 11:19:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include "array.h"
#include <iostream>
#include <vector>
//#define DEBUG_TEST
template <typename K> 
class MinPQ{

	template <typename T>
		friend std::ostream& operator<<(std::ostream &os, const MinPQ<T> &pq);
	private:
		//keys from index 1 to N (exclusive)
		Array<K> keys;

		//keys[1...N] are the keys
		size_t N;
		
		/*	@brief check keys are min heap
		 */
		bool check_min_heap(){
			for(size_t idx = 1; idx <= N>>1; ++idx){
				if( ((idx<<1) <= N) && keys[idx] > keys[idx<<1]){
					std::cerr<<"size of heap is: " << N <<std::endl;
					std::cerr<<"keys["<<idx<<"] = " <<keys[idx];
					std::cerr<<"\tkeys["<<(idx<<1) << "]" << std::endl;
					std::cerr<<"not a heap "<<std::endl;
					return false;
				}
				if(	( ( (idx<<1)+1 ) <= N ) && keys[idx] > keys[(idx<<1)+1] ) {
					std::cerr<<"size of heap is: " << N <<std::endl;
					std::cerr<<"keys["<<idx<<"] = " <<keys[idx];
					std::cerr<<"\tkeys["<<((idx<<1)+1) << "]" << std::endl;
					std::cerr<<"not a heap "<<std::endl;
					return false;
				}
			}
			return true;
		}
		
		/*	@brief ckeck if keys[i] < keys[j]
		 */
		bool less(size_t i, size_t j)const{
			return keys[i] < keys[j];
		}

		/*	@brief swap element of index i and j
		 */
		void swap(size_t i, size_t j){
			K tmp = keys[i];
			keys[i] = keys[j];
			keys[j] = tmp;
		}

		/*	@brief Assume that keys[1...N-1] are a min heap
		 *		now insert a key at position N
		 *		adjust keys[1...N] to be a min heap
		 *	@param n 
		 */
		void swim(size_t n){
//			while( (n > 1) && keys[n] < keys[n>>1] ){
			while( (n > 1) && less(n, n>>1)  ){
				//swap
				swap(n, n>>1);
				//n = n/2
				n >>= 1;
			}
		}
			
		/*	@brief sink i 
		 *		n violate heap 
		 *		all other keys do not sink n
		 */
		void sink(size_t i){
			//i is current index
			while( 2*i <= N ){
				//invariant
				//j is possible next sink index
				size_t j = 2*i;
				if( j < N && less(j+1, j) ){
					++j;
				}
				if( !less(j, i) ) {
					break;
				}
				swap(i,j);
				i = j;
			}
		}
//		void sink(size_t n){
//			size_t left = n<<1;
//			size_t right = (n<<1) + 1;
//			//keys[n] has no child
//			if( left > N ){
//				return ;
//			}else if(left <= N && right > N){
//				//no right child
//				if( less(left, n) ){
//					swap(left,n);
//					sink(left);
//				}
//			}else if(right <= N){
//				if( less(left,right) ){
//					if( less(left,n) ) {
//						swap(left,n);
//						sink(left);
//					}
//				}else{
//					if( less(right, n) ){
//						swap(right,n);
//						sink(right);
//					}
//				}
//			}
//		}


	public:
		/*	@brief default constructor
		 *		new array with one element keys[0] = K()
		 *		range[1...N] are keys
		 */
		MinPQ():keys( Array<K>(1,K()) ), N(0) {}
		
		/*	@brief copy constructor
		 */
		MinPQ(const MinPQ &from): keys(from.keys), N(from.N) {}

		/*	@brief assignment operator
		 */
		MinPQ& operator=(const MinPQ &that){
			if(this != &that){
				keys = that.keys;
				N = that.N;
			}
			return *this;
		}

		/*	@brief insert k into pq
		 *	@param  k	key
		 */
		void insert(const K &k){
			//push
			//it is a bug
			//keys[++N] = k;
			keys.push_back(k);
			++N;
			swim(N);
			check_min_heap();
		}
		
		/*	@brief remove minimum key 	
		 *		return the minimum
		 */
		K removeMin(){
			if( empty() ){
				std::cerr<<"remove empty priority queue"<<std::endl;
				exit(1);
			}
			K minKey = keys[1];
			swap(1, N--);
			sink(1);
#ifdef DEBUG_TEST

			std::cout<<"keys are: " <<keys;
#endif
			//this is a bug.....
			keys.pop_back();
			return minKey;
		}

		/*	@brief return size of pq
		 */
		size_t size()const{
			return N;
		}
	
		/*	@brief check if pq is empty
		 */
		bool empty()const {
			return N == 0;
		}

};

template <typename T>
std::ostream& operator<<(std::ostream &os, const MinPQ<T> &pq){
	os << pq.keys;
	return os;
}


/*	@brief
 *		it makes sense to allow clients to refer items 
 *		which are already on priority queue
 *		one way to do this is to associate a unique index
 *		with each item
 */
template <typename K> class IndexMinPQ{

	template <typename T> 
	friend std::ostream& operator<<(std::ostream &os, const IndexMinPQ<T> &mpq);

	private:
		int N;
		int NMAX;
		//keys[1...N] are heap data
		Array<K> keys;
		//index of heap
		Array<int> pq;
		//reverse index
		//qp[pq[i]] = i
		Array<int> qp;
		
		/*	@brief check if keys[ pp[i] ] is less than keys[ pq[j] ]
		 *	@param i	pq[i] is the key
		 *	@param j	pq[j] is the key
		 */
		bool less(int i, int j)const {
			return keys[ pq[i] ] < keys[ pq[j] ];
		}
		
		void swap(int i, int j){
			//swap pq
			int tmp = pq[i];
			pq[i] = pq[j];
			pq[j] = tmp;
			
			//update qp
			qp[pq[i]] = i;
			qp[pq[j]] = j;
		}

		/*	@brief swim pq[i]
		 */
		void swim(int i){
			while( i > 1 && less(i, i>>1) ){
				swap(i, i>>1);
				i >>= 1;
			}
		}
		
		/*	@brief sink pq[i]
		 *		what elagant and beautiful code block
		 */
		void sink(int i){
			//i is current index
			while( 2*i <= N ){
				//invariant
				//j is possible next sink index
				int j = 2*i;
				if( j < N && less(j+1, j) ){
					++j;
				}
				if( !less(j, i) ) {
					break;
				}
				//
				swap(i,j);
				i = j;
			}
		}

		/*	@brief check if index is less than NMAX and 
		 *		greater than or equal to 0
		 */
		bool check_index(int index){
			if( index < NMAX && index >= 0 ){
				return true;
			}else{
				std::cerr<<
					"Index should less than maximun # of elements on pq" << std::endl;
				exit(1);
			}
		}


	public:
	
		/*	@brief default constructor
		 *		using for some cases in which IndexMinPQ is a member
		 *		some class, but this class is not initialized all ()
		 */
		IndexMinPQ(){
			int maxN = 1;
			NMAX = maxN;
			N = 0;
			keys = Array<K>(maxN + 1, K());
			pq = Array<int>(maxN + 1, -1);
			qp = Array<int>(maxN, -1);
		}
		/*	@brief construct with maximum number index
		 */
		IndexMinPQ(int maxN){
			//maximum # of elements on priority queue
			NMAX = maxN;
			N = 0;
			keys = Array<K>(maxN + 1, K());
			pq = Array<int>(maxN + 1, -1);
			qp = Array<int>(maxN, -1);
		}
	
		void remove(int index){
			check_index(index);
			if( !contain(index) ){
				std::cerr<<"index is not contained on priority queue" <<std::endl;
				return ;
			}
			//k is where index of element is
			int k = qp[index];
			//swap k with last
			swap(k, N--);
			//swap k
			swim(k);
			//sink k
			sink(k);
			//reset keys[index]
			keys[index] = K();
			//remove index
			qp[k] = -1;
		}

		/*	@brief remove minimum key
		 *		return index of minimum key
		 */
		int removeMin(){
			//
			int indexOfMin = pq[1];
			//swap min and last element
			swap(1,N--);
			//sink first
			sink(1);
			//update keys
			//K minKey = keys[indexOfMin];
			qp[pq[N+1]] = -1;
			keys[pq[N+1]] = K();
			return indexOfMin;
		}

		/*	@brief change k associates with index
		 *	@param index if index is not contained 
		 *		insert it into priority queue
		 *	@param k
		 */
		void changeKey(int index, const K &k){
			check_index(index);
			if( !contain(index) ){
				insert(index, k);
				return ;
			}
			keys[index] = k;
			swim( qp[index] );
			sink( qp[index] );
		}

		/*	@brief insert index with k
		 *	@param index if index is already on priority queue
		 *		change its corresponding key to k
		 *	@param k
		 */
		void insert(int index, const K &k){
			check_index(index);
			if( contain(index) ){
				changeKey(index,k);
				return ;
			}
			++N;	
			//put k into keys		
			keys[index] = k;
			//put index on pq
			pq[N] = index;
			//update inverse index
			qp[index] = N;
			//swim pq[N]
			swim(N);
		}
		
		/*	@brief return index of minimum key
		*/
		int minIndex() const{
			return pq[1];
		}
		
		/*	@brief return the minimum key
		*/
		K min()const{
			return keys[pq[1]];
		}
	
		/*	@brief check if index is contained
		 */
		bool contain(int index){
			return qp[index] != -1;
		}

		/*	@brief if queue is empty
		 */
		bool empty() const {
			return N == 0;
		}
		

};

template <typename K> 
std::ostream& operator<<(std::ostream &os, const IndexMinPQ<K> &mpq){
	os<<mpq.keys;
	os<<mpq.pq;
	os<<mpq.qp;
	return os;
}


#endif
